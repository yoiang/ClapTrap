//
//  ClapTrapApp.cpp
//
//  Created by Ian G on 7/31/12.
//

#include "ClapTrapApp.h"
#include "CameraView.h"
#include "ofxGenericException.h"

ClapTrapApp::ClapTrapApp()
{
}

ClapTrapApp::~ClapTrapApp()
{
}

void ClapTrapApp::setup()
{	
    ofxGenericApp::setup();
    
    ofPtr< ofxGenericView > rootView = getRootView();
    if ( rootView )
    {
        rootView->addChildView( CameraView::create( _window->getFrame() ) );
    }
}

ofPtr< ClapTrapApp > ClapTrapApp::_this;

ofPtr< ClapTrapApp > ClapTrapApp::getInstance()
{
    if ( !ClapTrapApp::_this )
    {
        ( new ClapTrapApp() )->setClapTrapAppInstanceToThis();
    }
    return ClapTrapApp::_this;
}

void ClapTrapApp::setClapTrapAppInstanceToThis()
{
    if ( !ClapTrapApp::_this )
    {
        ClapTrapApp::_this = ofPtr< ClapTrapApp >( this );
        ClapTrapApp::_this->setofxGenericAppInstanceToThis();
    } else
    {
        throw ofxGenericExceptionSubclassedSingletonInitializedTwice( "ofxGenericApp" );        
    }
}

