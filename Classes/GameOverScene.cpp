#include "GameOverScene.h"
#include "StartUpScene.h"
#include "GameScene.h"

Scene * GameOver::createScene(int currentHeroCount, double score){

	auto s = Scene::create();
	auto l = GameOver::create(currentHeroCount, score);
	s->addChild(l);
	return s;
}

GameOver * GameOver::create(int currentHeroCount, double score){
	auto _ins = new GameOver();
	_ins->initWithCurrentHeroCountAndScore(currentHeroCount, score);
	_ins->autorelease();
	return _ins;
}


bool GameOver::initWithCurrentHeroCountAndScore(int currentHeroCount, double score){
	LayerColor::initWithColor(Color4B(255, 255, 255, 255));

	_currentHeroCount = currentHeroCount;
	_score = score;

	auto label = Label::create();
	label->setString("Game Over");
	label->setColor(Color3B(0, 0, 0));
	label->setSystemFontSize(40);
	addChild(label);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	label->setPosition(visibleSize.width / 2, visibleSize.height - label->getContentSize().height / 2 - 80);

	//add replay btn
	btnReplay = createButton("Replay", 32);
	btnReplay->setPosition(visibleSize.width / 2, label->getPositionY() - label->getContentSize().height / 2 - 150);
	addChild(btnReplay);
	//add gohome btn
	btnGoHome = createButton("Home", 32);
	btnGoHome->setPosition(visibleSize.width / 2, btnReplay->getPositionY() - btnReplay->getContentSize().height / 2 - 50);
	addChild(btnGoHome);

	
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [this](Touch *t, Event *e){
		if (this->btnGoHome->getBoundingBox().containsPoint(t->getLocation())) {
			Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);
			Director::getInstance()->replaceScene(StartUp::createScene());
		}
		else if (this->btnReplay->getBoundingBox().containsPoint(t->getLocation())){
			Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);
			Director::getInstance()->replaceScene(MyGame::createScene(this->_currentHeroCount));
		}

		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}


Label * GameOver::createButton(std::string text, float fontSize){
	auto l = Label::create();
	l->setString(text);
	l->setColor(Color3B::BLACK);
	l->setSystemFontSize(fontSize);
	return l;
}