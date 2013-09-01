//
//  ring.cpp
//  Lunarlon_v3
//
//  Created by Francisco Zamorano on 8/31/13.
//
//

#include "ring.h"
//------------------------------------------------------------
void Ring::setup(int _nParticles, ofVec2f _ctr, float _radius, float _springiness, float _distance){
    ctr = _ctr;
    radius = _radius;
    
    //Particles
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
    
    //Springs
    for (int i = 0; i < particles.size(); i++){
		Spring mySpring;
		mySpring.distance		= _distance;
		mySpring.springiness	= _springiness;
		mySpring.particleA = & (particles[i]);
		mySpring.particleB = & (particles[(i+1) % particles.size()]);
        mySpring.color = ofColor(0,0,0);
		springs.push_back(mySpring);
        
        //bFix some points
        particles[0].bFixed = true;
        particles[1].bFixed = true;
        particles[particles.size()-1].bFixed = true;
	}    
}

//------------------------------------------------------------
void Ring::updateForces(vector<ofVec2f>_blobs){
    
    blobs = _blobs;
    
    //Particle interaction
    for (int i=0; i<particles.size(); i++) {
        particles[i].resetForce();
    }
    
    for (int i=0; i<particles.size(); i++) {
//        particles[i].addAttractionForce(blobs[0].x, blobs[0].y,  200, 0.7f); //debugging, just one attached to mouse
    
        for (int n=0; n<blobs.size(); n++) {
            particles[i].addAttractionForce(blobs[n].x, blobs[n].y,  200, 0.7f);
            particles[i].changeColor(blobs[n],100);

        }

        
        for (int j=0; j<i; j++) {
            particles[i].addRepulsionForce(particles[j],p2pForceRadius,p2pForceStrength);
        }
    }
    
    //Springs
    for (int i=0; i<springs.size(); i++) {
        springs[i].update();
    }
    
    for (int i=0; i<particles.size(); i++) {
        particles[i].addDampingForce();
        particles[i].update();
    }

    

}

//------------------------------------------------------------
void Ring::setColor(ofColor _color){
    baseColor = _color;
    
}

//------------------------------------------------------------
void Ring::draw(){
    
    for (int i=0; i<springs.size(); i++) {
        springs[i].draw();
    }
    for (int i=0; i<particles.size(); i++) {
        particles[i].draw();
    }
    
}





