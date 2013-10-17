#ifndef __AirPlane__MenuLayer__
#define __AirPlane__MenuLayer__

#include "cocos2d.h"
class MenuLayer:
	public cocos2d::CCLayer
{
public:
	CREATE_FUNC(MenuLayer);
	bool init();

	void onEnter();
	void onExit();
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	//一些回调
	void resume_Call_Back(cocos2d::CCObject* sender);
	void restart_Call_Back(cocos2d::CCObject* sender);
	void quit_Call_Back(cocos2d::CCObject* sender);
};
#endif