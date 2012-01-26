#pragma once

#include "ofDesktop.h"

class ofIcon : public ofBaseGui{
    friend class ofWallpaper;
    
public:    
	ofIcon* setup(string image, string _name) {
        lucidaGrande.loadFont("fonts/Lucida Grande.ttf", 11);
        name = _name;
        appIcon.loadImage(image);
        appIconBox.set(0,0,80,80);
        appTextBox.set(0,0,lucidaGrande.stringWidth(name),lucidaGrande.stringHeight(name));
        currentFrame = 0;
		bGuiActive = false;
        startApp = false;
        
		return this;
	}
    
    void update(){
        if(ofGetElapsedTimeMillis()-prevAppTime>200){
            startApp = false;
        }
    }
	
	virtual void mouseMoved(ofMouseEventArgs & args){	
	}
	
	virtual void mousePressed(ofMouseEventArgs & args){
        
        if(ofGetElapsedTimeMillis()-prevClickTime<200){
            doubleClicked = true;
        } else {
            doubleClicked = false;
        }
        
        prevClickTime = ofGetElapsedTimeMillis();
        
        setValue(args.x, args.y, true);
        
	}
	
	virtual void mouseDragged(ofMouseEventArgs & args){
        setValue(args.x, args.y, false);
	}
	
	virtual void mouseReleased(ofMouseEventArgs & args){
		bGuiActive = false;		
	}	
	
	void draw(){
		currentFrame = ofGetFrameNum();
		
		ofPushStyle();
		ofPushMatrix();
        
        ofTranslate(b.x, b.y);
		
//        if(bGuiActive) {
//            ofRect(appIconBox);
//        }
        
        appIcon.draw(appIconBox.x, appIconBox.y, appIconBox.width, appIconBox.height);
        
        ofSetColor(255);
		ofTranslate(appIconBox.x, appIconBox.height);
        
		ofTranslate((appIconBox.width/2) - (appTextBox.width/2), appTextBox.height + textPadding);
		lucidaGrande.drawString(name, 0, 0);

        
        ofPopMatrix();
		ofPopStyle();
		
	}
    
    bool isRunning(){
        return startApp;
    }
    
    
protected:
	
	void setValue(float mx, float my, bool bCheck){
        
		if( ofGetFrameNum() - currentFrame > 1 ){
			bGuiActive = false;
			return; 
		}
        
        if( bCheck ){
            ofRectangle checkRect = appIconBox;
            checkRect.x += b.x;
			checkRect.y += b.y;
			if( checkRect.inside(mx, my) ){
				bGuiActive = true;
                bGrabbed = true;					
                grabPt.set(mx-b.x, my-b.y);
                if(doubleClicked) {
                    startApp = true;
                    prevAppTime = ofGetElapsedTimeMillis();
                }
			}else{
				bGuiActive = false;
                bGrabbed = false;
            }
		} else if( bGrabbed ){
			b.x = mx - grabPt.x;
			b.y = my - grabPt.y;
		}
    }
    
    
	ofPoint grabPt;
	bool bGrabbed;
    bool doubleClicked;
    bool startApp;
    
    ofRectangle appIconBox;
    ofRectangle appTextBox;
    string name;
    ofImage appIcon;
    
    int prevClickTime;
    int currentTime;
    int prevAppTime;
};