//
//  SculptureTouch.cpp
//  emptyExample
//
//  Created by Joseph Saavedra on 9/3/13.
//
//

#include "SculptureTouch.h"
#include "testApp.h"

//--------------------------------------------------------------
void SculptureTouch::setup(){
    int xOffset = 100;
    int yOffset = 0;
    
    //    //--- raw drawscript "ofShape" output:
    //    ofFill();
    //    ofSetColor(255,255,255);
    //    ofBeginShape();
    //    ofVertex(598,0);
    //    ofVertex(231,0);
    //    ofBezierVertex(231,0,186,123,310,127);
    //    ofBezierVertex(360,129,443,104,492,142);
    //    ofBezierVertex(536,177,646,141,598,0);
    //    ofEndShape();
    
    // TODO: output drawscript as JSON,
    //       build JSON parser and do this dynamically:
    
    lines.clear();
    ofPolyline line;
    line.setClosed(true);
    line.addVertex(598+xOffset,0+yOffset);
    line.addVertex(231+xOffset,0+yOffset);
    line.bezierTo(231+xOffset,0+yOffset,186+xOffset,123+yOffset,310+xOffset,127+yOffset);
    line.bezierTo(360+xOffset,129+yOffset,443+xOffset,104+yOffset,492+xOffset,142+yOffset);
    line.bezierTo(536+xOffset,177+yOffset,646+xOffset,141+xOffset,598+xOffset,0+yOffset);
    line.simplify();
    lines.push_back(line);
    
    ofFill();   
}

//--------------------------------------------------------------
void SculptureTouch::update(){
    
    pts = ((testApp *)ofGetAppPtr())->blobPoints; //update vector of all current points (blob positions)
    cout<<"pts.size(): "<<pts.size()<<endl;
    
    for (int j=0; j<pts.size(); j++){
                
        for (int i=0; i<lines.size(); i++){
            if (ofInsidePoly(pts[j],lines[i].getVertices())){

                bTouch = true;
                
                // >>> SEND TOUCH EVENT HERE
                
            } else {
                bTouch = false;
            }
        }
    }
}

//--------------------------------------------------------------
void SculptureTouch::draw(){
    if(bTouch){
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