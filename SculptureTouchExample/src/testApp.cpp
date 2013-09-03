#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    sculpture.setup();
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    //--- make some fake blobs
    int nMouseBlobs = 1;
    blobPoints.clear();
    for (int i=0; i<nMouseBlobs; i++){
        ofPoint mouse;
        if(i == 0){
            mouse.x = mouseX;
            mouse.y = mouseY;
        } else if (i==1){
            mouse.x = ofGetWidth() - mouseX;
            mouse.y = ofGetHeight() - mouseY;
        } else if (i==2){
            mouse.x = ofGetWidth() - mouseX;
            mouse.y = mouseY;
        } else if(i ==3){
            mouse.x = mouseX;
            mouse.y = ofGetHeight() - mouseY;
        } else break;
        blobPoints.push_back(mouse);
    }
    
    //--- update
    sculpture.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(10, 10, 10);
    
    //--- draw sculpture
    sculpture.draw();
    
    
    //--- draw blobs
    for (int i=0; i<blobPoints.size(); i++){
        ofFill();
        ofSetColor(255, 255, 255);
        ofEllipse(blobPoints[i], 10, 10);
        
    }

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}