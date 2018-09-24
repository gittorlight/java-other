// 这是主 DLL 文件。

#include "stdafx.h"

#include "jvmti_evt_ex.h"
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <jvmti.h>

void printStackTrace(JNIEnv* env, jobject exception) {
	jclass throwable_class = (*env).FindClass("java/lang/Throwable");
	jmethodID print_method = (*env).GetMethodID(throwable_class, "printStackTrace", "()V");
	(*env).CallVoidMethod(exception, print_method);
}

void JNICALL Callback_JVMTI_EVENT_EXCEPTION (jvmtiEnv *jvmti_env,
	JNIEnv* jni_env,
	jthread thread,
	jmethodID method,
	jlocation location,
	jobject exception,
	jmethodID catch_method,
	jlocation catch_location) {

	printf("loaded class name=%s\n ", "run in Callback_JVMTI_EVENT_EXCEPTION method");
	char* class_name;

	jclass exception_class = jni_env->GetObjectClass(exception);
	jvmti_env->GetClassSignature(exception_class, &class_name, NULL);
	printf("Exception: %s\n", class_name);	

	printStackTrace(jni_env, exception);
}


void JNICALL Callback_JVMTI_EVENT_Exception_Catch (jvmtiEnv *jvmti_env,
	JNIEnv* jni_env,
	jthread thread,
	jmethodID method,
	jlocation location,
	jobject exception)	{

	char* class_name;
	jclass exception_class = jni_env->GetObjectClass(exception);
	jvmti_env->GetClassSignature(exception_class, &class_name, NULL);
	printf("Exception: %s\n", class_name);	

	printStackTrace(jni_env, exception);	
}


JNIEXPORT jint JNICALL Agent_OnLoad(JavaVM *vm, char *options, void *reserved){
	jvmtiEnv *jvmti = NULL;
	
	fprintf(stderr,"agent onload");

	//获取JVMTI environment
	jint erno = vm->GetEnv((void **)&jvmti, JVMTI_VERSION_1_1);
	if (erno != JNI_OK) {
		fprintf(stderr, "ERROR: Couldn't get JVMTI environment");
		return JNI_ERR;
	}
	
	//注册功能
	jvmtiCapabilities capabilities;
	(void)memset(&capabilities, 0, sizeof(jvmtiCapabilities));
	capabilities.can_generate_exception_events=1;

	jvmtiError error = jvmti->AddCapabilities(&capabilities);
	if(error != JVMTI_ERROR_NONE) {
		fprintf(stderr, "ERROR: Unable to AddCapabilities JVMTI");
		return  error;
	}

	/*
	//设置JVM事件 (JVMTI_EVENT_EXCEPTION_CATCH) 回调
	jvmtiEventCallbacks callbacks;
	callbacks.ExceptionCatch = &Callback_JVMTI_EVENT_Exception_Catch;
	error = jvmti->SetEventCallbacks(&callbacks, (jint)sizeof(callbacks));
	if(error != JVMTI_ERROR_NONE) {
		fprintf(stderr, "ERROR: Unable to SetEventCallbacks JVMTI!");		
		return error;
	}

	//设置事件通知
	error = jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_EXCEPTION_CATCH, (jthread)NULL);
	if(error != JVMTI_ERROR_NONE) {
		fprintf(stderr, " ERROR: Unable to SetEventNotificationMode JVMTI!,the error code=%d",error);
		return  error;
	}*/

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	//设置JVM事件 (JVMTI_EVENT_EXCEPTION) 回调
	jvmtiEventCallbacks ex_callbacks;
	ex_callbacks.Exception = &Callback_JVMTI_EVENT_EXCEPTION;
	error = jvmti->SetEventCallbacks(&ex_callbacks, (jint)sizeof(ex_callbacks));
	if(error != JVMTI_ERROR_NONE) {
		fprintf(stderr, "ERROR: Unable to SetEventCallbacks JVMTI!");		
		return error;
	}

	//设置事件通知
	error = jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_EXCEPTION, (jthread)NULL);
	if(error != JVMTI_ERROR_NONE) {
		fprintf(stderr, " ERROR: Unable to SetEventNotificationMode JVMTI!,the error code=%d",error);
		return  error;
	}

	return JNI_OK;
}

JNIEXPORT jint JNICALL
	Agent_OnAttach(JavaVM* vm, char *options, void *reserved){
		//do nothing
		
	return JNI_OK;
}

JNIEXPORT void JNICALL
	Agent_OnUnload(JavaVM *vm){
		//do nothing
	
}