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
    touchAmt = 0;
    
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
        mySpring.color.setHsb(78, 50 , 200, 100);
		springs.push_back(mySpring);
        
        //bFix some points
        particles[0].bFixed = true;
        particles[1].bFixed = true;
        particles[particles.size()-1].bFixed = true;
	}
    
    // Mesh Mode (For Spring Fills)
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
}

//------------------------------------------------------------
void Ring::updateForces(vector<ofVec2f>_blobs){
    
    blobs = _blobs;
    
    // Reset Particles
    for (int i=0; i<particles.size(); i++) {
        particles[i].resetForce();
    }
    
    // Clear Mesh
    for (int i=0; i<particles.size(); i++) {
        mesh.clear();
    }
    
    // Particle forces update
    for (int i=0; i<particles.size(); i++) {
        
        //Incoming forces from blobs
        for (int n=0; n<blobs.size(); n++) {
            particles[i].addAttractionForce(blobs[n].x, blobs[n].y,  200, 0.7f);
            particles[i].changeColor(blobs[n],100);
        }
        
        //Particle-to-particle forces
        for (int j=0; j<i; j++) {
            particles[i].addRepulsionForce(particles[j],p2pForceRadius,p2pForceStrength);
        }
    }
    
    // Create Mesh
    for (int i=0; i<particles.size(); i++) {
        ofColor tempColor;
        tempColor.setHsb(120 - 0.4*i + 50*touchAmt, 255-i/2, 255-i,5);
        mesh.addColor(tempColor);
        mesh.addVertex(particles[i].pos);
    }
    
    // Springs update
    for (int i=0; i<springs.size(); i++) {
        springs[i].update();
        ofColor tempColor;
        tempColor.setHsb(78 - 0.3*i - 40*touchAmt, 255, 255,200);

        springs[i].color = tempColor;
    }
    
    // Particle update. This should go at the end--Important!!
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
    mesh.draw();
    
    for (int i=0; i<springs.size(); i++) {
        springs[i].draw();
    }
    for (int i=0; i<particles.size(); i++) {
        particles[i].draw();
    }
    
//    mesh.drawWireframe();
    
}





