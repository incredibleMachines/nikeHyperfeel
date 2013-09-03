#include "lunarlonStatue.h"

//--------------------------------------------------------------
void lunarlonStatue::setup(){

	ofBackground(40, 100, 40);

	// open an outgoing connection to HOST:PORT
	sender.setup("192.168.1.10", SEND_PORT);
    receiver.setup(RECEIVE_PORT);
    bTouched=false;
    ofBackground(255);
}

//--------------------------------------------------------------
void lunarlonStatue::update(){
    while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        if(m.getAddress()=="/touch"){
            if (m.getArgAsInt32(0)==1)
            {
                message="touched";
                bTouched=true;
            }
            else if (m.getArgAsInt32(0)==0)
            {
                bTouched=false;
                message="off";

            }
        }
    }

}

//--------------------------------------------------------------
void lunarlonStatue::draw(){
	// display instructions
    if(bTouched==true){
        ofBackground(255);
    }
    else{
        ofBackground(0);
    }
	string buf;
	buf = "sending osc messages to " + string("192.168.1.10") + ofToString(SEND_PORT);
	ofDrawBitmapString(buf, 10, 20);
    buf = "receiving osc message" + message+" from "+ string("192.168.1.10") + ofToString(RECEIVE_PORT);
	ofDrawBitmapString(buf, 10, 40);
}

//--------------------------------------------------------------
void lunarlonStatue::keyPressed(int key){
    
    switch (key) {
        case 't':
            bTouched = true;
            sendTouch();
            break;
    }
}

//--------------------------------------------------------------
void lunarlonStatue::keyReleased(int key){
    switch (key) {
        case 't':
            bTouched = false;
            sendTouch();
            break;
    }
}

//--------------------------------------------------------------
void lunarlonStatue::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void lunarlonStatue::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void lunarlonStatue::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void lunarlonStatue::mouseReleased(int x, int y, int button){


}

//--------------------------------------------------------------
void lunarlonStatue::windowResized(int w, int h){

}

//--------------------------------------------------------------
void lunarlonStatue::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void lunarlonStatue::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void lunarlonStatue::sendTouch(){
    ofxOscMessage m;
    m.setAddress("/touch");
    m.addIntArg(1);
    sender.sendMessage(m);
    
}
//--------------------------------------------------------------
void lunarlonStatue::sendOff(){
    ofxOscMessage m;
    m.setAddress("/touch");
    m.addIntArg(0);
    sender.sendMessage(m);
    
}

