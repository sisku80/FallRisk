#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofSetFrameRate(60);
	
	// Kinect initialization code
	kinect.initSensor();

	// We first set up data streams for the Kinect (color, depth and skeleton tracking)
	kinect.initColorStream(640, 480, true);
	kinect.initDepthStream(640, 480, true);
	kinect.initSkeletonStream(false);

	// Launch Kinect
	kinect.start();

	box2d.init();
	box2d.setGravity(0, 10);
	box2d.createBounds();
	box2d.setFPS(30.0);
	box2d.registerGrabbing();

	ambientCanyon.loadImage("westernvalley.gif");
	
	LHumerusTrack.setup(box2d.getWorld(),0,0, 80, 20);
	RHumerusTrack.setup(box2d.getWorld(),0,0, 80, 20);
	LRadiusTrack.setup( box2d.getWorld(),0,0, 70, 20);
	RRadiusTrack.setup( box2d.getWorld(),0,0, 70, 20);

	explosion.loadSound("explosion.wav");
	explosion.setVolume(1.0f);
	explosion.setLoop(false);
	splash.loadSound("splash.wav");
	splash.setVolume(1.0f);
	splash.setLoop(false);
	mines.loadSound("mines.mp3");
	mines.setVolume(0.6f);
	mines.setLoop(true);
	mines.play();

	score = 0;
	level = 1;
	started = false;

	//SET UP THE TRACKS:
	generateLevel();
}

//--------------------------------------------------------------
void testApp::update(){

	kinect.update();	

	box2d.update();	
	if(vehicles.size() == 0){
		vehicles.push_back(ofPtr<Vehicle>(new Vehicle));
		vehicles.back().get()->setPhysics(3.0, 0.0, 0.1);
		vehicles.back().get()->setVelocity(5,0);
		vehicles.back().get()->setup(box2d.getWorld(), 20, 230 , 30, 30);
		
	}

	if(started != false){
		
		//SE ACTUALIZAN LOS VEHICULOS
		for(int i=0; i< vehicles.size(); i++) {
			vehicles[i].get()->update();
			if(vehicles[i].get()->getPosition().x > ofGetWidth()-20){
				//vehicles[i].get()->destroy();
				//vehicles[i].get()->setPosition(20,220);
				score += 1;
			}
		}
		
		for(int i=0; i<vehicles.size(); i++) {
			//SI LLEGAN AL FINAL SE ENVIAN AL LIMBO A ESPERAR (PORQUE NO SE PUEDEN DESTRUIR...?)
			if( vehicles[i].get()->getPosition().x > ofGetWidth()-20){
				vehicles[i].get()->setPosition(2000,2000);
				//generateLevel();
			}	
		}
		for(int i = 0 ; i < vehicles.size() ; i++){
			//SI CAEN AL AGUA SE REINICIA EL NIVEL
			if( vehicles[i].get()->getPosition().y > ofGetHeight()-50 && 
				vehicles[i].get()->getPosition().x > 0 && 
				vehicles[i].get()->getPosition().x < ofGetWidth()){
				splash.play();
				//vehicles[i].get()->setPosition(20,220);
				started = false;
				resetTrains();
			}
		}
		//if all trains are done: 
		if(allTrainsDone() == true){
			level++;
			generateLevel();
			started = false;
			for(int i=0; i<vehicles.size(); i++) {
				vehicles[i].get()->setPosition(15,230);
			}
			if(level%3 == 0){
				vehicles.push_back(ofPtr<Vehicle>(new Vehicle));
				vehicles.back().get()->setPhysics(3.0, 0.0, 0.1);
				vehicles.back().get()->setVelocity(5,0);
				vehicles.back().get()->setup(box2d.getWorld(), 20, 230 , 30, 30);
			}
		}

		
		

	}
}

