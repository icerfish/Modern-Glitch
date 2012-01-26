#pragma once

#include "ofBaseGui.h"
#include "ofxPhysics2d.h"

#define MAX_PARTICLES 200

class ofErrorBall : public ofBaseGui{
    
public:    
    void setup() {
        
        ballIndex = 0;
        
        currentMilli = 0;
        
        sampleBallStrings.push_back("osx1.png");
        sampleBallStrings.push_back("osx2.png");
        sampleBallStrings.push_back("osx3.png");
        sampleBallStrings.push_back("osx4.png");
        sampleBallStrings.push_back("osx5.png");
        sampleBallStrings.push_back("osx6.png");
        
        for(int i = 0; i < sampleBallStrings.size(); i++){
            ofImage* ball = new ofImage();
            ball->allocate(20, 20, OF_IMAGE_COLOR);
            ball->loadImage(sampleBallStrings[i]);
            eBallArray.push_back( ball );
        }
        
        ofPoint gravity(0, 1);
        physics = new ofxPhysics2d(gravity);
        physics->checkBounds(true);
        physics->enableCollisions(true);
        physics->setNumIterations(10);
        physics->_resX = resX;
        physics->_resY = resY;
        
        bCreateParticles = false;
        mouseParticle = new ofxParticle();
        mouseParticle->setActive(false);
        mouseSpring = NULL;
        newParticle = NULL;
        
        newParticleIncrement = 0;
        bCreateParticleString = false;
        beginParticleString = NULL;
        endParticleString = NULL;
        
        ofRegisterMouseEvents(this);
        ofRegisterKeyEvents(this);
        
        currentFrame = 0;
		bGuiActive = false;
	}
    
    void update(){
        
        mouseParticle->set(ofGetAppPtr()->mouseX, ofGetAppPtr()->mouseY);
        if(newParticle){
            newParticle->setRadius((sin(newParticleIncrement)*5) + 10);
            newParticleIncrement+= 0.01f;
            newParticle->moveTo(ofGetAppPtr()->mouseX, ofGetAppPtr()->mouseY);
        }
        if(bCreateParticles){
            if(ofGetFrameNum() % 5 == 0){
                float radius = ofRandom(5, 20);
                float mass = radius * 0.5f;
                ofxParticle* p = new ofxParticle(ofGetAppPtr()->mouseX, ofGetAppPtr()->mouseY, radius, mass);
                float randomStep = 5;
                ofPoint impulse(ofRandom(-randomStep, randomStep), ofRandom(-randomStep, randomStep));
                p->applyImpulse(impulse);
                particles.push_back(p);
                physics->add(p);
            }
        }
        for(int i=0; i<particles.size(); i++){
            if(particles[i]->y > ofGetHeight() + particles[i]->getRadius()){
                while(physics->getConstraintWithParticle(particles[i]) != NULL){
                    physics->deleteConstraintsWithParticle(particles[i]);
                }
                physics->deleteParticle(particles[i]);
                particles.erase(particles.begin()+i);
            }
        }
        physics->update();
        
//        if ((ofGetElapsedTimeMillis() - currentMilli) > 150000) {
//            physics->deleteAll();
//            particles.clear();
//            currentMilli = ofGetElapsedTimeMillis();
//        }
    }
	
	void draw(){
        
		currentFrame = ofGetFrameNum();
        
        if(ballIndex > 4) {
            ballIndex = 0;
        } else {
            ballIndex++;
        }
        
		ofPushStyle();
		ofPushMatrix();
        
        ofNoFill();
        ofSetColor(240, 240, 240);
        physics->renderParticles();
        physics->drawParticleImage(eBallArray[ballIndex]);
        ofSetColor(100, 100, 100);
        physics->renderConstraints();
        ofSetColor(255,255,255);
        
//        string info = "num particles: " + ofToString(physics->getNumParticles()) + "\n" + 
//        "num constraints: " + ofToString(physics->getNumConstraints()) + "\n" + 
//        "fps: " + ofToString(ofGetFrameRate());
//        ofDrawBitmapString(info, 20,20);
        
        ofPopMatrix();
		ofPopStyle();
		
	}
    
