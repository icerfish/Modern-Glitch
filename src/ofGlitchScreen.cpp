
#include "ofGlitchScreen.h"

ofGlitchScreen::ofGlitchScreen(){
	init(0,0, NULL);
}

ofGlitchScreen::ofGlitchScreen(float _x, float _y, ofImage* _cImg){
	init(_x, _y, _cImg);
}

ofGlitchScreen::ofGlitchScreen(ofPoint iniPos, ofImage* _cImg){
	init(iniPos.x, iniPos.y, _cImg);
}

void ofGlitchScreen::init(float _x, float _y, ofImage* _cImg){
	x = _x;
	y = _y;
	oldPos.x = x;
	oldPos.y = y;
    
    screenShot = _cImg;

	bActive = true;
    isOverRed = false;
}

void ofGlitchScreen::updateAdvert(float timeStep){
	if(!bActive) return;
	float tempX = x, tempY = y;
	oldPos.x = tempX;
	oldPos.y = tempY;
}

void ofGlitchScreen::debugRender(){
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(x, y);
    ofSetColor(255,ofRandom(180, 255));
    screenShot -> draw(0,0, screenShot -> getWidth(), screenShot -> getHeight());
    ofPopStyle();
    ofPopMatrix();
}


//--------CUSTOM-------
void ofGlitchScreen::graphics(ofImage* _frame){
    //    _cImg->draw(x-radius, y-radius, radius*2, radius*2);
    
}


void ofGlitchScreen::setActive(bool _bActive){
	bActive = _bActive;
}

bool ofGlitchScreen::isActive(){
	return bActive;	
}

void ofGlitchScreen::moveTo(ofPoint& _target){
	moveTo(_target.x, _target.y);
}

void ofGlitchScreen::moveTo(float _x, float _y){
	float diffX = _x - x;
	float diffY = _y - y;
	oldPos.x += diffX;
	oldPos.y += diffY;
	x = _x;
	y = _y;
}


