#ifndef __AirPlane__StartScene__
#define __AirPlane__StartScene__

//做个统一：
//每个Layer里面的精灵命名用小写开头
//添加到Scene里面的Layer命名用_(下划线)开头

#include "cocos2d.h"
#include "StartScene/StartLayer.h"
class StartScene:
	public cocos2d::CCScene
{
public:
	CREATE_FUNC(StartScene);
public:
	virtual bool init();
private:
	StartLayer* _startLayer;
};
#endif