    void clear(){
		eBallArray.clear();
	}
    
    //-----------------------------------------------------------------
    
    void createParticleString(ofxParticle*begin, ofxParticle*end, int numParticles){
        ofPoint step = (*end - *begin) / (numParticles-1);
        ofPoint particlePos = *begin;
        ofxParticle* prevParticle = begin;
        prevParticle->setActive(false);
        end->setActive(false);
        particlePos += step;
        if(!physics->has(begin)) physics->add(begin);
        if(!physics->has(end)) physics->add(end);
        for(int i=1; i<numParticles; i++){
            ofxParticle* p = new ofxParticle(particlePos, 5);
            float rest = prevParticle->distanceTo(p);
            ofxSpring* s = new ofxSpring(prevParticle, p, rest, 1.1);
            physics->add(p);
            physics->add(s);
            if(i==numParticles-1)p->setActive(false);
            prevParticle = p;
            particlePos += step;
        }
        float rest = prevParticle->distanceTo(end);
        ofxSpring* s = new ofxSpring(prevParticle, end, rest);
        physics->add(s);
    }
    
    virtual void keyPressed(ofKeyEventArgs & args){
        if(args.key){
        }
    }
    
    virtual void keyReleased(ofKeyEventArgs & args){
        if(args.key){
            physics->deleteAll();
            particles.clear();
        }
    }
    
    virtual void mouseMoved(ofMouseEventArgs & args){
        
	}
	
	virtual void mousePressed(ofMouseEventArgs & args){
        if(args.button == 0){
            if(bCreateParticleString){
                beginParticleString = new ofxParticle(args.x, args.y, 5);
                beginParticleString->setActive(false);
                physics->add(beginParticleString);
            } else {
                ofPoint mousePoint = ofPoint(args.x, args.y);
                ofxParticle* particleUnderMouse = physics->getParticleUnderPoint(mousePoint);
                if(particleUnderMouse){
                    float rest = mouseParticle->distanceTo(particleUnderMouse);
                    mouseSpring = new ofxSpring(mouseParticle, particleUnderMouse, rest);
                    physics->add(mouseSpring);
                } else {
                    if(newParticle == NULL){
                        newParticle = new ofxParticle(args.x, args.y, 1);
                        newParticle->setActive(false);
                        physics->add(newParticle);
                        particles.push_back(newParticle);
                    } 
                }
                
            }
        }
        if(args.button == 2){
            bCreateParticles = true;
        }
        
	}
	
	virtual void mouseDragged(ofMouseEventArgs & args){
        
	}
	
	virtual void mouseReleased(ofMouseEventArgs & args){
        if(bCreateParticleString){
            if(beginParticleString){
                endParticleString = new ofxParticle(args.x, args.y, 5);
                endParticleString->setActive(false);
                int numParticles = (int)(beginParticleString->distanceTo(endParticleString)/10);
                createParticleString(beginParticleString, endParticleString, numParticles);
                beginParticleString = NULL;
                endParticleString = NULL;
            }
            bCreateParticleString = false;
        } 
        
        if(mouseSpring){
            physics->deleteConstraint(mouseSpring);
            mouseSpring = NULL;
        }
        if(newParticle){
            newParticle->setActive(true);
            newParticle->setMass(newParticle->getRadius() * 0.5);
            newParticle = NULL;
            newParticleIncrement = 0;
        }
        bCreateParticles = false;	
	}

    
protected:
	
	void setValue(float mx, float my, bool bCheck){
        
		if( ofGetFrameNum() - currentFrame > 1 ){
			bGuiActive = false;
			return; 
		}
    }
    
	ofxPhysics2d*physics;
	ofxParticle* mouseParticle;
	ofxSpring*mouseSpring;
	ofxParticle* newParticle;
	bool bCreateParticles;
	float newParticleIncrement;
	
	bool bCreateParticleString;
	ofxParticle* beginParticleString;
	ofxParticle* endParticleString;
	vector<ofxParticle*>particles;
    ofImage eBalls;
    
    int ballIndex;
    
    int currentMilli;
    
    vector<ofImage*> eBallArray;
    vector<string> sampleBallStrings;
    
};