//--------------------------------------------------------------
void testApp::draw(){

	ofDisableAlphaBlending();
		ofSetColor(255);
		kinect.draw(0, 0);
	ofEnableAlphaBlending();

	for(int i=0; i<circles.size(); i++) {
		ofFill();
		ofSetHexColor(0xf6c738);
		circles[i].get()->draw();
	}
	
	for(int i=0; i<boxes.size(); i++) {
		ofFill();
		ofSetHexColor(0xBF2545);
		boxes[i].get()->draw();
	}
	for(int i=0; i<vehicles.size(); i++) {
		ofFill();
		ofSetColor(50,200,50);
		vehicles[i].get()->draw();
	}
	
	for(int i = 0 ; i < tracks.size() ; i++){
		ofFill();
		ofSetColor(40,180,70);
		tracks[i].get()->draw();
	}
	LHumerusTrack.draw();
	RHumerusTrack.draw();
	LRadiusTrack.draw();
	RRadiusTrack.draw();
	ofSetColor(50,50,200);
	//train.draw();
	// draw the ground
	box2d.drawGround();
	
	string info = "";
	/*info += "Press [c] for circles\n";
	info += "Press [b] for blocks\n";
	info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
	info += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";*/
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
	info += "Time: "+ofToString(ofGetElapsedTimef())+"\n";
	info += "Score: "+ofToString(score)+"\n";
	info += "Level: "+ofToString(level)+"\n";
	ofFill();	
	ofSetColor(255);
	ofDrawBitmapString(info, 30, 30);

	//SCENARIO ELEMENTS
	ofSetColor(50,100,230,180);
	ofRect(0,ofGetHeight()-50,ofGetWidth(),50); //THE RIVER!!!
	ofSetColor(255);
	ambientCanyon.draw(0,0);					//THE VALLEY!!


	if(kinect.isNewSkeleton())
	{
		ofSetColor(255);
		for(int i = 0 ; i < kinect.getSkeletons().size(); i++)
		{
			if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HEAD) != kinect.getSkeletons().at(i).end())
			{
				SkeletonBone headBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HEAD)->second;
				ofVec2f headScreenPosition(headBone.getScreenPosition().x, headBone.getScreenPosition().y);
				if(started == false){
					ofSetColor(255,255,100);
					ofCircle(headScreenPosition.x+50, headScreenPosition.y-30, 25);
					ofSetColor(0);
					ofDrawBitmapString("START",headScreenPosition.x+30, headScreenPosition.y-30);
				}
				//RIGHT SHOULDER
				ofSetColor(100,80,40);
				if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_SHOULDER_RIGHT) != kinect.getSkeletons().at(i).end())
				{
					SkeletonBone RShoulderBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_SHOULDER_RIGHT)->second;
					ofVec2f partScreenPosition(RShoulderBone.getScreenPosition().x, RShoulderBone.getScreenPosition().y);
					ofCircle(partScreenPosition.x, partScreenPosition.y, 10);
					//LEFT SHOULDER
					if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_SHOULDER_LEFT) != kinect.getSkeletons().at(i).end())
					{
						SkeletonBone LShoulderBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_SHOULDER_LEFT)->second;
						ofVec2f partScreenPosition(LShoulderBone.getScreenPosition().x, LShoulderBone.getScreenPosition().y);
						ofCircle(partScreenPosition.x, partScreenPosition.y, 10);
						//RIGHT HAND
						if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_WRIST_RIGHT) != kinect.getSkeletons().at(i).end())
						{
							SkeletonBone RHandBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_WRIST_RIGHT)->second;
							ofVec2f partScreenPosition(RHandBone.getScreenPosition().x, RHandBone.getScreenPosition().y);
							ofCircle(partScreenPosition.x, partScreenPosition.y, 10);

							//LEFT HAND
							if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_WRIST_LEFT) != kinect.getSkeletons().at(i).end())
							{
								SkeletonBone LHandBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_WRIST_LEFT)->second;
								ofVec2f partScreenPosition(LHandBone.getScreenPosition().x, LHandBone.getScreenPosition().y);
								ofCircle(partScreenPosition.x, partScreenPosition.y, 10);

								//RIGHT ELBOW
								if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_ELBOW_RIGHT) != kinect.getSkeletons().at(i).end())
								{
									SkeletonBone RElbowBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_ELBOW_RIGHT)->second;
									ofVec2f partScreenPosition(RElbowBone.getScreenPosition().x, RElbowBone.getScreenPosition().y);
									ofCircle(partScreenPosition.x, partScreenPosition.y, 10);

									//LEFT ELBOW
									if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_ELBOW_LEFT) != kinect.getSkeletons().at(i).end())
									{
										SkeletonBone LElbowBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_ELBOW_LEFT)->second;
										ofVec2f partScreenPosition(LElbowBone.getScreenPosition().x, LElbowBone.getScreenPosition().y);
										ofCircle(partScreenPosition.x, partScreenPosition.y, 10);

										//Starting the game...
										if(started == false){
											if( RHandBone.getScreenPosition().x > (headScreenPosition.x+50) &&
												RHandBone.getScreenPosition().x < (headScreenPosition.x+80) &&
												RHandBone.getScreenPosition().y > (headScreenPosition.y-30) &&
												RHandBone.getScreenPosition().y < (headScreenPosition.y  )) {
												started = true;
												explosion.play();
											}
										}
										//Con todos los bones guardados...

										float LHumerusX = LElbowBone.getScreenPosition().x - LShoulderBone.getScreenPosition().x;
										float LHumerusY = LElbowBone.getScreenPosition().y - LShoulderBone.getScreenPosition().y;

										float LRadiusX  = LHandBone.getScreenPosition().x - LElbowBone.getScreenPosition().x;
										float LRadiusY  = LHandBone.getScreenPosition().y - LElbowBone.getScreenPosition().y;

										float RHumerusX = RElbowBone.getScreenPosition().x - RShoulderBone.getScreenPosition().x;
										float RHumerusY = RElbowBone.getScreenPosition().y - RShoulderBone.getScreenPosition().y;

										float RRadiusX  = RHandBone.getScreenPosition().x - RElbowBone.getScreenPosition().x;
										float RRadiusY  = RHandBone.getScreenPosition().y - RElbowBone.getScreenPosition().y;

										float LHumerusAngle = 90 - atan2(LHumerusX,LHumerusY)*180/M_PI;
										LHumerusTrack.setPosition((LElbowBone.getScreenPosition().x + LShoulderBone.getScreenPosition().x) / 2,
																  (LElbowBone.getScreenPosition().y + LShoulderBone.getScreenPosition().y) / 2);
										LHumerusTrack.setRotation(LHumerusAngle);

										float RHumerusAngle = 90 - atan2(RHumerusX,RHumerusY)*180/M_PI;
										RHumerusTrack.setPosition((RElbowBone.getScreenPosition().x + RShoulderBone.getScreenPosition().x) / 2,
																  (RElbowBone.getScreenPosition().y + RShoulderBone.getScreenPosition().y) / 2);
										RHumerusTrack.setRotation(RHumerusAngle);

										float LRadiusAngle = 90 - atan2(LRadiusX,LRadiusY)*180/M_PI;
										LRadiusTrack.setPosition((LHandBone.getScreenPosition().x + LElbowBone.getScreenPosition().x) / 2,
																 (LHandBone.getScreenPosition().y + LElbowBone.getScreenPosition().y) / 2);
										LRadiusTrack.setRotation(LRadiusAngle);

										float RRadiusAngle = 90 - atan2(RRadiusX,RRadiusY)*180/M_PI;
										RRadiusTrack.setPosition((RHandBone.getScreenPosition().x + RElbowBone.getScreenPosition().x) / 2,
																 (RHandBone.getScreenPosition().y + RElbowBone.getScreenPosition().y) / 2);
										RRadiusTrack.setRotation(RRadiusAngle);

										
									}
								}
							}
						}
					}
				}
				return;
			}
		}
	}
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	if(key == 'c') {
		float r = ofRandom(4, 20);
		circles.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
		circles.back().get()->setPhysics(3.0, 0.53, 0.1);
		circles.back().get()->setup(box2d.getWorld(), mouseX, mouseY, r);
		
	}
	
	if(key == 'b') {
		float w = ofRandom(4, 20);
		float h = ofRandom(4, 20);
		boxes.push_back(ofPtr<ofxBox2dRect>(new ofxBox2dRect));
		boxes.back().get()->setPhysics(3.0, 0.53, 0.1);
		boxes.back().get()->setup(box2d.getWorld(), mouseX, mouseY, w, h);
	}

	//Si pulsamos V ahora tambien aparecen trenes!
	if(key == 'v') {
		vehicles.push_back(ofPtr<Vehicle>(new Vehicle));
		vehicles.back().get()->setPhysics(3.0, 0.0, 0.1);
		vehicles.back().get()->setVelocity(5,0);
		vehicles.back().get()->setup(box2d.getWorld(), mouseX, mouseY , 30, 30);
	}
	
	if(key == 't') ofToggleFullscreen();

}


