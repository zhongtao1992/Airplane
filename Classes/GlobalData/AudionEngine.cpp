#include "GlobalData/AudioEngine.h"
static AudioEngine* _sharedEngine=NULL;
using namespace CocosDenshion;
USING_NS_CC;

AudioEngine* AudioEngine::sharedEngine()
{
	if (_sharedEngine==NULL)
	{
		_sharedEngine=new AudioEngine();
		_sharedEngine->init();
	}
	return _sharedEngine;
}

bool AudioEngine::init()
{
	this->preloadBackgroundMusic("sound/game_music.mp3");
	this->preloadBackgroundMusic("sound/game_over.mp3");
	this->preloadEffect("sound/achievement.mp3");
	this->preloadEffect("sound/big_spaceship_flying.mp3");
	this->preloadEffect("sound/bullet.mp3");
	this->preloadEffect("sound/button.mp3");
	this->preloadEffect("sound/enemy0_down.mp3");
	this->preloadEffect("sound/enemy1_down.mp3");
	this->preloadEffect("sound/enemy2_down.mp3");
	this->preloadEffect("sound/get_bomb.mp3");
	this->preloadEffect("sound/get_double_laser.mp3");
	this->preloadEffect("sound/out_porp.mp3");
	this->preloadEffect("sound/use_bomb.mp3");

	return true;
}