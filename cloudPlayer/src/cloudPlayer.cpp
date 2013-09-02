#include "cloudPlayer.h"

//--------------------------------------------------------------
void cloudPlayer::setup(){
	ofBackground(0,0,0);
	ofSetVerticalSync(true);
    
    bFading=false;
    fadeSpeed=1500;

	// Uncomment this to show movies with alpha channels
	// cloudMovie.setPixelFormat(OF_PIXELS_RGBA);
    
    receiver.setup(PORT);

	cloudMovie.loadMovie("movies/"+ofToString(SCREEN)+".mov");
}

//--------------------------------------------------------------
void cloudPlayer::update(){
    while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        if(m.getAddress()=="/on"){
            if (m.getArgAsInt32(0)==SCREEN)
            {
                if(!cloudMovie.isPlaying()){
                    cloudMovie.play();
                    cloudMovie.setLoopState(OF_LOOP_NONE);
                }
            }
        }
        else if(m.getAddress()=="/off"){
            if (m.getArgAsInt32(0)==SCREEN)
            {
                if(cloudMovie.isPlaying()){
                    fadeMovie();
                }
            }
        }
    }
  
    if(cloudMovie.isPlaying()){
        cloudMovie.update();
    }
}

//--------------------------------------------------------------
void cloudPlayer::draw(){

	ofSetHexColor(0xFFFFFF);
    
    if(cloudMovie.isPlaying()){
        if(bFading==true){
            if(ofGetElapsedTimeMillis()-fadeTimer<fadeSpeed){
                float color=255-(255*((ofGetElapsedTimeMillis()-fadeTimer)/fadeSpeed));
                cout<<((ofGetElapsedTimeMillis()-fadeTimer)/fadeSpeed)<<endl;
                ofSetColor(color);
                cloudMovie.draw(0,0);
            }
            else{
                cloudMovie.stop();
                cloudMovie.firstFrame();
                bFading=false;
            }
        }
        else{
            cloudMovie.draw(0,0);
        }
    
        
    }

}
    
    //--------------------------------------------------------------
    void cloudPlayer::fadeMovie(){
        bFading=true;
        fadeTimer=ofGetElapsedTimeMillis();
    }

//--------------------------------------------------------------
void cloudPlayer::keyPressed  (int key){
    switch(key){

    }
}

//--------------------------------------------------------------
void cloudPlayer::keyReleased(int key){

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
