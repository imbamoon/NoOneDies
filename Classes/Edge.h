#ifndef __NoOneDies__Edge__
#define __NoOneDies__Edge__

#include <iostream>

#include <cocos2d.h>

USING_NS_CC;

class Edge :public Node {
public:
	virtual bool init();
	CREATE_FUNC(Edge);
};

#endif