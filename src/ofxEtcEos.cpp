//
//  ofxEtcEos.cpp
//
//  Created by Ryan Wilkinson on 8/23/17.
//

#include "ofxEtcEos.h"

//Init
#pragma mark INIT
ofxEtcEos::ofxEtcEos(){
    ip = "";
    port = 0;
    twoWayMode = false;
}
ofxEtcEos::~ofxEtcEos(){
    udpTx.Close();
    udpRx.Close();
    stopThread();
}

//Setup
#pragma mark SETUP
void ofxEtcEos::setup(string _ip, int _port, bool _twoWayMode){
    ofLogVerbose("ofxEtcEos")<<"Initializing module with ip:"<<_ip<<":"<<_port<<" - two way mode:"<<_twoWayMode;
    ip = _ip;
    port = _port;
    twoWayMode = _twoWayMode;
    setupComs();
    startThread();
}
void ofxEtcEos::setupComs(){
    ofLogVerbose("ofxEtcEos")<<"Initializing coms";
    //Setup UDP Transmitter
    ofxUDPSettings settings;
    settings.sendTo(ip, port);
    settings.blocking = false;
    udpTx.Setup(settings);
    
    if (twoWayMode){
        //Setup UDP Receiver
        udpRx.Create();
        udpRx.Bind(51302);
        udpRx.SetNonBlocking(true);
    }
    ofLogVerbose("ofxEtcEos")<<"Initializing coms complete";
}

//Running
#pragma mark RUNNING
void ofxEtcEos::threadedFunction(){
    while (isThreadRunning()){
        
        
        
    }
}


//Sets
#pragma mark SETS
void ofxEtcEos::setEnabled(bool _enable){
    
}




void triggerCue(int _cuelist, int _cue){
    
    
}


