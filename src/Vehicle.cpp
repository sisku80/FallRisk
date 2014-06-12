#include "Vehicle.h"

Vehicle::Vehicle()
{
	speed = 20;
	avatar.loadImage("train.gif");
	locomotive.loadSound("locomotive.wav");
	locomotive.setVolume(1.0f);
	locomotive.setLoop(true);
	
}

Vehicle::~Vehicle()
{
	
}

void Vehicle::update()
{
	
	this->addForce(ofVec2f(speed,0),1.0f);

	if(this->getRotation() >= 90.0 || this->getRotation() <= -90.0)
		this->setRotation(0.0);
}

void Vehicle::draw()
{
	if(body == NULL) {
		return;	
	}
	//Dibuixa la imatge sobre el Box2dRect
	ofSetColor(255);
	ofPushMatrix();
	ofTranslate(this->getPosition().x,this->getPosition().y);
	ofRotate(this->getRotation());
	avatar.draw(-15,-15,30,30);
	ofPopMatrix();
	
}

void Vehicle::sound(){
	locomotive.play();
}


