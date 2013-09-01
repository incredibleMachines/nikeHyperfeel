#include "lunarlon.h"

//--------------------------------------------------------------
void lunarlon::setup(){
    ofSetVerticalSync(true);
//    ofEnableSmoothing();
    ofSetFrameRate(60);
    int nRings;
    int nParticlesringZero;
    
    //Background
    ofBackground(0);
    bg.loadImage("bg_1.jpg");
    

    
    //Dummy blob points, remove when CV is implemeted !!
    for(int i=0; i< 6;i++){
        ofVec2f temp;
        temp.set(ofRandom(ofGetWidth()), ofRandom(100,ofGetHeight()));
        blobPoints.push_back(temp);
    }
    
    //RingMaster
    ringmaster.setup();

}

//--------------------------------------------------------------
void lunarlon::update(){
    
    blobPoints[0] = ofVec2f(mouseX, mouseY);
    ringmaster.update(blobPoints, false); //using Dummy points until CV blobs are implemented

}

//--------------------------------------------------------------
void lunarlon::draw(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    bg.draw(0,0);
    ringmaster.draw();

}



//--------------------------------------------------------------
void lunarlon::keyPressed(int key){

    switch (key) {
        case 't':
            
            
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