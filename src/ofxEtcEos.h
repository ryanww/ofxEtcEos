//
//  ofxEtcEos.hpp
//  wrvTitanicShowControl
//
//  Created by Ryan Wilkinson on 8/23/17.
//

#include "ofMain.h"

#pragma once

class ofxEtcEos : public ofThread {
  
public:
    void setup(string _ip, int _port);
    
    void triggerCue(int _cuelist, int _cue);
    
    
private:
    
    //Connection
    string ip;
    int port;
    
    
    
};


