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
/*
void Vehicle::setup(b2World * b2dworld, ofRectangle rec) {
	setup(b2dworld, rec.x, rec.y, rec.width, rec.height);
}

//------------------------------------------------
void Vehicle::setup(b2World * b2dworld, float x, float y, float w, float h) {
	
	if(b2dworld == NULL) {
		ofLog(OF_LOG_NOTICE, "- must have a valid world -");
		return;
	}
	
	b2PolygonShape shape;
	shape.SetAsBox((w/2)/OFX_BOX2D_SCALE, (h/2)/OFX_BOX2D_SCALE);
	
	fixture.shape		= &shape;
	fixture.density		= density;
	fixture.friction	= friction;
	fixture.restitution = bounce;
	
	b2BodyDef bodyDef;
	if(density == 0.f) bodyDef.type	= b2_staticBody;
	else               bodyDef.type	= b2_dynamicBody;
	bodyDef.position.Set(x/OFX_BOX2D_SCALE, y/OFX_BOX2D_SCALE);
	
	
	body = b2dworld->CreateBody(&bodyDef);
	body->CreateFixture(&fixture);
    
    updateMesh();
    alive = true;
}
*/
void Vehicle::update()
{
	
	this->addForce(ofVec2f(speed,0),1.0f);
	/*if(this->getPosition().x > 620){
		this->destroy();

	}*/
	if(this->getRotation() >= 90.0 || this->getRotation() <= -90.0)
		this->setRotation(0.0);
}

void Vehicle::draw()
{
	if(body == NULL) {
		return;	
	}

	ofSetColor(255);
	ofPushMatrix();
	ofTranslate(this->getPosition().x,this->getPosition().y);
	ofRotate(this->getRotation());
	//mesh.draw(ofGetFill()==OF_FILLED?OF_MESH_FILL:OF_MESH_WIREFRAME);
	avatar.draw(-15,-15,30,30);
	ofPopMatrix();
	
}

void Vehicle::sound(){
	locomotive.play();
}
/*
void Vehicle::setColor(ofColor c){
	this->color = c;
}
ofColor Vehicle::getColor(){
	return this->color;
}*/

