#pragma once

#include "ofBaseGui.h"

class ofMenuBar : public ofBaseGui{
public:
	
	void setup(float x = 0, float y = 0) {
		setup("", x, y);
	}
	
	void setup(string menuName, float x = 0, float y = 0){
		name = menuName;
		b.x = x;
		b.y = y;
		header = defaultHeight;
		leftJustify  = 10;
		b.width = 45;
        currentX = b.width;
		b.height = defaultHeight; // weird to start out with something arbitrary like this
		ofRegisterMouseEvents(this);
        bg.loadImage("screen/menuBar/menuBack.png");
        apple.loadImage("screen/menuBar/apple.png");
        applePressed.loadImage("screen/menuBar/applePressed.png");
        
		appleIconBox.x = leftJustify;
		appleIconBox.y = 0;
		appleIconBox.width = apple.getWidth();
		appleIconBox.height = defaultHeight;
	}
	
	void add(ofBaseGui * element){
		collection.push_back( element );
		
		element->b.y = 0;
		element->b.x = currentX;
		currentX += element->b.width;
		
		if( currentX >= b.width ){
			b.width += 100;
		} 
	}
	
	void clear(){
		collection.clear();
	}
	
	virtual void mouseMoved(ofMouseEventArgs & args){
        
	}
	
	virtual void mousePressed(ofMouseEventArgs & args){
		setValue(args.x, args.y, true);
		if( bGuiActive ){
			ofMouseEventArgs a = args;
			a.x -= b.x;
			a.y -= b.y;
			for(int i = 0; i < collection.size(); i++){
				collection[i]->mousePressed(a);
			}
		}
	}
	
	virtual void mouseDragged(ofMouseEventArgs & args){
        
	}
	
	virtual void mouseReleased(ofMouseEventArgs & args){
		bGuiActive = false;
		for(int k = 0; k < collection.size(); k++){
			ofMouseEventArgs a = args;
			a.x -= b.x;
			a.y -= b.y;			
			collection[k]->mouseReleased(a);
		}
	}		
	
	void draw(){
		ofPushStyle();
		ofPushMatrix();
		
		currentFrame = ofGetFrameNum();
		
		ofTranslate(b.x, b.y);
        
		ofNoFill();	
		ofPushMatrix();
        bg.draw(0, 0, resX, 22);
		apple.draw(appleIconBox.x, appleIconBox.y);
        if(bGrabbed && bGuiActive) {
            applePressed.draw(appleIconBox.x, appleIconBox.y);
        }
		ofPopMatrix();
		
		for(int i = 0; i < collection.size(); i++){
			collection[i]->draw();
		}
		
		ofPopMatrix();
		ofPopStyle();
	}
    
	
protected:
	
	void setValue(float mx, float my, bool bCheck){
		
		if( ofGetFrameNum() - currentFrame > 1 ){
			bGrabbed = false;
			bGuiActive = false;
			return; 
		}
		if( bCheck ){
			if( b.inside(mx, my) ){
				bGuiActive = true;
				
                if( appleIconBox.inside(mx, my) ){
                    bGrabbed = true;
                }else{
                    bGrabbed = false;
				}
            }
		}
	}		
	
	bool bGrabbed;
	float currentX;
	float leftJustify;
	float header;
	vector <ofBaseGui *> collection;
	
	string filename;
	ofImage apple, applePressed;
    ofImage bg;
	ofRectangle appleIconBox;
};
