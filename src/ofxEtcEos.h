//
//  ofxEtcEos.h
//
//  Created by Ryan Wilkinson on 8/23/17.
//

#include "ofMain.h"
#include "ofxNetwork.h"

#pragma once

class ofxEtcEos : public ofThread {
  
public:
    //Init
    ofxEtcEos();
    ~ofxEtcEos();
    
    //Setup
    void setup(string _ip, int _port, bool _twoWayMode = true);
    
    //Sets
    void setEnabled(bool _enable);
    void setUser(int _user);
    
    //Commands
    void goCueList(int _list);
    void goCue(int _list, int _cue);
    void releaseCueList(int _list);
    void clearCueList(int _list);
    void offCueList(int _list);
    void resumeCueList(int _list);
    void resumeCue(int _list, int _cue);
    void resumeAll();
    void assertCueList(int _list);
    void stopCueList(int _list);
    void stopCue(int _list, int _cue);
    void stopAll();
    void triggerMacro(int _macro);
    
private:
    
    //Connection
    string ip;
    int port;
    bool comsEnabled;
    ofxUDPManager udpRx, udpTx;
    bool twoWayMode;
    void setupComs();
    
    //Running
    void threadedFunction();
    
    //Internal Functions
    void parseReply(string _reply);
    void sendCommandToConsoleCmdLine(string _cmd);
    void sendCommandToEventHandler(string _cmd);
    
    //Console Specific Stuff
    int user;
    
    
    
    
    
};


