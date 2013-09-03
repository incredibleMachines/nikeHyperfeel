//
//  SculptureTouch.h
//  emptyExample
//
//  Created by Joseph Saavedra on 9/3/13.
//
//

#pragma once

#include "ofMain.h"

class Touches { //experiment
public:
    bool touchOn;
    ofVec2f pos;
};

class SculptureTouch {
    
public:
    void setup();
    void update();
    void draw();
    void sendTouch();
    
    bool bTouch;

    vector <ofPolyline> lines;
    vector <ofVec2f> pts;
//    vector <Touches> touches;
};