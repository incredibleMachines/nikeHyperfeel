//
//  user.h
//  lunarlon
//
//  Created by Francisco Zamorano on 9/1/13.
//
//

#ifndef __lunarlon__user__
#define __lunarlon__user__

#include <iostream>
#include "ofMain.h"

class User {
    
public:
    void setup();
    void updatePosition(ofVec2f _pos);
    void draw();
    
    ofMesh mesh;
    int nPoints;
    ofVec2f pos;
    float radius;
    
    
};
#endif /* defined(__lunarlon__user__) */
