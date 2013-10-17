#ifndef __AirPlane__PropLayer__
#define  __AirPlane__PropLayer__

#include "cocos2d.h"
typedef enum
{
	k_Prop_Bullet=0,
	k_Prop_Bomb,
	k_Prop_Count
}PropType;
class PropLayer:
	public cocos2d::CCLayer
{
public:
	PropLayer();
	~PropLayer();
public:
	CREATE_FUNC(PropLayer);
	CC_SYNTHESIZE(cocos2d::CCSprite*,_prop,PropSprite);
	bool init();

	void initThisType(PropType type=k_Prop_Bomb);
	void moveDone(cocos2d::CCNode* sender);
	cocos2d::CCArray* allProps;
	cocos2d::CCRect getBoundingBox();
};
#endif