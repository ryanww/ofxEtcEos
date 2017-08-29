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
    comsEnabled = false;
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
        
        //UDP RX
        char udpRxMsg[1000];
        udpRx.Receive(udpRxMsg,1000);
        string msg = udpRxMsg;
        if (msg.length()>0){
            parseReply(msg);
        }
    }
}

//Internal Functions
void ofxEtcEos::parseReply(string _reply){
    //TODO: Handle parse reply
    ofLogVerbose("ofxEtcEos")<<"Received string: "<<_reply;
}
void ofxEtcEos::sendCommandToConsoleCmdLine(string _cmd){
    if (comsEnabled){
        stringstream c;
        if (user > 0){ c<<"<U"<<user<<"> "; }
        c<<"$ ";
        c<<_cmd;
        c<<"\r";
    } else {
        ofLogError("ofxEtcEos")<<"Coms are disabled - can't send command to console";
    }
}
void ofxEtcEos::sendCommandToEventHandler(string _cmd){
    if (comsEnabled){
        stringstream c;
        c<<_cmd;
        c<<"\r";
    } else {
        ofLogError("ofxEtcEos")<<"Coms are disabled - can't send command to console";
    }
}



//Sets
#pragma mark SETS
void ofxEtcEos::setEnabled(bool _enable){
    ofLogVerbose("ofxEtcEos")<<"Setting enable to: "<<_enable;
    comsEnabled = _enable;
}
void ofxEtcEos::setUser(int _user){
    if (_user < 9 && _user >= 0){
        ofLogVerbose("ofxEtcEos")<<"Setting user to: "<<_user;
        user = _user;
    } else {
        ofLogError("ofxEtcEos")<<"Setting user failed - out of range";
    }
}


//Commands
#pragma mark Commands
void ofxEtcEos::goCueList(int _list){
    if (_list >0){
        ofLogVerbose("ofxEtcEos")<<"Go list:"<<_list;
        sendCommandToEventHandler("Go "+ofToString(_list));
    } else {
        ofLogError("ofxEtcEos")<<"goCueList - List out of range";
    }
}
void ofxEtcEos::goCue(int _list, int _cue){
    if (_list > 0 && _cue >= 0){
        ofLogVerbose("ofxEtcEos")<<"Go cue:"<<_cue<<" list:"<<_list;
        sendCommandToEventHandler("Cue "+ofToString(_list)+" "+ofToString(_cue));
    } else {
        ofLogError("ofxEtcEos")<<"goCue - List or cue out of range";
    }
}
void ofxEtcEos::releaseCueList(int _list){
    if (_list >0){
        ofLogVerbose("ofxEtcEos")<<"Release list:"<<_list;
        sendCommandToEventHandler("Release "+ofToString(_list));
    } else {
        ofLogError("ofxEtcEos")<<"releaseCueList - List out of range";
    }
}
void ofxEtcEos::resumeCue(int _list, int _cue){
    if (_list > 0 && _cue >= 0){
        ofLogVerbose("ofxEtcEos")<<"Resume cue:"<<_cue<<" list:"<<_list;
        sendCommandToEventHandler("Resume "+ofToString(_list)+" "+ofToString(_cue));
    } else {
        ofLogError("ofxEtcEos")<<"resumeCue - List or cue out of range";
    }
}
void ofxEtcEos::resumeAll(){
    ofLogVerbose("ofxEtcEos")<<"Resume All";
    sendCommandToEventHandler("Resume");
}
void ofxEtcEos::clearCueList(int _list){
    if (_list >0){
        ofLogVerbose("ofxEtcEos")<<"Clear list:"<<_list;
        sendCommandToEventHandler("GoCue 0 "+ofToString(_list));
    } else {
        ofLogError("ofxEtcEos")<<"clearCueList - List out of range";
    }
}
void ofxEtcEos::offCueList(int _list){
    if (_list >0){
        ofLogVerbose("ofxEtcEos")<<"Off list:"<<_list;
        sendCommandToEventHandler("Off "+ofToString(_list));
    } else {
        ofLogError("ofxEtcEos")<<"offCueList - List out of range";
    }
}
void ofxEtcEos::resumeCueList(int _list){
    if (_list >0){
        ofLogVerbose("ofxEtcEos")<<"Resume list:"<<_list;
        sendCommandToEventHandler("Resume "+ofToString(_list));
    } else {
        ofLogError("ofxEtcEos")<<"resumeCueList - List out of range";
    }
}

void ofxEtcEos::assertCueList(int _list){
    if (_list >0){
        ofLogVerbose("ofxEtcEos")<<"Assert list:"<<_list;
        sendCommandToEventHandler("Assert "+ofToString(_list));
    } else {
        ofLogError("ofxEtcEos")<<"asseertCueList - List out of range";
    }
}
void ofxEtcEos::stopCueList(int _list){
    if (_list >0){
        ofLogVerbose("ofxEtcEos")<<"Stop list:"<<_list;
        sendCommandToEventHandler("Stop "+ofToString(_list));
    } else {
        ofLogError("ofxEtcEos")<<"stopCueList - List out of range";
    }
}
void ofxEtcEos::stopCue(int _list, int _cue){
    if (_list > 0 && _cue >= 0){
        ofLogVerbose("ofxEtcEos")<<"Stop cue:"<<_cue<<" list:"<<_list;
        sendCommandToEventHandler("Stop Cue "+ofToString(_list)+" "+ofToString(_cue));
    } else {
        ofLogError("ofxEtcEos")<<"stopCue - List or cue out of range";
    }
}
void ofxEtcEos::stopAll(){
    ofLogVerbose("ofxEtcEos")<<"Stop All";
    sendCommandToEventHandler("Stop");
}
void ofxEtcEos::triggerMacro(int _macro){
    if (_macro >0){
        ofLogVerbose("ofxEtcEos")<<"Fire macro:"<<_macro;
        sendCommandToEventHandler("Macro "+ofToString(_macro));
    } else {
        ofLogError("ofxEtcEos")<<"triggerMacro - Macro out of range";
    }
}




