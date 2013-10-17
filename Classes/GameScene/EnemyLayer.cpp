#include "GameScene/EnemyLayer.h"
#include "GameScene/GameScene.h"
#include "GlobalData/AudioEngine.h"
#include "GlobalData/GlobalData.h"
USING_NS_CC;
EnemyLayer::EnemyLayer():time(0.0),addSmall(0),addMiddle(0),addLarge(0)
{
	
}

EnemyLayer::~EnemyLayer()
{
	CC_SAFE_RELEASE(allEnemys);
}
bool EnemyLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		//管理飞机的数组
		allEnemys=CCArray::create();
		CC_SAFE_RETAIN(allEnemys);

		//定时器
		this->scheduleUpdate();
		bRet=true;
	} while (0);
	return bRet;
}

void EnemyLayer::update(float delta)
{
	addSmall++;
	addMiddle++;
	addLarge++;
	float speed=gameSpeed;
	if (addSmall>50-gameSpeed)
	{
		Enemy* enemySmall=Enemy::create(k_Enemy_Type_Small);
		enemySmall->setTag(k_Enemy_Type_Small);
		this->flyTo(enemySmall,3.0f-speed);
		addSmall=0;
	}
	if (addMiddle>300-gameSpeed)
	{
		Enemy* enemyMiddle=Enemy::create(k_Enemy_Type_Middle);
		enemyMiddle->setTag(k_Enemy_Type_Middle);
		this->flyTo(enemyMiddle,5.0f-speed);
		addMiddle=0;
	}
	if (addLarge>800-gameSpeed)
	{
		Enemy* enemyLarge=Enemy::create(k_Enemy_Type_Large);
		enemyLarge->setTag(k_Enemy_Type_Large);
		enemyLarge->getEnemySprite()->runAction(enemyLarge->flyAction());
		this->flyTo(enemyLarge,6.0f-speed);
		addLarge=0;
	}
}

void EnemyLayer::flyTo(Enemy* sender,float speed)
{
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	//计算飞机随机产生的横坐标
	int max=winSize.width-sender->getEnemySprite()->getContentSize().width/2;
	int min=sender->getEnemySprite()->getContentSize().width/2;
	float randomX=rand()%max;
	if (randomX<min)
	{
		randomX+=min;
	}

	//设定位置
	sender->setPosition(ccp(randomX,winSize.height));
	this->addChild(sender);
	allEnemys->addObject(sender);

	//飞行目的地
	CCPoint pos=CCPointMake(randomX,-sender->getEnemySprite()->getContentSize().height/2);
	//飞机飞向目的地
	CCMoveTo* flyTo=CCMoveTo::create(speed,pos);
	flyTo->setTag(9);
	CCCallFuncN* moveDone=CCCallFuncN::create(this,callfuncN_selector(EnemyLayer::moveDone));
	CCSequence* seq=CCSequence::create(flyTo,moveDone,NULL);
	sender->runAction(seq);
}

void EnemyLayer::moveDone(CCNode* sender)
{
	Enemy* enemy=(Enemy*)sender;
	allEnemys->removeObject(enemy);
	this->removeChild(enemy);
}

void EnemyLayer::enemyBlowUp(Enemy* sender,EnemyType type)
{
	sender->stopAllActions();
	CCString* animationName=CCString::createWithFormat("enemy%d_blow_up",type);
	CCString* effectName=CCString::createWithFormat("sound/enemy%d_down.mp3",type);

	AudioEngine::sharedEngine()->preloadEffect(effectName->getCString());

	CCAnimation* blowUpAnimation=CCAnimationCache::sharedAnimationCache()->animationByName(animationName->getCString());
	CCAnimate* animate=CCAnimate::create(blowUpAnimation);
	CCCallFuncND* remove=CCCallFuncND::create(this,callfuncND_selector(EnemyLayer::remove),(void*)sender);
	CCSequence* seq=CCSequence::create(animate,remove,NULL);

	sender->getEnemySprite()->runAction(seq);
}

void EnemyLayer::remove(CCNode* sender,void* data)
{
	Enemy* enemy=(Enemy*)data;
	allEnemys->removeObject(enemy);
	this->removeChild(enemy);
}

void EnemyLayer::allBlowUp(CCArray* enemys)
{
	GameScene* pGameScene=(GameScene*)this->getParent();
	CCObject* obj;
	CCARRAY_FOREACH(enemys,obj)
	{
		Enemy* enemy=(Enemy*)obj;
		if (enemy->getEnemyLife()>0&&enemy->isRunning())
		{
			int type=enemy->getType();
			this->enemyBlowUp(enemy,(EnemyType)type);
			pGameScene->alterScore((EnemyType)type);
			enemys->removeAllObjects();
		}	
	}
}

CCRect EnemyLayer::getBoundingBox(int type)
{
	CCRect box=this->getChildByTag((EnemyType)type)->boundingBox();
	//CCPoint pos=this->getChildByTag((EnemyType)type)->getPosition();
	CCPoint origin=this->convertToWorldSpace(box.origin);
	//CCLog("%f  %f",origin.x,origin.y);
	CCSize size=this->getChildByTag((EnemyType)type)->getContentSize();
	CCRect boundingBox=CCRectMake(origin.x,origin.y,box.size.width,box.size.height);
	return boundingBox;
}