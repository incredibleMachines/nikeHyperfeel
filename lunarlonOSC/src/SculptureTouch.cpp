//
//  SculptureTouch.cpp
//  emptyExample
//
//  Created by Joseph Saavedra on 9/3/13.
//
//

#include "SculptureTouch.h"
#include "lunarlonStatue.h"

//--------------------------------------------------------------
void SculptureTouch::setup(){
    int xOffset = 100;
    int yOffset = 0;

    //Create mask points
    lines.clear();
    ofPolyline line;
    line.setClosed(true);
    
    line.addVertex(426,417);
    line.addVertex(653,417);
    line.addVertex(653,358);
    line.addVertex(632,189);
    line.addVertex(693,114);
    line.addVertex(693,35);
    line.addVertex(386,35);
    line.addVertex(386,104);
    line.addVertex(444,189);
    line.addVertex(426,352);

    lines.push_back(line);

    ofFill();   
}

//--------------------------------------------------------------
void SculptureTouch::update(){
    
    pts = ((lunarlonStatue *)ofGetAppPtr())->blobPoints; //update vector of all current points (blob positions)
//    cout<<"pts.size(): "<<pts.size()<<endl;
    
    for (int j=0; j<pts.size(); j++){
//        cout<<"j: "<<j<<"  pts.x: "<<pts[j].x<<endl;
//        cout<<"j: "<<j<<"  pts.y: "<<pts[j].y<<endl;
        
        //for (int i=0; i<lines.size(); i++){
        if (ofInsidePoly(pts[j],lines[0].getVertices())){
            
            ((lunarlonStatue *)ofGetAppPtr())->bTouched = true;
            ((lunarlonStatue *)ofGetAppPtr())->sendTouch();
            
        } else {
            ((lunarlonStatue *)ofGetAppPtr())->bTouched = false;
            ((lunarlonStatue *)ofGetAppPtr())->sendOff();
        }
        //}
    }
}

//--------------------------------------------------------------
void SculptureTouch::draw(ofColor color){
    if(bTouch){
        ofSetColor(255);
        ofDrawBitmapString("TOUCH ON", 50,50);
    }
    
            ofSetColor(color);
        
    for(int i=0; i<lines.size(); i++){
        ofBeginShape();
        for( int j = 0; j < lines[i].getVertices().size(); j++) {
            ofVertex(lines[i].getVertices().at(j).x, lines[i].getVertices().at(j).y);
        }
        ofEndShape();
    }
}


//--------------------------------------------------------------
void SculptureTouch::sendTouch(){
    
    
}