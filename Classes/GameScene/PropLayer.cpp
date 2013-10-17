#include "GameScene/PropLayer.h"
#include "GameScene/GameScene.h"
#include "GlobalData/AudioEngine.h"
#include "GlobalData/GlobalData.h"
USING_NS_CC;
PropLayer::PropLayer()
{

}

PropLayer::~PropLayer()
{
	CC_SAFE_RELEASE(allProps);
}

bool PropLayer::init()
{
	allProps=CCArray::create();
	CC_SAFE_RETAIN(allProps);
	return true;
}
void PropLayer::initThisType(PropType type/* =k_Prop_Bomb */)
{

	CCSize winSize=CCDirector::sharedDirector()->getWinSize();

	CCString* propName=CCString::createWithFormat("prop_type_%d.png",type);
	_prop=CCSprite::createWithSpriteFrameName(propName->getCString());

	_prop->setTag((int)type);
	//计算道具随机产生的横坐标
	int max=winSize.width-_prop->getContentSize().width/2;
	int min=_prop->getContentSize().width/2;
	float randomX=rand()%max;
	if (randomX<min)
	{
		randomX+=min;
	}
	//设定位置
	_prop->setPosition(ccp(randomX,winSize.height));
	this->addChild(_prop);
	allProps->addObject(_prop);

	//道具飞行动画
	CCMoveTo* move1=CCMoveTo::create(0.2f,ccp(randomX,winSize.height*0.7));
	CCMoveTo* move2=CCMoveTo::create(0.4f,ccp(randomX,winSize.height*0.75));
	CCMoveTo* move3=CCMoveTo::create(0.4f,ccp(randomX,0));
	CCCallFuncN* remove=CCCallFuncN::create(this,callfuncN_selector(PropLayer::moveDone));
	
	CCSequence* seq=CCSequence::create(move1,move2,move3,remove,NULL);
	_prop->runAction(seq);
}

void PropLayer::moveDone(CCNode* sender)
{
	AudioEngine::sharedEngine()->playEffect("out_prop.mp3");
	CCSprite* prop=(CCSprite*)sender;
	this->removeChild(prop);
}

CCRect PropLayer::getBoundingBox()
{
	CCRect contentBox = _prop->boundingBox();
	CCPoint point=this->convertToWorldSpace(contentBox.origin);
	CCRect boundingBox=CCRectMake(point.x,point.y,contentBox.size.width,contentBox.size.height);
	return boundingBox;
}