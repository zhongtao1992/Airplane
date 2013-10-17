#ifndef __AirPlane__PanelLayer__
#define __AirPlane__PanelLayer__

#include "cocos2d.h"
class PanelLayer:
	public cocos2d::CCLayer
{
public:
	PanelLayer();
	~PanelLayer();

public:
	CREATE_FUNC(PanelLayer);
	bool init();

	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	bool clicked;
	void click(float dt);

	//回调
	void pause_Call_Back(cocos2d::CCObject* sender);

	//得分
	cocos2d::CCLabelBMFont* scoreLabel;
	cocos2d::CCLabelBMFont* bombNumber;
	void alterScore(int socre);
	void alterBomb(int bomb);

	//炸弹道具的使用

};

class GameOver:
	public cocos2d::CCScene
{
public:
	GameOver():highScore(0){}
	~GameOver(){}
	CREATE_FUNC(GameOver);
	bool init();

	//一些回调
	void restart_Call_Back(cocos2d::CCObject* sender);
	void quit_Call_Back(cocos2d::CCObject* sender);

	int highScore;
};
#endif