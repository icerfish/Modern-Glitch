

#include "ofWindowSetup.h"


ofWindowSetup::ofWindowSetup(ofPoint _worldMin, ofPoint _worldMax){
	worldMin.set(_worldMin.x, _worldMin.y);
	worldMax.set(_worldMax.x, _worldMax.y);
	numAdverts = 0;
}

ofWindowSetup::~ofWindowSetup(){
	for(int i=0; i<adverts.size(); i++){
		delete adverts[i];	
	}
	adverts.clear();
}

void ofWindowSetup::update(float timeStep){
	numAdverts = adverts.size();
	for(int i=0; i<numAdverts; i++){
		adverts[i]->updateAdvert(timeStep);
	}
}

void ofWindowSetup::renderAdverts(){
	for(int i=0; i<numAdverts; i++){
		adverts[i]->render();
	}
}

void ofWindowSetup::drawAdvertImage(ofImage *_cImg){
	for(int i=0; i<numAdverts; i++){
		adverts[i]->drawAdvertImage(_cImg);
	}
}

void ofWindowSetup::debugRender(){
	renderAdverts();
}

void ofWindowSetup::addAdvert(ofPopUpAd* _p){
	adverts.push_back(_p);
}

void ofWindowSetup::deleteAdvert(ofPopUpAd* _p){
	for(int i=0; i<adverts.size(); i++){
		if(_p == adverts[i]){
			adverts.erase(adverts.begin() + i);
			delete _p;
			return;
		}
	}
}

void ofWindowSetup::removeAdvert(ofPopUpAd*p){
	for(int i=0; i<adverts.size(); i++){
		if(adverts[i] == p){
			adverts.erase(adverts.begin() + i);
			return;
		}
	}
}


void ofWindowSetup::add(ofPopUpAd*p){
	adverts.push_back(p);
}


bool ofWindowSetup::hasAdvert(ofPopUpAd*p){
	for(int i=0; i<numAdverts; i++){
		if(adverts[i] == p) return true;	
	}
	return false;
}


bool ofWindowSetup::has(ofPopUpAd*p){
	return hasAdvert(p);
}


int ofWindowSetup::getNumAdverts(){
	return numAdverts;	
}


vector<ofPopUpAd*>& ofWindowSetup::getAdverts(){
	return adverts;
}



void ofWindowSetup::removeAllAdverts(){
	adverts.clear();
}

void ofWindowSetup::deleteAllAdverts(){
	for(int i=0; i<numAdverts; i++){
		delete adverts[i];
	}
	adverts.clear();
}


void ofWindowSetup::removeAll(){
	removeAllAdverts();
}

void ofWindowSetup::deleteAll(){
	deleteAllAdverts();
}

void ofWindowSetup::reserveForAdverts(int numberOfAdverts){
	adverts.reserve(numberOfAdverts);
}










