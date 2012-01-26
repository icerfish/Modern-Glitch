#pragma once

#include "ofGlitchScreen.h"


class ofGlitchCreator : public ofBaseGui{
    
public:    
    void setup() {
        currentFrame = 0;
		bGuiActive = false;
        iterations = 0;
        bCreateGlitches = true;
	}
	
    void update(){
        
        if(glitches.size() > 20){
            delete glitches[0];
            glitches.erase (glitches.begin());
        }
        
        if(bCreateGlitches){
            int del = ofRandom(10, 100);
            if(ofGetFrameNum() % del == 0){
                ofImage* grab = new ofImage();
                int iWid, iHei;
                iWid = ofRandom(ofGetScreenWidth());
                iHei = ofRandom(ofGetScreenHeight());
                if(iWid > ofGetScreenWidth()/15){
                    iHei = ofRandom(0, ofGetScreenHeight()/10);
                }
                
                int iX, iY;
                iX = ofRandom(ofGetScreenWidth()-iWid);
                iY = ofRandom(ofGetScreenHeight() - iHei);
                grab -> allocate(iWid, iHei, OF_IMAGE_COLOR_ALPHA);
                grab -> grabScreen(iX, iY, iWid, iHei);
                ofGlitchScreen* p = new ofGlitchScreen(iX, iY, grab);
                //                float randomStep = 5;
                glitches.push_back(p);
                iterations++;
            }
        }

//        if(iterations > 40){
//            bCreateGlitches = false;
//        }
        
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
        
        for(int i=0; i<glitches.size(); i++){
            glitches[i]->debugRender();
        }
        
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
    
    ofGlitchScreen* nGlitch;
    vector<ofGlitchScreen*> glitches;
    
    bool bCreateGlitches;
    int iterations;
    
    
};