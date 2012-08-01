//
//  CameraView.h
//
//  Created by Ian G on 7/31/12.
//

#pragma once

#include "ofxGenericView.h"
#include "ofxGenericTimer.h"
#include "ofxGenericCameraPreviewView.h"

class ofxGenericMicrophone;
class ofxGenericActivityView;

class CameraView : public ofxGenericView, public ofxGenericTimerDelegate, public ofxGenericCameraPreviewViewDelegate
{
public:
    static ofPtr< CameraView > create( const ofRectangle& setFrame );

    virtual void didLoad();
    virtual void willAppear();
    virtual void willDisappear();
    
    void pictureTaken( ofImage& image );
    void timer_fired( ofPtr< ofxGenericTimer > timer );
    
protected:
    CameraView();
    
    ofPtr< ofxGenericTimer > _timer;
    ofPtr< ofxGenericMicrophone > _microphone;
    
    ofPtr< ofxGenericCameraPreviewView > _camera;
    void takePicture();
    ofPtr< ofxGenericActivityView > _currentlyTakingPictureView;
    bool _currentlyTakingPicture;    
};