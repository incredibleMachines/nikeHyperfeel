//
//  ringMaster.cpp
//  lunarlon
//
//  Created by Francisco Zamorano on 8/31/13.
//
//

#include "ringMaster.h"
#include "lunarlon.h" //we include this to get a pointer to main app.Should NOT be included in the .h file!!!

//--------------------------------------------------------------
void RingMaster::setup(){
    // Main Center Position
    centerOfRings.set(ofGetWidth()/2, 50);
    
    
    // Rings init values
    nRings = 49;
    int nParticlesRingZero = 2;
    particleDist = 1;
    particleSpringiness = 0.4;
    float initRadius = 10;
    breathing = 0.03;
    
    for (int i=0; i<nRings; i++) {
        Ring tempRing;
        rings.push_back(tempRing);
    }
    
    for (int i=0; i<rings.size(); i++) {
        rings[i].setup(nParticlesRingZero*i, centerOfRings, initRadius * i, particleSpringiness, particleDist);
        rings[i].p2pForceStrength = 0.4;
        rings[i].p2pForceRadius = 9*i;
    }
    
}

//--------------------------------------------------------------
void RingMaster::update(vector<ofVec2f>_blobs, bool _bTouch){
    blobs.clear(); // do I have to do this?
    blobs = _blobs;
    
    //update blobs positions in rings
    for (int i=0; i<rings.size(); i++) {
        rings[i].updateForces(_blobs);
        rings[i].p2pForceStrength = 0.1  + 0.5 * ((lunarlon*) ofGetAppPtr())->TouchReactionAmt;
        rings[i].touchAmt =  ((lunarlon*) ofGetAppPtr())->TouchReactionAmt;
        float osc = sin(ofGetElapsedTimef()) * breathing * i;
        rings[i].p2pForceRadius += osc;
    }
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

//    ofRect(centerOfRings,10,10);

}

