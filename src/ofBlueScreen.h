#pragma once

#include "ofBaseGui.h"

class ofBlueScreen : public ofBaseGui{
    
public:    
    void setup() {
        courier.loadFont("fonts/Courier.ttf", 12);
        b.x = 0;
        b.y = 0;
        b.width = resX;
        b.height = resY;
        currentMilli = 0;
        blink.set(0,0,10,2);
        currentFrame = 0;
		bGuiActive = false;
        title = "WARNING!";
        body = "The system is either feeling blue or has become emotionally unstable. You can wait and";
        body2 = "see if it begins to feel better, or you can cheer up your computer";
        opt = "* Press any key to return to GlitchOS.";
        opt2 = "* Press CTRL+ALT+DEL again to relieve your computer. You will";
        opt3 = "lose unsaved information in any programs that are running.";
        prompt = "Press any key to continue";
        ofRegisterKeyEvents(this);
	}
    
    virtual void keyPressed(ofKeyEventArgs & args){
        if(args.key){
            isQuit = true;
        }
    }
    
    virtual void keyReleased(ofKeyEventArgs & args){
        if(args.key){
            isQuit = false;
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
        
        ofFill();
        ofSetColor(0,0,255);
        ofRect(b.x, b.y, b.width, b.height);
        
        ofTranslate(resX/2, resY/2 - 100);
        
        ofPushMatrix();
        ofTranslate(-(courier.stringWidth(title)+16)/2, 0);
        ofSetColor(255);
        ofRect(0, 0, courier.stringWidth(title) + 16, courier.stringHeight(title) + 4);
        ofSetColor(0,0,255);
        courier.drawString(title, 8, courier.stringHeight(title)+1);
        ofPopMatrix();
        
        ofTranslate(0, 50);
        
        ofPushMatrix();
        ofSetColor(255);
        ofTranslate(-courier.stringWidth(body)/2, 0);
        courier.drawString(body, 0, courier.stringHeight(body));
        ofTranslate(0, courier.stringHeight(body) + textPadding);
        courier.drawString(body2, 0, courier.stringHeight(body2));
        ofPopMatrix();
        
        ofTranslate(0, (12+5)*2 +25);
        
        ofPushMatrix();
        ofTranslate(-courier.stringWidth(opt)/3*2, 0);
        courier.drawString(opt, 0, courier.stringHeight(opt));
        ofTranslate(0, courier.stringHeight(opt) + textPadding);
        courier.drawString(opt2, 0, courier.stringHeight(opt2));
        ofTranslate(19, courier.stringHeight(opt) + textPadding);
        courier.drawString(opt3, 0, courier.stringHeight(opt3));
        ofPopMatrix();
        
        ofTranslate(-10, (12+5)*3 + 25);
        
        ofPushMatrix();
        ofTranslate(-courier.stringWidth(prompt)/2,0);
        courier.drawString(prompt, 0, courier.stringHeight(prompt));
        ofPushStyle();
        ofTranslate(courier.stringWidth(prompt) + blink.width/2, courier.stringHeight(prompt) -blink.height);
        ofSetColor(255, 255, 0);
        if (1000 < (ofGetElapsedTimeMillis() - currentMilli) && (ofGetElapsedTimeMillis() - currentMilli) < 2000) {
            ofRect(blink);
        }
        if ((ofGetElapsedTimeMillis() - currentMilli) > 2000) {
            currentMilli = ofGetElapsedTimeMillis();
        }
        ofPopStyle();
        ofPopMatrix();
        
        
        ofPopMatrix();
		ofPopStyle();
		
	}
    
    bool isFalse(){
        return isQuit;
    }
    
protected:
	
	void setValue(float mx, float my, bool bCheck){
        
		if( ofGetFrameNum() - currentFrame > 1 ){
			bGuiActive = false;
			return; 
		}
    }
    
    ofTrueTypeFont courier;
    string title;
    string body;
    string body2;
    string opt;
    string opt2;
    string opt3;
    string prompt;
    ofRectangle blink;
    int currentMilli;
    bool isQuit;

    
};