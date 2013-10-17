#ifndef __AirPlane__Enemy__
#define __AirPlane__Enemy__

#include "cocos2d.h"
typedef enum
{
	k_Enemy_Type_Small=0,
	k_Enemy_Type_Middle,
	k_Enemy_Type_Large,
	k_Enemy_Type_Count
}EnemyType;

class Enemy:
	public cocos2d::CCNode
{
public:
	static Enemy* create(EnemyType type=k_Enemy_Type_Small);
	bool init(EnemyType type=k_Enemy_Type_Small);

	CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*,_enemy,EnemySprite);
	CC_SYNTHESIZE_READONLY(int,_type,Type);
	CC_SYNTHESIZE(int,_life,EnemyLife);
	void lostLife(int nIdx);
public:
	//大飞机的飞行动画
	cocos2d::CCFiniteTimeAction*  flyAction();
	//飞机的挨打动画
	void enemyBeHit(Enemy* sender,EnemyType type);
	
	cocos2d::CCRect getBoundingBox();	
};
#endif