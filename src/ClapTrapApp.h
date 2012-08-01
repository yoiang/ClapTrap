//
//  ClapTrapApp.h
//
//  Created by Ian G on 7/31/12.
//

#pragma once

#include "ofxGenericApp.h"

#include "ofxGenericUtility.h"

#include "ofMain.h"

class ClapTrapApp : public ofxGenericApp
{
public:
	void setup();

public:
    virtual ~ClapTrapApp();
    static ofPtr< ClapTrapApp > getInstance();

protected:
    ClapTrapApp();
    static ofPtr< ClapTrapApp > _this;
    void setClapTrapAppInstanceToThis();
};


