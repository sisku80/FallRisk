#pragma once
#include "ofMain.h"
#include "ofxBox2dRect.h"

class TrackPart : public ofxBox2dRect
{	
	private:
		
		int instability;
		ofImage structure;
		int iter;
		ofImage column;

	public:
		TrackPart();
		~TrackPart();


		//void setup(b2World * b2dworld, ofRectangle rec, int instab);
		//void setup(b2World * b2dworld, float x, float y, float w, float h, int instab);
		void update();//float deltaTime);
		void draw();
		void setInstability(int instab);
	
};