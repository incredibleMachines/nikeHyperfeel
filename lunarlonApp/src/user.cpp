//
//  user.cpp
//  lunarlon
//
//  Created by Francisco Zamorano on 9/1/13.
//
//

#include "user.h"

void User::setup(){
    nPoints = 12;
    radius = 50;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
}

void User::updatePosition(ofVec2f _pos){
    
    float oscAngle = sin(ofGetElapsedTimef()*2);    
    float radiusOsc = radius + 10*oscAngle;
    
    pos = _pos;
    
    mesh.clear();
    
    ofColor tempColor;
    tempColor.setHsb(100, 255, 200,100);
    
    mesh.addColor(tempColor);
    mesh.addVertex(_pos);
    
    for (int i=0; i<nPoints; i++) {
        float angle = (TWO_PI / nPoints) * i;
        float x = _pos.x + cos(angle) * radiusOsc;
        float y = _pos.y + sin(angle) * radiusOsc;
        
        ofColor tempColor;
        tempColor.setHsb(78, 255, 200,0);
        mesh.addColor(ofColor(tempColor));
        mesh.addVertex(ofVec2f(x,y));
    }
    
    ofColor tempColor2;
    tempColor2.setHsb(78, 255, 200,0);
    mesh.addColor(tempColor2);
    mesh.addVertex(ofVec2f(_pos.x+radiusOsc, _pos.y));
    
}

void User::draw(){
    mesh.draw();
//    mesh.drawWireframe();
}