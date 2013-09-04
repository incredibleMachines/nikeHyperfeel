#include "cloudPlayer.h"

//--------------------------------------------------------------
void cloudPlayer::setup(){
    
    
    if( settings.loadFile("mySettings.xml") ){
		message = "mySettings.xml loaded!";
	}else{
		message = "unable to load mySettings.xml check data/ folder";
	}
    
    gradientCenter=settings.getValue("CENTER",ofGetWidth()/2);
    gradientWidth=settings.getValue("WIDTH",100);
    gradientFadeWidth=settings.getValue("FADE",25);
    horizWidth=settings.getValue("HORIZBORDER",90);
    horizFadeWidth=settings.getValue("HORIZFADE",25);
    vertWidth=settings.getValue("VERTBORDER",90);
    vertFadeWidth=settings.getValue("VERTFADE",25);
    
	ofBackground(0,0,0);
	ofSetVerticalSync(true);
    ofSetFrameRate(24);
    
    bFadingOut=false;
    bFadingIn=false;
    fadeOutSpeed=1500;
    fadeInSpeed=500;

	// Uncomment this to show movies with alpha channels
	// cloudMovie.setPixelFormat(OF_PIXELS_RGBA);
    
    receiver.setup(PORT);

	cloudMovie.loadMovie("movies/"+ofToString(SCREEN)+".mov");
    
    bMask=settings.getValue("MASK",1);
    bHorizBorder=settings.getValue("HORIZ",0);
    bVertBorder=settings.getValue("VERT",0);
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
    
    if(bVertBorder==true){
        for(int x=0;x<=ofGetWidth();x++){
            if(x<vertWidth-vertFadeWidth){
                ofSetColor(0,0,0,255);
                ofLine(x,0,x,ofGetHeight());
            }
            else if(x<vertWidth){
                int opacity=ofMap(x,vertWidth-vertFadeWidth,vertWidth,255,0);
                ofSetColor(0,0,0,opacity);
                ofLine(x,0,x,ofGetHeight());
            }
            else if(x>ofGetWidth()-(vertWidth-vertFadeWidth)){
                ofSetColor(0,0,0,255);
                ofLine(x,0,x,ofGetHeight());

            }
            else if (x>ofGetWidth()-vertWidth){
                int opacity=ofMap(x,ofGetWidth()-vertWidth,ofGetWidth()-(vertWidth-vertFadeWidth),0,255);
                ofSetColor(0,0,0,opacity);
                ofLine(x,0,x,ofGetHeight());
            }
            
        }
    }
    if(bHorizBorder==true){
        for(int y=0;y<=ofGetHeight();y++){
            if(y<horizWidth-horizFadeWidth){
                ofSetColor(0,0,0,255);
                ofLine(0,y,ofGetWidth(),y);
            }
            else if(y<horizWidth){
                int opacity=ofMap(y,horizWidth-horizFadeWidth,horizWidth,255,0);
                ofSetColor(0,0,0,opacity);
                ofLine(0,y,ofGetWidth(),y);
            }
            else if(y>ofGetHeight()-(horizWidth-horizFadeWidth)){
                ofSetColor(0,0,0,255);
                ofLine(0,y,ofGetWidth(),y);
                
            }
            else if (y>ofGetHeight()-horizWidth){
                int opacity=ofMap(y,ofGetHeight()-horizWidth,ofGetHeight()-(horizWidth-horizFadeWidth),0,255);
                ofSetColor(0,0,0,opacity);
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
        case 'b':
            bHorizBorder=!bHorizBorder;
            break;
        case 'B':
            bVertBorder=!bVertBorder;
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
        case OF_KEY_LEFT_CONTROL:
            bAdjustHoriz=true;
            break;
        case OF_KEY_LEFT_ALT:
            bAdjustVert=true;
            break;
        case '=':
            if(bAdjustHoriz==true){
                horizWidth++;
            }
            else if(bAdjustVert==true){
                vertWidth++;
            }
            else{
                gradientWidth++;
            }
            break;
        case ']':
            if(bAdjustHoriz==true){
                horizFadeWidth++;
            }
            else if(bAdjustVert==true){
                vertFadeWidth++;
            }
            else{
                gradientFadeWidth++;
            }
            break;
        case '-':
            if(bAdjustHoriz==true){
                horizWidth--;
            }
            else if(bAdjustVert==true){
                vertWidth--;
            }
            else{
                gradientWidth--;
            }
            break;
        case '[':
            if(bAdjustHoriz==true){
                horizFadeWidth--;
            }
            else if(bAdjustVert==true){
                vertFadeWidth--;
            }
            else{
                gradientFadeWidth--;
            }
            break;
        case ' ':
            settings.setValue("WIDTH",gradientWidth);
            settings.setValue("CENTER",gradientCenter);
            settings.setValue("FADE", gradientFadeWidth);
            settings.setValue("HORIZBORDER",horizWidth);
            settings.setValue("HORIZFADE", horizFadeWidth);
            settings.setValue("VERTBORDER",vertWidth);
            settings.setValue("VERTFADE", vertFadeWidth);
            settings.setValue("HORIZ",bHorizBorder);
            settings.setValue("VERT", bVertBorder);
            settings.setValue("MASK",bMask);
            settings.save("mySettings.xml");
    }
}

//--------------------------------------------------------------
void cloudPlayer::keyReleased(int key){
      switch(key){  
    case OF_KEY_LEFT_CONTROL:
        bAdjustHoriz=false;
        break;
    case OF_KEY_LEFT_ALT:
        bAdjustVert=false;
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
