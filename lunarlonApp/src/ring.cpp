//
//  ring.cpp
//  Lunarlon_v3
//
//  Created by Francisco Zamorano on 8/31/13.
//
//

#include "ring.h"

void Ring::setup(int _nParticles, ofVec2f _ctr, float _radius, float _springiness, float _distance){
    ctr = _ctr;
    radius = _radius;
    nParticles = _nParticles;    
    for (int i = 0; i < _nParticles; i++){
        particle myParticle;
        float ang = (TWO_PI/nParticles) * i + HALF_PI*3;
        float x = _ctr.x + cos(ang) * _radius;
        float y = (_ctr.y + sin(ang) * _radius)+_radius;
        
        myParticle.setInitialCondition(x,y,0,0,0.3);
        myParticle.color.setHsb(78, 50 , 200, 200);
        particles.push_back(myParticle);
    }
}

void Ring::setColor(ofColor _color){
    baseColor = _color;
    
}

void Ring::draw(){    
    for (int i=0; i<particles.size(); i++) {
        particles[i].draw();
    }
    
}





