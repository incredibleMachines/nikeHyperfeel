#include "cloudSender.h"

//--------------------------------------------------------------
void cloudSender::setup(){

	ofBackground(0, 0, 0);
    
    host[0]="10.0.1.11";
    host[1]="10.0.1.12";
    host[2]="10.0.1.13";
    host[3]="10.0.1.14";
    
    
	// open an outgoing connection to HOST:PORT
	one.setup(host[0], PORT);
    two.setup(host[1], PORT);
    three.setup(host[2], PORT);
    four.setup(host[3], PORT);
    
    // print input ports to console
	midiIn.listPorts(); // via instance
	//ofxMidiIn::listPorts(); // via static as well
	
	// open port by number (you may need to change this)
	midiIn.openPort(1);
	//midiIn.openPort("IAC Pure Data In");	// by name
	//midiIn.openVirtualPort("ofxMidiIn Input");	// open a virtual port
	
	// don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
	midiIn.ignoreTypes(false, false, false);
	
	// add testApp as a listener
	midiIn.addListener(this);
	
	// print received messages to the console
	midiIn.setVerbose(true);
}

//--------------------------------------------------------------
void cloudSender::update(){

}

//--------------------------------------------------------------
void cloudSender::draw(){
	// display instructions
	string buf;
	buf = "sending osc messages to" + string(host[0]) + ", " + string(host[1]) + ", " + string(host[2]) + ", " + string(host[3]) + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);
    
    // draw the last recieved message contents to the screen
	text << "Received: " << ofxMidiMessage::getStatusString(midiMessage.status);
	ofDrawBitmapString(text.str(), 20, 40);
	text.str(""); // clear
	
	text << "channel: " << midiMessage.channel;
	ofDrawBitmapString(text.str(), 20, 54);
	text.str(""); // clear
	
	text << "pitch: " << midiMessage.pitch;
	ofDrawBitmapString(text.str(), 20, 68);
	text.str(""); // clear
	ofRect(20, 78, ofMap(midiMessage.pitch, 0, 127, 0, ofGetWidth()-40), 20);
	
	text << "velocity: " << midiMessage.velocity;
	ofDrawBitmapString(text.str(), 20, 116);
	text.str(""); // clear
	ofRect(20, 125, ofMap(midiMessage.velocity, 0, 127, 0, ofGetWidth()-40), 20);
	
	text << "control: " << midiMessage.control;
	ofDrawBitmapString(text.str(), 20, 164);
	text.str(""); // clear
	ofRect(20, 174, ofMap(midiMessage.control, 0, 127, 0, ofGetWidth()-40), 20);
	
	text << "value: " << midiMessage.value;
	ofDrawBitmapString(text.str(), 20, 212);
	text.str(""); // clear
	if(midiMessage.status == MIDI_PITCH_BEND) {
		ofRect(20, 222, ofMap(midiMessage.value, 0, MIDI_MAX_BEND, 0, ofGetWidth()-40), 20);
	}
	else {
		ofRect(20, 222, ofMap(midiMessage.value, 0, 127, 0, ofGetWidth()-40), 20);
	}
	
	text << "delta: " << midiMessage.deltatime;
	ofDrawBitmapString(text.str(), 20, 260);
	text.str(""); // clear
}

//--------------------------------------------------------------
void cloudSender::keyPressed(int key){
	if(key == '1'){
		ofxOscMessage m;
		m.setAddress("/on");
		m.addIntArg(1);
		one.sendMessage(m);
	}
    if(key == '2'){
		ofxOscMessage m;
		m.setAddress("/on");
		m.addIntArg(2);
		two.sendMessage(m);
	}
    if(key == '3'){
		ofxOscMessage m;
		m.setAddress("/on");
		m.addIntArg(3);
		three.sendMessage(m);
        
        ofxOscMessage n;
		n.setAddress("/on");
		n.addIntArg(4);
		four.sendMessage(n);
	}
//    if(key == '4'){
//		ofxOscMessage m;
//		m.setAddress("/on");
//		m.addIntArg(4);
//		four.sendMessage(m);
//	}
}

//--------------------------------------------------------------
void cloudSender::keyReleased(int key){
    if(key == '1'){
		ofxOscMessage m;
		m.setAddress("/off");
		m.addIntArg(1);
		one.sendMessage(m);
	}
    if(key == '2'){
		ofxOscMessage m;
		m.setAddress("/off");
		m.addIntArg(2);
		two.sendMessage(m);
	}
    if(key == '3'){
		ofxOscMessage m;
		m.setAddress("/off");
		m.addIntArg(3);
		three.sendMessage(m);
        
        ofxOscMessage n;
		n.setAddress("/off");
		n.addIntArg(4);
		four.sendMessage(n);
	}
//    if(key == '4'){
//		ofxOscMessage m;
//		m.setAddress("/off");
//		m.addIntArg(4);
//		four.sendMessage(m);
//	}
}

//--------------------------------------------------------------
void cloudSender::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void cloudSender::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void cloudSender::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void cloudSender::mouseReleased(int x, int y, int button){


}

//--------------------------------------------------------------
void cloudSender::windowResized(int w, int h){

}

//--------------------------------------------------------------
void cloudSender::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void cloudSender::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void cloudSender::newMidiMessage(ofxMidiMessage& msg) {
    
	// make a copy of the latest message
	midiMessage = msg;
    
    if (msg.velocity>0){
        if(msg.pitch == START_PITCH){
            ofxOscMessage m;
            m.setAddress("/on");
            m.addIntArg(1);
            one.sendMessage(m);
        }
        else if(msg.pitch == START_PITCH+PITCH_INTERVAL){
            ofxOscMessage m;
            m.setAddress("/on");
            m.addIntArg(2);
            two.sendMessage(m);
        }
        else if(msg.pitch == START_PITCH+PITCH_INTERVAL*2){
            ofxOscMessage m;
            m.setAddress("/on");
            m.addIntArg(3);
            three.sendMessage(m);
            
            ofxOscMessage n;
            n.setAddress("/on");
            n.addIntArg(4);
            four.sendMessage(n);
        }
        else if(msg.pitch == START_PITCH+PITCH_INTERVAL*3){ //--- should never happen
            ofxOscMessage m;
            m.setAddress("/on");
            m.addIntArg(4);
            four.sendMessage(m);
        }
    }
    
    else{
        if(msg.pitch == START_PITCH){
            ofxOscMessage m;
            m.setAddress("/off");
            m.addIntArg(1);
            one.sendMessage(m);
        }
        else if(msg.pitch == START_PITCH+PITCH_INTERVAL){
            ofxOscMessage m;
            m.setAddress("/off");
            m.addIntArg(2);
            two.sendMessage(m);
        }
        else if(msg.pitch == START_PITCH+PITCH_INTERVAL*2){
            ofxOscMessage m;
            m.setAddress("/off");
            m.addIntArg(3);
            three.sendMessage(m);
            
            ofxOscMessage n;
            n.setAddress("/off");
            n.addIntArg(4);
            four.sendMessage(n);
        }
        else if(msg.pitch == START_PITCH+PITCH_INTERVAL*3){ //--- should never happen
            ofxOscMessage m;
            m.setAddress("/off");
            m.addIntArg(4);
            four.sendMessage(m);
        }
    }
}
