#pragma once

#include "ofBaseGui.h"

class ofTemp : public ofBaseGui{
    
public:    
    void setup() {
        currentFrame = 0;
		bGuiActive = false;
	}
	
	virtual void mouseMoved(ofMouseEventArgs & args){
        
	}
	
	virtual void mousePressed(ofMouseEventArgs & args){
        
	}
	
	virtual void mouseDragged(ofMouseEventArgs & args){
        
	}
	
	virtual void mouseReleased(ofMouseEventArgs & args){
		bGuiActive = false;		
	}	
	
	void draw(){
		currentFrame = ofGetFrameNum();
        
		ofPushStyle();
		ofPushMatrix();

        ofPopMatrix();
		ofPopStyle();
		
	}
    
protected:
	
	void setValue(float mx, float my, bool bCheck){
        
		if( ofGetFrameNum() - currentFrame > 1 ){
			bGuiActive = false;
			return; 
		}
    }
    

    
};