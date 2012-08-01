//
//  main.cpp
//
//  Created by Ian G on 7/31/12.
//

#include "ofMain.h"

#include "ClapTrapApp.h"
#include "ofxAppGenericWindow.h"

int main()
{
#if TARGET_OS_IPHONE
    NSAutoreleasePool* pool = [ [ NSAutoreleasePool alloc ] init];
#endif

//#ifdef DEBUG
    ofSetLogLevel( OF_LOG_VERBOSE );
//#else
//    ofSetLogLevel( OF_LOG_ERROR );
//#endif
    
    ofxGLogVerbose( "Starting app..." );

    ofPtr< ClapTrapApp > app( ClapTrapApp::getInstance() );
    ofPtr< ofAppBaseWindow > window( new ofxAppGenericWindow() );
    
    // TODO: don't use ofSetupOpenGL
    ofSetupOpenGL( window, 1024, 768, OF_FULLSCREEN );
	ofRunApp( app );
    
#if TARGET_OS_IPHONE
    [ pool release ];    
#endif
}

#ifdef TARGET_ANDROID
#include <jni.h>
extern "C"
{
	void Java_cc_openframeworks_ofxGeneric_Activity_Main( JNIEnv* env, jobject thiz )
	{
		ofLLog( OF_LOG_VERBOSE, "In Main(): %d", env );
		main();
	}
}
#endif
