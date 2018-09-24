#jvmti_evt_ex 工程说明#

# 前言 #
借助jvmti提供的异常事件进行相应的扩展，当jvm捕获到异常时，回调的的针对该事件的扩展方法，在该方法体内部调用 printStackTrace 方法，打印异常提示信息。更详细的内容请阅读文章
**[java异常查看利器之使用 jvmti 的Callback_JVMTI_EVENT_EXCEPTION 事件查看异常](https://www.cnblogs.com/yql1986/p/9695319.html "java异常查看利器之使用 jvmti 的Callback_JVMTI_EVENT_EXCEPTION 事件查看异常")**

# 编译和构建工程 #
使用visual studio 打开解决方案，选择相应的JDK头文件，进行编译即可

# JVM Tool Interface #
有关jvmti更详尽的内容，可以查看官方提供的文档。[https://docs.oracle.com/javase/8/docs/platform/jvmti/jvmti.html#Exception](https://docs.oracle.com/javase/8/docs/platform/jvmti/jvmti.html#Exception "jvmti")