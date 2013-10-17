#ifndef __AirPlane__GameScene__
#define __AirPlane__GameScene__

#include "cocos2d.h"
#include "GameScene/PlaneLayer.h"
#include "GameScene/BulletLayer.h"
#include "GameScene/EnemyLayer.h"
#include "GameScene/MenuLayer.h"
#include "GameScene/PanelLayer.h"
#include "GameScene/PropLayer.h"
typedef enum
{
	k_Operate_Pause=0,
	k_Operate_Resume
}OperateFlag;
class GameScene:
	public cocos2d::CCScene
{
public:
	CREATE_FUNC(GameScene);
	CC_SYNTHESIZE(bool,_Double,DPStatus);
	CC_SYNTHESIZE(int,_number,BombNumber);
	GameScene();
	~GameScene();
    virtual bool init();

	//设计碰撞检测的定时器
	void update(float dt);
	void collisionBetweenBulletAndEnemy();
	void collisionBetweenHeroAndEnemy(bool enable);
	void collisionBetweenHeroAndProp();

	//使用炸弹道具
	void useBomb();
	//游戏得分
	void alterScore(EnemyType type);

	//游戏控制
	void pause();
	void operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag);
	void resume();
	void restart();
	void quit();
	void over();
protected:
	//定时调用的函数，实现背景滚动
	void backgroundMove(float dt);
	//定时添加道具
	void addProp(float dt);

	//两个背景
	cocos2d::CCSprite* bg1;
	cocos2d::CCSprite* bg2;
	//英雄飞机
	PlaneLayer* _planeLayer;
	//子弹
	BulletLayer* _bulletLayer;
	//敌机
	EnemyLayer* _enemyLayer;
	//菜单
	MenuLayer* _menuLayer;
	//panel
	PanelLayer* _panelLayer;
	//道具
	PropLayer* _propLayer;

	int score;
	int bulletLastTime;
};

#endif