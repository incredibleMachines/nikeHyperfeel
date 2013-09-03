//
//  SculptureTouch.cpp
//  emptyExample
//
//  Created by Joseph Saavedra on 9/3/13.
//
//

#include "SculptureTouch.h"
#include "lunarlon.h"

//--------------------------------------------------------------
void SculptureTouch::setup(){

    //--- OFFSETS FOR SCULPTURE
    int xOffset = 200;
    int yOffset = 0;
    
    //--- raw drawscript "ofShape" output:
//    ofFill();
//    ofSetColor(255,255,255);
//    ofBeginShape();
//    ofVertex(411,0);
//    ofVertex(227,0);
//    ofBezierVertex(227,0,204,61,266,63);
//    ofBezierVertex(292,64,333,52,358,71);
//    ofBezierVertex(380,88,435,70,411,0);
//    ofEndShape();
//    
    

    // TODO: output drawscript as JSON,
    //       build JSON parser and do this dynamically:
    
    lines.clear();
    ofPolyline line;
    line.setClosed(true);
    line.addVertex(411+xOffset,0+yOffset);
    line.addVertex(227+xOffset,0+yOffset);
    line.bezierTo(227+xOffset,0+yOffset,204+xOffset,61+yOffset,266+xOffset,63+yOffset);
    line.bezierTo(292+xOffset,64+yOffset,333+xOffset,52+yOffset,358+xOffset,71+yOffset);
    line.bezierTo(380+xOffset,88+yOffset,435+xOffset,70+xOffset,411+xOffset,0+yOffset);
    line.simplify();
    lines.push_back(line);
    
    ofFill();   
}

//--------------------------------------------------------------
void SculptureTouch::update(){
    
    pts = ((lunarlon *)ofGetAppPtr())->blobPoints; //update vector of all current points (blob positions)
    cout<<"pts.size(): "<<pts.size()<<endl;
    
    for (int j=0; j<pts.size(); j++){
        cout<<"j: "<<j<<"  pts.x: "<<pts[j].x<<endl;
        cout<<"j: "<<j<<"  pts.y: "<<pts[j].y<<endl;
        
        //for (int i=0; i<lines.size(); i++){
            if (ofInsidePoly(pts[j],lines[0].getVertices())){
                
                ((lunarlon *)ofGetAppPtr())->bTouch = true;
                //((lunarlon *)ofGetAppPtr())->sendTouch();
                
            } else {
                ((lunarlon *)ofGetAppPtr())->bTouch = false;
                //((lunarlon *)ofGetAppPtr())->sendOff();
            }
        //}
    }
}

//--------------------------------------------------------------
void SculptureTouch::draw(){
    
    bool currTouchState = ((lunarlon *)ofGetAppPtr())->bTouch;
    
    if(currTouchState){
        ofSetColor(255);
        ofDrawBitmapString("TOUCH ON", 50,50);

        ofSetColor(200, 50, 50);
    } else {
        ofSetColor(50, 50, 200);
    }
        
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