#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

class Vehicle : public ofxBox2dRect
{	
	public:
		Vehicle();
		~Vehicle();

		bool setup();
		void update();//float deltaTime);
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		//void addThrust(float thrust);

		void setPosition(ofPoint pos);
		ofPoint getPosition();

		void setDirection(ofPoint direction);
		ofPoint getDirection();

		void setRotation(float angle);
		void addRotation(float angle);
		float getRotation();

		void setSize(float size);
		float getSize();

		void setSpeed(float speed);
		float getSpeed();

		void setColor(ofColor c);
		ofColor getColor();
		
	private:
		ofPoint position, direction;
		ofColor color;
		float rotation, size, speed;
		//ofSoundPlayer  thrustSound;
};