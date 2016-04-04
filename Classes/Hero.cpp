#include "Hero.h"
#include "FlashTool.h"


bool Hero::init(){
	Sprite::init();

	Size s = Size(44, 52);

	runAction(RepeatForever::create(FlashTool::readJsonSpriteSheet("Hero.json", 0.2f)));
	setContentSize(s);
	setPhysicsBody(PhysicsBody::createBox(s));
	getPhysicsBody()->setRotationEnable(false);
	getPhysicsBody()->setContactTestBitmask(1);

	return true;
}