#pragma once

#include "ofMain.h"

#include "ofxKinectCommonBridge.h"
#include "ofxBox2d.h"
#include "Vehicle.h"
#include "TrackPart.h"

#define M_PI 3.1416


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
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

		ofxKinectCommonBridge kinect;
		ofxBox2d                            box2d;			  //	the box2d world
		vector    <ofPtr<ofxBox2dCircle> >	circles;		  //	default box2d circles
		vector	  <ofPtr<ofxBox2dRect> >	boxes;			  //	defalut box2d rects

		int score;
		bool started;
		int level;
		ofImage ambientCanyon;
		ofSoundPlayer mines;
		ofSoundPlayer  explosion;
		ofSoundPlayer  splash;

		void generateLevel();
		void resetTrains();
		bool allTrainsDone();

		vector    <ofPtr<Vehicle> > vehicles;				  //	default FallRisk vehicles
		vector	  <ofPtr<TrackPart> > tracks;				  //	default FallRisk tracks

		//Arms pieces
		ofxBox2dRect LHumerusTrack;
		ofxBox2dRect RHumerusTrack;
		ofxBox2dRect LRadiusTrack;
		ofxBox2dRect RRadiusTrack;
		
};
