#include "cloudPlayer.h"

//--------------------------------------------------------------
void cloudPlayer::setup(){
    
    
    if( settings.loadFile("mySettings.xml") ){
		message = "mySettings.xml loaded!";
	}else{
		message = "unable to load mySettings.xml check data/ folder";
	}
    
    gradientCenter=settings.getValue("CENTER",ofGetWidth()/2);


    
    
    
	ofBackground(0,0,0);
	ofSetVerticalSync(true);
    ofSetFrameRate(24);
    
    bFadingOut=false;
    bFadingIn=false;
    fadeOutSpeed=1500;
    fadeInSpeed=500;
    flipHorizontal = false;
    
	// Uncomment this to show movies with alpha channels
	// cloudMovie.setPixelFormat(OF_PIXELS_RGBA);
    
    receiver.setup(PORT);
    
	cloudMovie.loadMovie("movies/"+ofToString(SCREEN)+".mov");
    

    
    //---new controls
    
    selectionColor.set(255, 0, 0);
    
    gradientCenter=settings.getValue("CENTER",ofGetWidth()/2);
    gradientWidth=settings.getValue("WIDTH",100);
    gradientFadeWidth=settings.getValue("FADE",25);
    bMask=settings.getValue("MASK",1);
    
    leftWidth=settings.getValue("LEFTBORDER",90);
    rightWidth=settings.getValue("RIGHTBORDER",90);
    upperWidth=settings.getValue("UPPERBORDER",90);
    lowerWidth=settings.getValue("LOWERBORDER",90);
    
    leftFadeWidth=settings.getValue("LEFTFADE",10);
    rightFadeWidth=settings.getValue("RIGHTFADE",10);
    upperFadeWidth=settings.getValue("UPPERFADE",10);
    lowerFadeWidth=settings.getValue("LOWERFADE",10);
   
    bLeftBorder=settings.getValue("LEFT", 0);
    bRightBorder=settings.getValue("RIGHT", 0);
    bUpperBorder=settings.getValue("UPPER", 0);
    bLowerBorder=settings.getValue("LOWER", 0);
    
    
    
    bWhite=false;
    cout<<message<<endl;
    
    tex.allocate(ofGetWidth(),ofGetHeight(),GL_RGBA);
    
}

//--------------------------------------------------------------
void cloudPlayer::update(){
    if(bFadingOut==false&&cloudMovie.isPlaying()){
        //        cout<< cloudMovie.getDuration()<< " postion: "<<cloudMovie.getPosition()*cloudMovie.getDuration()<<endl;
        if(cloudMovie.getDuration()*1000-cloudMovie.getPosition()*cloudMovie.getDuration()*1000<fadeOutSpeed){
            cout<<"fade"<<endl;
            fadeOut();
        }
    }
    while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        if(m.getAddress()=="/on"){
            
            if(!cloudMovie.isPlaying()){
                cloudMovie.play();
                cloudMovie.setLoopState(OF_LOOP_NONE);
                fadeIn();
            }
            
        }
        else if(m.getAddress()=="/off"){
            
            if(cloudMovie.isPlaying()){
                fadeOut();
            }
            
        }
    }
    
    if(cloudMovie.isPlaying()){
        cloudMovie.update();
    }
}

