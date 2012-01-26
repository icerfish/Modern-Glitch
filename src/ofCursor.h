#pragma once

#include "ofBaseGui.h"

class ofCursor : public ofBaseGui{
    
public:    
    void setup(string imageName) {
        
        currentMilli = 0;
        currentMilli2 = 0;
        currentMilli3 = 0;
        
        cursor.loadImage(imageName);
        b.x = 0;
        b.y = 0;
        b.width = cursor.width;
        b.height = cursor.height;
        currentFrame = 0;
		bGuiActive = false;
	}
    
    void update(){
        if ((ofGetElapsedTimeMillis() - currentMilli) > 100) {
            cursor2.x = (ofGetAppPtr()->mouseX - 1);
            cursor2.y = (ofGetAppPtr()->mouseY - 1);
            currentMilli = ofGetElapsedTimeMillis();  
        }
        
        if ((ofGetElapsedTimeMillis() - currentMilli2) > 250) {
            cursor3.x = (ofGetAppPtr()->mouseX - 1);
            cursor3.y = (ofGetAppPtr()->mouseY - 1);
            currentMilli2 = ofGetElapsedTimeMillis();  
        }
        
        if ((ofGetElapsedTimeMillis() - currentMilli3) > 500) {
            cursor4.x = (ofGetAppPtr()->mouseX - 1);
            cursor4.y = (ofGetAppPtr()->mouseY - 1);
            currentMilli3 = ofGetElapsedTimeMillis();   
        }
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
        ofTranslate(ofGetAppPtr()->mouseX - 1, ofGetAppPtr()->mouseY - 1);
        ofRotate(currentFrame);
        cursor.draw(b.x, b.y, b.width, b.height);
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(cursor2.x, cursor2.y);
        ofRotate(currentFrame);
        cursor.draw(b.x, b.y, b.width, b.height);
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(cursor3.x, cursor3.y);
        ofRotate(currentFrame);
        cursor.draw(b.x, b.y, b.width, b.height);
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(cursor4.x, cursor4.y);
        ofRotate(currentFrame);
        cursor.draw(b.x, b.y, b.width, b.height);
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
    
    ofImage cursor;
    ofPoint cursor2;
    ofPoint cursor3;
    ofPoint cursor4;
    
    int currentMilli;
    int currentMilli2;
    int currentMilli3;
    
};