//
//  spring.cpp
//  Lunarlon_v2
//
//  Created by Francisco Zamorano on 8/24/13.
//
//

#include "spring.h"

//------------------------------------------
Spring::Spring(){
    particleA = NULL;
    particleB = NULL;
    lineThickness = 1.5f;
}

//------------------------------------------
void Spring::update(){
    
    if (particleA == NULL || particleB ==NULL) {
        return;
    }
    
    ofVec2f pta = particleA->pos;
    ofVec2f ptb = particleB->pos;
    
    float particleDist = (pta-ptb).length();
    float springForce = (springiness * (distance - particleDist));
    frcToAdd = (pta-ptb).normalized()*springForce;
    
    particleA->addForce(frcToAdd.x, frcToAdd.y);
    particleB->addForce(-frcToAdd.x, -frcToAdd.y);
    
    
}

//------------------------------------------
void Spring::draw(){
    
    if (particleA == NULL || particleB ==NULL) {
        return;
    }
    
    ofPushStyle;
    ofSetLineWidth(lineThickness);
    ofSetColor(color);
    ofLine(particleA->pos,particleB->pos);
    ofPopStyle;
}

