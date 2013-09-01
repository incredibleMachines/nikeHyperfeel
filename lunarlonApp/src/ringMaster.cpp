//
//  ringMaster.cpp
//  lunarlon
//
//  Created by Francisco Zamorano on 8/31/13.
//
//

#include "ringMaster.h"

//--------------------------------------------------------------
void RingMaster::setup(){
    // Main Center Position
    centerOfRings.set(ofGetWidth()/2, 50);
    
    //Touch Controls
    bTouch = false;
    counter = 0;
    touchReactionSpeed = 0.05;
    bTimerReached = false;
    bStartCount = false;
    
    //Rings
    nRings = 35;
    int nParticlesRingZero = 4;
    particleDist = 1;
    particleSpringiness = 0.7;
    float initRadius = 10;
    
    for (int i=0; i<nRings; i++) {
        Ring tempRing;
        rings.push_back(tempRing);
    }
    
    for (int i=0; i<rings.size(); i++) {
        rings[i].setup(10*i, centerOfRings, initRadius * i, particleSpringiness, particleDist);
    }

}

//--------------------------------------------------------------
void RingMaster::update(vector<ofVec2f>_blobs, bool _bTouch){
    bTouch = _bTouch;
    blobs.clear(); // do I have to do this?
    blobs = _blobs;

}

//--------------------------------------------------------------
void RingMaster::draw(){
            
    //Rings
    for (int i=0; i<rings.size(); i++) {
        rings[i].draw();
    }
    
    //Draw blob points
    for (int i=0; i<blobs.size(); i++) {
        ofColor color;
        color.setHsb(50, 255, 255);
        ofSetColor(color);
        ofCircle(blobs[i], 5);
    }
}

//--------------------------------------------------------------
float RingMaster::touch(){
        
    if (bTouch) {
        bStartCount = true;
    }
    
    if (bStartCount && !bTimerReached) {
        counter+=touchReactionSpeed;
    }
    
    if (counter>=1) {
        bTimerReached = true;
    }
    
    if(bStartCount && bTimerReached){
        counter-=touchReactionSpeed;
        if (counter<=0) {
            bStartCount = false;
            bTimerReached = false;
            bTouch = false;
        }
    }
    return counter;
}