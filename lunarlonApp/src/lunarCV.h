//
//  lunarCV.h
//  lunarlon
//
//  Created by Joseph Saavedra on 9/2/13.
//
//

#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class lunarCV {
public:
    void setup();
    void update();
    void draw();
    
    
};

class Blob {
public:
    ofxCvBlob blob;
    ofPoint closest;
    int centroidDist;
};