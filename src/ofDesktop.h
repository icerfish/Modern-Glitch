#pragma once

#include "ofBaseGui.h"

class ofDesktop : public ofBaseGui{
	
public:    
	void setup() {
        lucidaGrande.loadFont("fonts/Lucida Grande.ttf", 11);
        ofRegisterMouseEvents(this);
        b.x = 0;
        b.y = 0;
        b.width = resX;
        b.height = resY;
	}
    
    void add(ofBaseGui * element){
		collection.push_back( element );
        
        element->b.y = ofRandom(defaultHeight, resY - 95);
		element->b.x = ofRandom(0, resX - 80);
	}
    
    void clear(){
		collection.clear();
	}
	
	virtual void mouseMoved(ofMouseEventArgs & args){
        ofMouseEventArgs a = args;
		a.x -= b.x;
		a.y -= b.y;		
		for(int i = 0; i < collection.size(); i++){
			collection[i]->mouseMoved(a);
		}		
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
        setValue(args.x, args.y, false);	
		if( bGuiActive ){
			ofMouseEventArgs a = args;
			a.x -= b.x;
			a.y -= b.y;			
			for(int i = 0; i < collection.size(); i++){
				collection[i]->mouseDragged(a);
			}
		}
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
        
        
		for(int i = 0; i < collection.size(); i++){
			collection[i]->draw();
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
        
        if( bCheck ){
			if( b.inside(mx, my) ){
				bGuiActive = true;
            }
        }
    }
    
    
    	vector <ofBaseGui *> collection;
    	bool bGrabbed;
        string num;
};