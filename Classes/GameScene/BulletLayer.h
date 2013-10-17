#ifndef __AirPlane__BulletLayer__
#define __AirPlane__BulletLayer__

#include "cocos2d.h"

//枚举两种子弹类型
typedef enum
{
	k_Bullet_Single=0,
	k_Bullet_Double
}BulletType;

class BulletLayer:
	public cocos2d::CCLayer
{
public:
	CREATE_FUNC(BulletLayer);
	bool init();
	BulletLayer():bullet(NULL),bulletBatchNode(NULL){}
	~BulletLayer();
public:
	void switchBulletType(BulletType type);

	void addSingleBullet(float dt);
	void addDoubleBullet(float dt);
	void moveDone(cocos2d::CCNode* sender);

	void removeBullet(cocos2d::CCSprite* bullet);
	cocos2d::CCArray* allBulltets;
protected:
	cocos2d::CCSprite* bullet;
	cocos2d::CCSpriteBatchNode* bulletBatchNode;
};
#endif