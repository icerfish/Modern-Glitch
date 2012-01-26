#pragma once

#include "ofMenuBar.h"

class ofMenuItem : public ofBaseGui{
	friend class ofMenuBar;
	
public:    
	ofMenuItem* setup(string itemName, bool bold, float height = defaultHeight) {
        if(bold) {
            lucidaGrande.loadFont("fonts/Lucida Grande Bold.ttf", 11);
        } else {
            lucidaGrande.loadFont("fonts/Lucida Grande.ttf", 11);
        }
        name = itemName;
        bPressed.loadImage("screen/menuBar/menuBackPressed.png");
        itemPadding = 30;
		b.x = 0;z
		b.y = 0;
		b.width = lucidaGrande.stringWidth(name) + itemPadding;
		b.height = height;
        buttonRect.set(b);
		currentFrame = 0;
		bGuiActive = false;
		return this;
	}
	
	virtual void mouseMoved(ofMouseEventArgs & args){
	}
	
	virtual void mousePressed(ofMouseEventArgs & args){
		setValue(args.x, args.y, true);
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
		
		ofSetColor(255);
        
        if(bGuiActive){
            bPressed.draw(b.x, b.y, b.width, b.height);
            ofSetColor(255);
        } else {
            ofSetColor(textColor);
        }
        
		ofTranslate(b.x, b.y);
		ofTranslate(((b.width+itemPadding)/2) - (b.width/2), b.height / 2 + textPadding);
		lucidaGrande.drawString(name, 0, 0);
		
		ofPopMatrix();
		ofPopStyle();
	}
	
protected:

	void setValue(float mx, float my, bool bCheck){
        
		if( ofGetFrameNum() - currentFrame > 1 ){
			bGuiActive = false;
			return; 
		}
		if( bCheck ){
            ofRectangle checkRect = buttonRect;
            checkRect.x += b.x;
			checkRect.y += b.y;
			if( checkRect.inside(mx, my) ){
				bGuiActive = true;
			}else{
				bGuiActive = false;
            }
		}
	}
    
    ofImage bPressed;
    float header;
    ofRectangle buttonRect;
    int itemPadding;


};