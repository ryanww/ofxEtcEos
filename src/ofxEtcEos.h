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
    
    
    
    void triggerCue(int _cuelist, int _cue);
    
    
private:
    
    //Connection
    string ip;
    int port;
    ofxUDPManager udpRx, udpTx;
    bool twoWayMode;
    void setupComs();
    
    //Running
    void threadedFunction();
    
    //Console Specific Stuff
    int user;
    
    
    
    
    
};