//--------------------------------------------------------------
void cloudPlayer::draw(){
    
    ofBackground(0,0,0);
    
	ofSetHexColor(0xFFFFFF);
    
    if(cloudMovie.isPlaying()){
        if(bFadingOut==true){
            if(ofGetElapsedTimeMillis()-fadeOutTimer<fadeOutSpeed){
                float color=255-(255*((ofGetElapsedTimeMillis()-fadeOutTimer)/fadeOutSpeed));
                //                cout<<((ofGetElapsedTimeMillis()-fadeOutTimer)/fadeOutSpeed)<<endl;
                ofSetColor(color);
                cloudMovie.draw(0,0);
//                cloudMovie.draw(0, 0, -cloudMovie.getWidth(), cloudMovie.getHeight());
            }
            else{
                cloudMovie.stop();
                cloudMovie.firstFrame();
                bFadingOut=false;
            }
        }
        else if(bFadingIn==true){
            if(ofGetElapsedTimeMillis()-fadeInTimer<fadeInSpeed){
                float color=255*((ofGetElapsedTimeMillis()-fadeInTimer)/fadeInSpeed);
                //                cout<<((ofGetElapsedTimeMillis()-fadeInTimer)/fadeInSpeed)<<endl;
                ofSetColor(color);
                cloudMovie.draw(0,0);
            }
            else{
                ofSetColor(255);
                cloudMovie.draw(0,0);
                bFadingIn=false;
            }
        }
        else{
            cloudMovie.draw(0,0);
        }
        
        
    }
    
    if(bWhite==true){
        ofBackground(255,255,255);
    }
    
    if(bMask==true){
        int startPixel=gradientCenter-gradientWidth/2;
        for(int i=0;i<gradientWidth;i++){
            if(i<gradientFadeWidth){
                int opacity=ofMap(i,0,gradientFadeWidth,0,255);
                ofSetColor(0,0,0,opacity);
                ofLine(startPixel+i,0,startPixel+i,ofGetHeight());
            }
            else if(i>gradientWidth-gradientFadeWidth){
                int opacity=ofMap(i,gradientWidth-gradientFadeWidth,gradientWidth,255,0);
                ofSetColor(0,0,0,opacity);
                ofLine(startPixel+i,0,startPixel+i,ofGetHeight());
            }
            else{
                ofSetColor(0,0,0,255);
                ofLine(startPixel+i,0,startPixel+i,ofGetHeight());
            }
            
        }
    }
    
    //--- borders
    if(bLeftBorder){
        for(int x=0;x<=ofGetWidth();x++){
            if(x<leftWidth-leftFadeWidth){
                
                if (bAdjustLeft) {
                    ofSetColor(selectionColor,255);
                }else{
                    ofSetColor(0,0,0,255);
                }
                ofLine(x,0,x,ofGetHeight());
            }
            else if(x<leftWidth){
                int opacity=ofMap(x,leftWidth-leftFadeWidth,leftWidth,255,0);
                
                if (bAdjustLeft) {
                    ofSetColor(selectionColor,opacity);
                }else{
                    ofSetColor(0,0,0,opacity);
                }

                ofLine(x,0,x,ofGetHeight());
            }
            
        }
    }
    
    if(bRightBorder){
        for(int x=0;x<=ofGetWidth();x++){
            if(x>ofGetWidth()-(rightWidth-rightFadeWidth)){
                if (bAdjustRight) {
                    ofSetColor(selectionColor,255);
                }else{
                    ofSetColor(0,0,0,255);
                }
                ofLine(x,0,x,ofGetHeight());
                
            }
            else if (x>ofGetWidth()-leftWidth){
                int opacity=ofMap(x,ofGetWidth()-rightWidth,ofGetWidth()-(rightWidth-rightFadeWidth),0,255);
                if (bAdjustRight) {
                    ofSetColor(selectionColor,opacity);
                }else{
                    ofSetColor(0,0,0,opacity);
                }
                ofLine(x,0,x,ofGetHeight());
            }
        }
    }
    
    if(bUpperBorder==true){
        for(int y=0;y<=ofGetHeight();y++){
            if(y<upperWidth-upperFadeWidth){
                if (bAdjustUpper) {
                    ofSetColor(selectionColor,255);
                }else{
                    ofSetColor(0,0,0,255);
                }
                ofLine(0,y,ofGetWidth(),y);
            }
            else if(y<upperWidth){
                int opacity=ofMap(y,upperWidth-upperFadeWidth,upperWidth,255,0);
                if (bAdjustUpper) {
                    ofSetColor(selectionColor,opacity);
                }else{
                    ofSetColor(0,0,0,opacity);
                }
                ofLine(0,y,ofGetWidth(),y);
            }            
        }
    }
    
    
    if(bLowerBorder==true){
        for(int y=0;y<=ofGetHeight();y++){
            if(y>ofGetHeight()-(lowerWidth-lowerFadeWidth)){
                if (bAdjustLower) {
                    ofSetColor(selectionColor,255);
                }else{
                    ofSetColor(0,0,0,255);
                }

                ofLine(0,y,ofGetWidth(),y);
                
            }
            else if (y>ofGetHeight()-lowerWidth){
                int opacity=ofMap(y,ofGetHeight()-lowerWidth,ofGetHeight()-(lowerWidth-lowerFadeWidth),0,255);
                if (bAdjustLower) {
                    ofSetColor(selectionColor,opacity);
                }else{
                    ofSetColor(0,0,0,opacity);
                }
                ofLine(0,y,ofGetWidth(),y);
            }
        }
    }

    


    
    
    
    
    //--- syphon
    tex.loadScreenData(0, 0, ofGetWidth(), ofGetHeight());
    individualTextureSyphonServer.publishTexture(&tex);
    ofSetColor(255);
    
}

