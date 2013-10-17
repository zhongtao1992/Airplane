#ifndef __AirPlane__AudioEngine__
#define __AirPlane__AudioEngine__

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
class AudioEngine:
	public CocosDenshion::SimpleAudioEngine
{
public:
	static AudioEngine* sharedEngine();
	void purge();
	bool init();
};
#endif