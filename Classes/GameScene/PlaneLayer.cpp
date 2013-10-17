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
		//�������ô���Ϊtrue
		this->setTouchEnabled(true);

		//����һ��Ӣ�۷ɻ�
		plane=CCSprite::createWithSpriteFrameName("hero1.png");
		plane->setScale(0.6f);
		plane->setTag(AirPlane);
		plane->setPosition(ccp(winSize.width/2,winSize.height*0.15));
		this->addChild(plane);

		//����Ӣ�۷ɻ����еĶ���
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

//�������¼�
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
	CCPoint m_tTouchesMoved=touch->getLocation();//ԭ��getLocation��������ֱ��ת��Ϊ��GL����
	//���ÿ�ʼ��������ƶ�����������ƶ��ĵ�
	float movedX=m_tTouchesMoved.x-m_tTouchesBegin.x;
	float movedY=m_tTouchesMoved.y-m_tTouchesBegin.y;

	//��ȡ�ɻ�Ŀǰ�ĵ�
    float contentX=this->getChildByTag(AirPlane)->getPositionX();
	float contentY=this->getChildByTag(AirPlane)->getPositionY();

	//�����Ҫ����ĵ�
	float moveToX=movedX+contentX;
	float moveToY=movedY+contentY;
	CCPoint pos=CCPointMake(moveToX,moveToY);
	//�趨�߽�
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

	//��ȡ���˴����㡣Ȼ����Ƿɻ����ƶ���
	this->moveTo(pos);

	//�Ե�һ�����������ʵʱ����
	m_tTouchesBegin=m_tTouchesMoved;
}

void PlaneLayer::moveTo(CCPoint pos)
{
	this->getChildByTag(AirPlane)->setPosition(pos);
}

void PlaneLayer::isCollision()
{
	//������ը����
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