# jvmti-t #
```java
package com.github.torlight.jvmtit;

/**
 * Hello world!
 *
 */
public class App {
	
    public static void main( String[] args ){
    	
        System.out.println( "Hello World!" );
      
        try {
			throw new NullPointerException("QQQ");
		} catch (Exception e) {
			
		}	
    }
}
```

故意抛出并捕获异常，用于测试jvmti Callback_JVMTI_EVENT_EXCEPTION事件。