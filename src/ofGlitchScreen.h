#pragma once
#include "ofMain.h"

class ofGlitchScreen: public ofPoint{
protected:
    
	ofPoint oldPos;
    float width, height;
	bool bActive;
    bool isOverRed;
	void init(float _x, float _y, ofImage* _cImg);
    ofImage* screenShot;
    
public:
	ofGlitchScreen();
	ofGlitchScreen(float x, float y, ofImage* _cImg);
	ofGlitchScreen(ofPoint _iniPos, ofImage* _cImg);
	
	virtual ~ofGlitchScreen(){}
	
	
	virtual void updateAdvert(float timeStep = 1.0f);
	virtual void render(){debugRender();}
	void debugRender();
    
	void setActive(bool _bActive);
	bool isActive();
    
    void moveTo(ofPoint& _target);
	void moveTo(float _x, float _y);
    
    //--------CUSTOM---------
    void graphics(ofImage* _frame);
};