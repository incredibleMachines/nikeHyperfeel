//
//  ringMaster.h
//  lunarlon
//
//  Created by Francisco Zamorano on 8/31/13.
//
//

#ifndef __lunarlon__ringMaster__
#define __lunarlon__ringMaster__

#include <iostream>
#include "ofMain.h"
#include "ring.h"
#include "ofxSyphon.h"

class RingMaster {
    
    
public:
    void setup();
    void update(vector<ofVec2f>_blobs, bool _bTouch);
    void draw();
    
    // Rings
    vector<Ring>rings;
    ofVec2f centerOfRings;
    int nRings;

    // Particles
    float particleDist;
    float particleSpringiness;
    
    // Blob positions
    vector<ofVec2f>blobs;
    
    // Animation
    float breathing;

};

#endif /* defined(__lunarlon__ringMaster__) */
