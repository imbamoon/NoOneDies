#include "GameScene.h"
#include "GameOverScene.h"

Scene * MyGame::createScene(int heroCount){
	auto s = Scene::createWithPhysics();
	//s->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	s->getPhysicsWorld()->setGravity(Vec2(0, -1000));
	auto l = MyGame::create(heroCount);
	s->addChild(l);
	return s;
}

MyGame * MyGame::create(int heroCount){
	auto _ins = new MyGame();
	_ins->initWithHeroCount(heroCount);
	_ins->autorelease();
	return _ins;
}


bool MyGame::initWithHeroCount(int heroCount){
	LayerColor::initWithColor(Color4B(255, 255, 255, 255));

	_heroCount = heroCount;

	addContactListener();
	addUserTouchListener();
	addGcs(heroCount);

	scheduleUpdate();
	return true;
}

void MyGame::addGcs(int heroCount){
	Size size = Director::getInstance()->getVisibleSize();
	float startPosition = 30;
	float gap = (size.height - startPosition) / heroCount;
	for (int i = 0; i<heroCount; i++) {
		gcs.insert(0, GameController::create(this, startPosition + gap*i));
	}
}

void MyGame::addContactListener(){
	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [this](PhysicsContact & contact){

		this->unscheduleUpdate();

		auto dir = Director::getInstance();
		dir->getEventDispatcher()->removeEventListener(contactListener);
		dir->getEventDispatcher()->removeEventListener(touchListener);
		dir->replaceScene(GameOver::createScene(_heroCount, 20));
		return true;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}


void MyGame::addUserTouchListener(){
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [this](Touch * t, Event * e){

		for (auto it = this->gcs.begin(); it != this->gcs.end(); it++) {
			auto gc = *it;
			if (gc->hitTestPoint(t->getLocation())){
				gc->onUserTouch();
				break;
			}
		}

		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void MyGame::update(float dt){
	for (auto it = gcs.begin(); it != gcs.end(); it++) {
		(*it)->onUpdate(dt);
	}
}