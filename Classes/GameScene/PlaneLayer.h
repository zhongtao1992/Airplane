#ifndef __AirPlane__PlaneLayer__
#define __AirPlane__PlaneLayer__

//飞机层。要添加飞机;
//飞机要移动，根据触摸移动。想法是直接在这个层加触摸事件，考虑到整个游戏需要触摸的东西就是控制飞机移动，因此不做一个单独的触摸层;
//另外需要设置飞机的碰撞区域，当作为英雄的飞机的碰撞区域与敌机的碰撞区域相交之后，变触发碰撞事件;
//碰撞事件包含，英雄飞机被撞的动画，删除英雄飞机;

static int AirPlane=999;//用作飞机的tag，以便能找到飞机
#include "cocos2d.h"
class PlaneLayer:
	public cocos2d::CCLayer
{
public:
	static PlaneLayer* sharedPlaneLayer();//做成单例事件，方便访问
	static PlaneLayer* _sharedPlaneLayer;
	PlaneLayer():plane(NULL){}
	~PlaneLayer(){}
	bool init();
	//触摸事件，考虑设置为不带优先级的触摸事件
	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	//将飞机的飞行单独抽象出一个函数
	void moveTo(cocos2d::CCPoint pos);
	//碰撞动画
	void isCollision();
	cocos2d::CCRect getBoundingBox();
	cocos2d::CCSprite* plane;
	cocos2d::CCPoint m_tTouchesBegin;
};
#endif