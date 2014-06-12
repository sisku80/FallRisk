#pragma once
#include "ofMain.h"
#include "ofxBox2dRect.h"

class Vehicle : public ofxBox2dRect
{	
	private:
		ofColor color;
		float speed;
		ofSoundPlayer  locomotive;
		ofImage avatar;

	public:
		Vehicle();
		~Vehicle();

		void update();//float deltaTime);
		void draw();
		void sound();

		void setSpeed(float speed);
		float getSpeed();

	
};