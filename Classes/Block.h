#ifndef __NoOneDies__Block__
#define __NoOneDies__Block__

#include <iostream>
#include <cocos2d.h>

USING_NS_CC;

class Block :public Sprite {

public:
	bool init();
	void update(float dt);
	CREATE_FUNC(Block);
};

#endif