//Funcion para generar los niveles automaticamente
void testApp::generateLevel(){
	
	if(tracks.size() > 0){
		for(int i = 0; i < tracks.size() ; i++){
			tracks[i].get()->setPosition(1000,1000);
			//tracks[i].get()->destroy();
		}
		tracks.clear();
	}
	
	//track 1
	tracks.push_back(ofPtr<TrackPart>(new TrackPart));
	tracks.back().get()->setup(box2d.getWorld(), 40,  250, 80, 20);
	tracks.back().get()->setPhysics(3.0, 0.0, 0.1);
	tracks.back().get()->setRotation(-5);

	for(int t = 1 ; t < 7 ; t++){
		if(t != 4){
			float w = ofRandom(30, 85);
			float h = 10;
			float r = ofRandom(-30,30);
			int instab = ofRandom(0,70);
			tracks.push_back(ofPtr<TrackPart>(new TrackPart));
			tracks.back().get()->setup(box2d.getWorld(), 40+80*t,  250+instab, w, h);
			tracks.back().get()->setPhysics(3.0, 0.0, 0.1);
			tracks.back().get()->setRotation(r);
			tracks.back().get()->setInstability(instab);
		}
	}
	//last track
	tracks.push_back(ofPtr<TrackPart>(new TrackPart));
	tracks.back().get()->setup(box2d.getWorld(), ofGetWidth()-40,  250, 80, 20);
	tracks.back().get()->setPhysics(3.0, 0.0, 0.1);
	tracks.back().get()->setRotation(0);
}

//Reset del vector de vehiculos a la posicion inicial
void testApp::resetTrains(){
	for(int i = 0 ; i < vehicles.size() ; i++){
		vehicles[i].get()->setPosition(20,220);
	}
}

//Comprueba si todos los trenes del nivel han pasado al otro lado
bool testApp::allTrainsDone(){
	bool flag = true;
	for(int i = 0 ; i < vehicles.size() ; i++){
		if(!(vehicles[i].get()->getPosition().x > ofGetWidth() && vehicles[i].get()->getPosition().y > ofGetHeight())){
			flag = false;
		}
	}
	return flag;
}
//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
