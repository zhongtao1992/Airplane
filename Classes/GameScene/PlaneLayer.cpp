#include "GameScene/PlaneLayer.h"
#include "GlobalData/GlobalData.h"
USING_NS_CC;

PlaneLayer* PlaneLayer:: _sharedPlaneLayer=NULL;
PlaneLayer* PlaneLayer::sharedPlaneLayer()
{
	if (_sharedPlaneLayer==NULL)
	{
		_sharedPlaneLayer=new PlaneLayer();
		_sharedPlaneLayer->init();
	}
	return _sharedPlaneLayer;
}

bool PlaneLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		CCSize winSize=CCDirector::sharedDirector()->getWinSize();
		//首先设置触摸为true
		this->setTouchEnabled(true);

		//创建一个英雄飞机
		plane=CCSprite::createWithSpriteFrameName("hero1.png");
		plane->setScale(0.6f);
		plane->setTag(AirPlane);
		plane->setPosition(ccp(winSize.width/2,winSize.height*0.15));
		this->addChild(plane);

		//创建英雄飞机飞行的动画
		CCAnimation* flyingAnimation=CCAnimation::create();
		flyingAnimation->setDelayPerUnit(0.1f);
		flyingAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
		flyingAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero2.png"));
		CCAnimate* animate=CCAnimate::create(flyingAnimation);
		plane->runAction(CCRepeatForever::create(animate));

		bRet=true;
	} while (0);
	return bRet;
}

//做触摸事件
void PlaneLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator ite=pTouches->begin();
	CCTouch* touch=(CCTouch*)(*ite);
	m_tTouchesBegin=touch->getLocation();
}
void PlaneLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	CCSize heroSize=this->getChildByTag(AirPlane)->getContentSize();

	CCSetIterator ite=pTouches->begin();
	CCTouch* touch=(CCTouch*)(*ite);
	CCPoint m_tTouchesMoved=touch->getLocation();//原来getLocation函数就是直接转换为了GL坐标
	//利用开始触摸点和移动触摸点计算移动的点
	float movedX=m_tTouchesMoved.x-m_tTouchesBegin.x;
	float movedY=m_tTouchesMoved.y-m_tTouchesBegin.y;

	//获取飞机目前的点
    float contentX=this->getChildByTag(AirPlane)->getPositionX();
	float contentY=this->getChildByTag(AirPlane)->getPositionY();

	//计算出要飞向的点
	float moveToX=movedX+contentX;
	float moveToY=movedY+contentY;
	CCPoint pos=CCPointMake(moveToX,moveToY);
	//设定边界
	if (pos.x<=heroSize.width*0.5)
	{
		pos.x=heroSize.width*0.5;
	}
	if(pos.x>=winSize.width-heroSize.width*0.5)
	{
		pos.x=winSize.width-heroSize.width*0.5;
	}
	if (pos.y<heroSize.height*0.47)
	{
		pos.y=heroSize.height*0.47;
	}
	if (pos.y>=winSize.height-heroSize.height*0.47)
	{
		pos.y=winSize.height-heroSize.height*0.47;
	}

	//获取到了触摸点。然后就是飞机的移动了
	this->moveTo(pos);

	//对第一个触摸点进行实时更新
	m_tTouchesBegin=m_tTouchesMoved;
}

void PlaneLayer::moveTo(CCPoint pos)
{
	this->getChildByTag(AirPlane)->setPosition(pos);
}

void PlaneLayer::isCollision()
{
	//创建爆炸动画
	CCAnimation* blowUp=CCAnimation::create();
	blowUp->setDelayPerUnit(0.5f);
	blowUp->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n1.png"));
	blowUp->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n2.png"));
	blowUp->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n3.png"));
	blowUp->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n4.png"));

	CCAnimate* animate=CCAnimate::create(blowUp);

	this->getChildByTag(AirPlane)->runAction(animate);
}

CCRect PlaneLayer::getBoundingBox()
{
	CCRect box=plane->boundingBox();
	CCSize size=plane->getContentSize();
	CCRect boundingBox=CCRectMake(box.origin.x,box.origin.y,size.width*0.6,size.height*0.5);
	return boundingBox;
}