//--------------------------------------------------------------
void cloudPlayer::fadeOut(){
    bFadingOut=true;
    fadeOutTimer=ofGetElapsedTimeMillis();
}
//--------------------------------------------------------------
void cloudPlayer::fadeIn(){
    bFadingIn=true;
    fadeInTimer=ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void cloudPlayer::keyPressed  (int key){
    switch(key){
        case 'm':
            bMask=!bMask;
            break;
 
        case '1':
            bLeftBorder=!bLeftBorder;
            break;
        case '2':
            bRightBorder=!bRightBorder;
            break;
        case '3':
            bUpperBorder=!bUpperBorder;
            break;
        case '4':
            bLowerBorder=!bLowerBorder;
            break;
            
            
        case 'f':
            flipHorizontal = !flipHorizontal;
            break;
 
        case 'q':
            bAdjustLeft = !bAdjustLeft;
            bAdjustRight = false;
            bAdjustUpper = false;
            bAdjustLower = false;

            break;
        case 'w':
            bAdjustRight = !bAdjustRight;
            bAdjustLeft = false;
            bAdjustUpper = false;
            bAdjustLower = false;
            break;
        case 'e':
            bAdjustUpper = !bAdjustUpper;
            bAdjustLeft = false;
            bAdjustRight = false;
            bAdjustLower = false;
            break;
        case 'r':
            bAdjustLower = !bAdjustLower;
            bAdjustLeft = false;
            bAdjustRight = false;
            bAdjustUpper = false;
            break;
 
        case 'M':
            //            bMask=true;
            //            bHorizBorder=true;
            //            bVertBorder=true;
            bWhite=!bWhite;
            break;
        case OF_KEY_RIGHT:
            gradientCenter++;
            break;
        case OF_KEY_UP:
            gradientCenter+=10;
            break;
        case OF_KEY_LEFT:
            gradientCenter--;
            break;
        case OF_KEY_DOWN:
            gradientCenter-=10;
            break;

        
        case '-':
            if(bAdjustLeft==true){
                leftWidth--;
            }
            else if(bAdjustRight==true){
                rightWidth--;
            }
            else if(bAdjustUpper==true){
                upperWidth--;
            }
            else if(bAdjustLower==true){
                lowerWidth--;
            }
            else{
                gradientWidth--;
            }
            break;
        
        case '=':
            if(bAdjustLeft==true){
                leftWidth++;
            }
            else if(bAdjustRight==true){
                rightWidth++;
            }
            else if(bAdjustUpper==true){
                upperWidth++;
            }
            else if(bAdjustLower==true){
                lowerWidth++;
            }
            else{
                gradientWidth++;
            }
            break;
            
        case '[':
            if(bAdjustLeft==true){
                leftFadeWidth--;
            }
            else if(bAdjustRight==true){
                rightFadeWidth--;
            }
            else if(bAdjustUpper==true){
                upperFadeWidth--;
            }
            else if(bAdjustLower==true){
                lowerFadeWidth--;
            }
            else{
                gradientFadeWidth--;
            }
            break;
            
            
        case ']':
            if(bAdjustLeft==true){
                leftFadeWidth++;
            }
            else if(bAdjustRight==true){
                rightFadeWidth++;
            }
            else if(bAdjustUpper==true){
                upperFadeWidth++;
            }
            else if(bAdjustLower==true){
                lowerFadeWidth++;
            }
            else{
                gradientFadeWidth++;
            }
            break;
 
        case ' ':
            settings.setValue("WIDTH",gradientWidth);
            settings.setValue("CENTER",gradientCenter);
            settings.setValue("FADE", gradientFadeWidth);
            settings.setValue("MASK",bMask);
            
            settings.setValue("LEFTBORDER",leftWidth);
            settings.setValue("RIGHTBORDER",rightWidth);
            settings.setValue("UPPERBORDER",upperWidth);
            settings.setValue("LOWERBORDER",lowerWidth);
            
            settings.setValue("LEFTFADE",leftFadeWidth);
            settings.setValue("RIGHTFADE",rightFadeWidth);
            settings.setValue("UPPERFADE",upperFadeWidth);
            settings.setValue("LOWERFADE",lowerFadeWidth);
            
            settings.setValue("LEFT",bLeftBorder);
            settings.setValue("RIGHT", bRightBorder);
            settings.setValue("UPPER", bUpperBorder);
            settings.setValue("LOWER", bLowerBorder);
            settings.save("mySettings.xml");
            break;
        case 'p':  
                if(!cloudMovie.isPlaying()){
                    cloudMovie.play();
                    cloudMovie.setLoopState(OF_LOOP_NONE);
                    fadeIn();
                }
            break;
                
        
    }
}

//--------------------------------------------------------------
void cloudPlayer::keyReleased(int key){
    switch(key){
        case 'p':
            if(cloudMovie.isPlaying()){
                fadeOut();
            }
            break;
    }

}

//--------------------------------------------------------------
void cloudPlayer::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void cloudPlayer::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void cloudPlayer::mousePressed(int x, int y, int button){
    
}


//--------------------------------------------------------------
void cloudPlayer::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void cloudPlayer::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void cloudPlayer::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void cloudPlayer::dragEvent(ofDragInfo dragInfo){ 
    
}
