#ifndef __AirPlane__StartLayer__
#define __AirPlane__StartLayer__

#include "cocos2d.h"
class StartLayer:
	public cocos2d::CCLayer
{
public:
	CREATE_FUNC(StartLayer);
	StartLayer():startBG(NULL),appName(NULL),loadingSprite(NULL){}
	~StartLayer(){}
public:
	//做个进度条
	virtual bool init();
	void loading(cocos2d::CCObject* sender);
	void loadingFinished(cocos2d::CCNode* node);
public:
	//加载完资源就加载动画相关
	void cacheInit();
	void enterGame();
private:
	cocos2d::CCSprite* startBG;
	cocos2d::CCSprite* appName;
	cocos2d::CCSprite* loadingSprite;
};
#endif