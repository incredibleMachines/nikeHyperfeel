#include "lunarlon.h"

//--------------------------------------------------------------
void lunarlon::setup(){
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofSetFrameRate(60);
    int nRings;
    int nParticlesringZero;
    
    //Background
    ofBackground(0);
    bg.loadImage("bg_1.jpg");
    
    // Main Center Position
    centerOfRings.set(ofGetWidth()/2, 100);
    
    //Touch Controls
    bTouch = false;
    counter = 0;
    touchReactionSpeed = 0.05;
    bTimerReached = false;
    bStartCount = false;
    
    //Blobs
    int nPlayers = 6; //for debugging. This will be replaced by the incoming blob points in CV
    for (int i=0; i<nPlayers; i++) {
        ofPoint temp;
        temp.set(ofRandom(ofGetHeight()), ofRandom(ofGetHeight()));
        blobs.push_back(temp);
    }
    
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

    for (int i=0; i<nRings; i++) {
        rings[i].setup(10*i, centerOfRings, initRadius * i, particleSpringiness, particleDist);
    }
    
    
    
}

//--------------------------------------------------------------
void lunarlon::update(){


}

//--------------------------------------------------------------
void lunarlon::draw(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    bg.draw(0,0);
    ofCircle(centerOfRings, 5);
    
    
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
float lunarlon::touch(){
    
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

//--------------------------------------------------------------
void lunarlon::keyPressed(int key){

    switch (key) {
        case 't':
            bTouch = !bTouch;
        default:
            break;
    }
}

//--------------------------------------------------------------
void lunarlon::keyReleased(int key){

}

//--------------------------------------------------------------
void lunarlon::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void lunarlon::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void lunarlon::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void lunarlon::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void lunarlon::windowResized(int w, int h){

}

//--------------------------------------------------------------
void lunarlon::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void lunarlon::dragEvent(ofDragInfo dragInfo){ 

}