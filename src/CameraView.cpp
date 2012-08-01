//
//  CameraView.cpp
//
//  Created by Ian G on 7/31/12.
//

#include "CameraView.h"

#include "ofxGenericTimer.h"
#include "ofxGenericMicrophone.h"
#include "ofxGenericActivityView.h"

ofPtr< CameraView > CameraView::create( const ofRectangle& setFrame )
{
    ofPtr< CameraView > view( new CameraView() );
    view->init( view, setFrame );
    return view;
}

CameraView::CameraView()
: _currentlyTakingPicture( false )
{
    
}

void CameraView::didLoad()
{
    ofxGenericView::didLoad();
    setBackgroundColor( ofColor( 0, 0, 0 ) );
    setAutoresizingMask( ofxGenericViewAutoresizingFull );

    _microphone = ofxGenericMicrophone::create();

    _camera = ofxGenericCameraPreviewView::create( dynamic_pointer_cast< ofxGenericCameraPreviewViewDelegate >( _this ), getFrame( ofPoint( 0, 0 ) ) );
    _camera->setAutoresizingMask( ofxGenericViewAutoresizingFull );
    addChildView( _camera );
    
    _currentlyTakingPictureView = ofxGenericActivityView::create( ofRectangle( 20, 40, 20, 20 ) );
    _currentlyTakingPictureView->setColor( ofColor( 0, 0, 0 ) );
    _currentlyTakingPictureView->setHidesWhenStoppedAnimating( true );
    addChildView( _currentlyTakingPictureView );
}

void CameraView::willAppear()
{
    ofxGenericView::willAppear();
    _timer = ofxGenericTimer::create( 0.05f, true, dynamic_pointer_cast< ofxGenericTimerDelegate >( _this ) );
    _microphone->start();
}

void CameraView::willDisappear()
{
    ofxGenericView::willDisappear();
    _microphone->stop();
    _timer->stop();
    _timer = ofPtr< ofxGenericTimer >();
}

void CameraView::timer_fired( ofPtr< ofxGenericTimer > timer )
{
    if ( _microphone )
    {
        float power = _microphone->getAveragePowerForChannel( 0 );
        float normalizedPower = _microphone->normalizePower( power );
        _camera->setAlpha( normalizedPower );
        ofxGLogVerbose( ofxGToString( power ) + " " + ofxGToString( normalizedPower ) );
        
        if ( normalizedPower > 0.9 )
        {
            takePicture();
        }
    }
}

void CameraView::takePicture()
{
    if ( !_currentlyTakingPicture )
    {
        _currentlyTakingPictureView->startAnimating();
        _camera->takePicture();
    }
}

void CameraView::pictureTaken( ofImage& image )
{
    _currentlyTakingPicture = false;
    ofxGenericApp::saveImageToLibrary( image );
    _currentlyTakingPictureView->stopAnimating();
}
