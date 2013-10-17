#ifndef __AirPlane__EnemyLayer__
#define __AirPlane__EnemyLayer__


/*
   1、三种不同类型的飞机要有不同的生命值
   2、随着游戏分数的增加，增加飞机的时间间隔也需要改变
   3、飞机的飞行时间也会缩短
   4、每种飞机有不同的刷新函数
   5、每种飞机也有不同的移除函数
   6、每种飞机有不同的爆炸回调函数remove
   7、用户使用炸弹道具可以清屏removeall
*/


#include "cocos2d.h"
#include "GameScene/Enemy.h"

class EnemyLayer:
	public cocos2d::CCLayer
{
public:
	CREATE_FUNC(EnemyLayer);
	CC_SYNTHESIZE_READONLY(cocos2d::CCArray*,allEnemys,Enemys);
	EnemyLayer();
	~EnemyLayer();

	bool init();
	//增加敌机的定时器
	void update(float delta);
	void flyTo(Enemy* sender,float speed);
	void moveDone(cocos2d::CCNode* sender);

	//飞机的爆炸动画
	void enemyBlowUp(Enemy* sender,EnemyType type);
	//爆炸后移除飞机
	void remove(cocos2d::CCNode* sender,void* data);
	void allBlowUp(cocos2d::CCArray* enemys);

	cocos2d::CCRect getBoundingBox(int type);

	//游戏速度控制
	float time;
	int addSmall;
	int addMiddle;
	int addLarge;
};
#endif