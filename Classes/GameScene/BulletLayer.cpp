#include "GameScene/BulletLayer.h"
#include "GameScene/GameScene.h"
#include "GameScene/PlaneLayer.h"
#include "GlobalData/AudioEngine.h"
#include "GlobalData/GlobalData.h"
USING_NS_CC;
bool BulletLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		CCTexture2D* texture=CCTextureCache::sharedTextureCache()->textureForKey("game/shoot.png");

		allBulltets=CCArray::create();
		CC_SAFE_RETAIN(allBulltets);

		//有多个子弹，考虑用批处理
		bulletBatchNode=CCSpriteBatchNode::createWithTexture(texture);
		//将批处理加入到层
		this->addChild(bulletBatchNode);

		bRet=true;
	} while (0);
	return bRet;
}

void BulletLayer::switchBulletType(BulletType type)
{
	if (type==k_Bullet_Single)
	{
		this->unschedule(schedule_selector(BulletLayer::addDoubleBullet));
		this->schedule(schedule_selector(BulletLayer::addSingleBullet),0.1f);
	}
	else if (type==k_Bullet_Double)
	{
		this->unschedule(schedule_selector(BulletLayer::addSingleBullet));
		this->schedule(schedule_selector(BulletLayer::addDoubleBullet),0.1f);
	}
}


void BulletLayer::addSingleBullet(float dt)
{
	AudioEngine::sharedEngine()->playEffect("sound/bullet.mp3");
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();

	CCSprite* bullet=CCSprite::createWithSpriteFrameName("bullet1.png");
	bulletBatchNode->addChild(bullet);
	allBulltets->addObject(bullet);
	
	//获取飞机的大小
	CCSize planeSize=PlaneLayer::sharedPlaneLayer()->getChildByTag(AirPlane)->getContentSize();
	//获取子弹大小
	CCSize bulletSize=bullet->getContentSize();
	//获取飞机的位置
	CCPoint planePosition=PlaneLayer::sharedPlaneLayer()->getChildByTag(AirPlane)->getPosition();
	//根据飞机的位置设置子弹的位置
	CCPoint bulletPosition=CCPointMake(planePosition.x,planePosition.y+planeSize.height*0.6);
	bullet->setPosition(bulletPosition);

	//子弹的飞行动画
	CCMoveTo* flyTo=CCMoveTo::create(0.3f,ccp(bulletPosition.x,winSize.height+bulletSize.height));
	CCCallFuncN* finished=CCCallFuncN::create(this,callfuncN_selector(BulletLayer::moveDone));
	CCSequence* seq=CCSequence::create(flyTo,finished,NULL);

	bullet->runAction(seq);

}

void BulletLayer::addDoubleBullet(float dt)
{
	AudioEngine::sharedEngine()->playEffect("sound/button.mp3");
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();

	CCSprite* bulletR=CCSprite::createWithSpriteFrameName("bullet2.png");
	CCSprite* bulletL=CCSprite::createWithSpriteFrameName("bullet2.png");
	bulletBatchNode->addChild(bulletR);
	allBulltets->addObject(bulletR);
	bulletBatchNode->addChild(bulletL);
	allBulltets->addObject(bulletL);

	//获取飞机的大小
	CCSize planeSize=PlaneLayer::sharedPlaneLayer()->getChildByTag(AirPlane)->getContentSize();
	//获取子弹大小
	CCSize bulletSize=bulletR->getContentSize();
	//获取飞机的位置
	CCPoint planePosition=PlaneLayer::sharedPlaneLayer()->getChildByTag(AirPlane)->getPosition();
	//根据飞机的位置设置子弹的位置
	CCPoint bulletPosition=CCPointMake(planePosition.x,planePosition.y+planeSize.height*0.6);
	bulletR->setPosition(ccp(bulletPosition.x-9,bulletPosition.y));
	bulletL->setPosition(ccp(bulletPosition.x+9,bulletPosition.y));

	//子弹的飞行动画
	CCMoveTo* flyTo1=CCMoveTo::create(0.3f,ccp(bulletPosition.x-9,winSize.height+bulletSize.height));
	CCMoveTo* flyTo2=CCMoveTo::create(0.3f,ccp(bulletPosition.x+9,winSize.height+bulletSize.height));

	CCCallFuncN* finished=CCCallFuncN::create(this,callfuncN_selector(BulletLayer::moveDone));
	CCSequence* seq1=CCSequence::create(flyTo1,finished,NULL);
	CCSequence* sep2=CCSequence::create(flyTo2,finished,NULL);

	bulletR->runAction(seq1);
	bulletL->runAction(sep2);
}

void BulletLayer::moveDone(CCNode* sender)
{
	CCSprite* bullet=(CCSprite*)sender;
	allBulltets->removeObject(bullet);
	bulletBatchNode->removeChild(bullet,true);
}

void BulletLayer::removeBullet(CCSprite* bullet)
{
	allBulltets->removeObject(bullet);
	this->removeChild(bullet);
}


BulletLayer::~BulletLayer()
{
	CC_SAFE_RELEASE(allBulltets);
}