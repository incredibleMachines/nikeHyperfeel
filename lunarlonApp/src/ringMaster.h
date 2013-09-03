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
    
    float touch(); //touch reaction triggering function
    
    // Rings
    vector<Ring>rings;
    ofVec2f centerOfRings;
    int nRings;

    // Particles
    float particleDist;
    float particleSpringiness;
    
    // Touch Controls
    bool bTouch;
    vector<ofVec2f>blobs;
    float startTime;
    float endTime;
    bool bTimerReached;
    float counter;
    bool bStartCount;
    float touchReactionSpeed;
    
};

#endif /* defined(__lunarlon__ringMaster__) */
