#ifndef __AirPlane__GlobalData__
#define __AirPlane__GlobalData__

static int finalScore=0;
static float gameSpeed=0.0f;
#include "cocos2d.h"
class GlobalData:
	public cocos2d::CCObject
{
public:
	static GlobalData* sharedGlobalDate();
	bool init();

	void flush();
};
#endif