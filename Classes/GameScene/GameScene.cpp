#include "GameScene/GameScene.h"
#include "GameScene/Enemy.h"
#include "GlobalData/AudioEngine.h"
#include "GlobalData/GlobalData.h"
#include "StartScene/StartScene.h"
USING_NS_CC;
GameScene::GameScene()
{
	bulletLastTime=1200;
	score=0;
	this->setBombNumber(0);
}

GameScene::~GameScene()
{
	CC_SAFE_RELEASE(_menuLayer);
}

bool GameScene::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());
		CCSize winSize=CCDirector::sharedDirector()->getWinSize();

		AudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.mp3");

		//实现背景滚动
		//背景一
		bg1=CCSprite::createWithSpriteFrameName("background.png");
		CC_BREAK_IF(!bg1);
		bg1->setScaleX(winSize.width/480);
		bg1->setScaleY(winSize.height/850);
		bg1->setAnchorPoint(ccp(0,0));
		bg1->setPosition(ccp(0,0));
		this->addChild(bg1);

		//背景二
		bg2=CCSprite::createWithSpriteFrameName("background.png");
		CC_BREAK_IF(!bg2);
		bg2->setScaleX(winSize.width/480);
		bg2->setScaleY(winSize.height/850);
		bg2->setAnchorPoint(ccp(0,0));
		bg2->setPosition(ccp(0,0));
		this->addChild(bg2);

		//加载英雄飞机
		_planeLayer=PlaneLayer::sharedPlaneLayer();
		this->addChild(_planeLayer);

		//加载子弹层
		_bulletLayer=BulletLayer::create();
		_bulletLayer->switchBulletType(k_Bullet_Single);
		this->addChild(_bulletLayer);

		//加载敌机
		_enemyLayer=EnemyLayer::create();
		this->addChild(_enemyLayer);

		//菜单
		_menuLayer=MenuLayer::create();
		_menuLayer->retain();

		//panel
		_panelLayer=PanelLayer::create();
		this->addChild(_panelLayer);

		_propLayer=PropLayer::create();
		this->addChild(_propLayer);

		//调用定时器,实现背景滚动
		this->schedule(schedule_selector(GameScene::backgroundMove),0.01f);
		this->schedule(schedule_selector(GameScene::addProp),30.0f);
		//检测
		this->scheduleUpdate();

		bRet=true;
	} while (0);
	return bRet;
}

void GameScene::backgroundMove(float dt)
{
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	float bg1Next=bg1->getPositionY()-2;
	bg1->setPositionY(bg1Next);

	float bg2Next=bg1->getPositionY()+winSize.height;
	bg2->setPositionY(bg2Next);
	if (bg2->getPositionY()==0)
	{
		bg1->setPositionY(0);
	}
}

void GameScene::addProp(float dt)
{
	int i=rand()%2;
	_propLayer->initThisType((PropType)i);
}

void GameScene::update(float dt)
{
	this->collisionBetweenBulletAndEnemy();
	this->collisionBetweenHeroAndProp();
	this->collisionBetweenHeroAndEnemy(true);
}

void GameScene::collisionBetweenBulletAndEnemy()
{
	CCObject *bobj,*eobj;
	//遍历子弹数组
	CCARRAY_FOREACH(_bulletLayer->allBulltets,bobj)
	{
		CCSprite* bullet=(CCSprite*)bobj;
		CCArray* enemys=_enemyLayer->getEnemys();
		CCARRAY_FOREACH(enemys,eobj)
		{
			Enemy* enemy=(Enemy*)eobj;
			int type=enemy->getType();
			if (enemy->getBoundingBox().intersectsRect(bullet->boundingBox()))
			{
				if(enemy->getEnemyLife()==1)
				{
					this->alterScore((EnemyType)type);
					bullet->setVisible(false);
					_enemyLayer->enemyBlowUp(enemy,(EnemyType)type);
					enemys->removeObject(enemy);
				}
				if (enemy->getEnemyLife()>1)
				{
					_bulletLayer->allBulltets->removeObject(bullet);
					bullet->setVisible(false);
					enemy->enemyBeHit(enemy,(EnemyType)type);
					enemy->lostLife(1);
				}
			}
		}
	}
}

void GameScene::collisionBetweenHeroAndEnemy(bool enable)
{
	if (enable)
	{
		//遍历所有敌机
		CCObject* bobj;
		CCArray* enemys=_enemyLayer->getEnemys();
		CCARRAY_FOREACH(enemys,bobj)
		{
			Enemy* enemy=(Enemy*)bobj;
			if (_planeLayer->getChildByTag(AirPlane)->boundingBox().intersectsRect(enemy->getBoundingBox()))
			{
				//CCLog("collision");
				_planeLayer->isCollision();
				this->over();
			}
		}
	}
}

void GameScene::collisionBetweenHeroAndProp()
{
	CCObject* pobj;
	CCARRAY_FOREACH(_propLayer->allProps,pobj)
	{
		CCSprite* prop=(CCSprite*)pobj;
		if (prop->boundingBox().intersectsRect(_planeLayer->getBoundingBox()))
		{
			CCLog("Get porp");
			if (prop->getTag()==(int)k_Prop_Bullet)
			{
				AudioEngine::sharedEngine()->playEffect("sound/get_double_laser.mp3");
				_bulletLayer->switchBulletType(k_Bullet_Double);
				this->setDPStatus(true);
			}
			if (prop->getTag()==(int)k_Prop_Bomb)
			{
				AudioEngine::sharedEngine()->playEffect("sound/get_bomb.mp3");
				int i=this->getBombNumber();
				i++;
				_panelLayer->getChildByTag(800)->setVisible(true);
				_panelLayer->getChildByTag(801)->setVisible(true);
				_panelLayer->alterBomb(i);
				this->setBombNumber(i);
			}
			_propLayer->allProps->removeObject(prop);
			_propLayer->removeChild(prop);
		}
	}
	if (this->getDPStatus()==true)
	{
		bulletLastTime--;
		if (bulletLastTime==0)
		{
			_bulletLayer->switchBulletType(k_Bullet_Single);
			bulletLastTime=1200;
			this->setDPStatus(false);
		}
	}
}

void GameScene::useBomb()
{
	int i=this->getBombNumber();
	CCLog("bombNumber__%d",i);
	if (i>=1)
	{
		AudioEngine::sharedEngine()->playEffect("sound/use_bomb.mp3");
		CCArray* enemys=_enemyLayer->getEnemys();
		_enemyLayer->allBlowUp(enemys);
		i--;
		this->setBombNumber(i);
		_panelLayer->alterBomb(i);
	}
	if (this->getBombNumber()==0)
	{
		_panelLayer->getChildByTag(800)->setVisible(false);
		_panelLayer->getChildByTag(801)->setVisible(false);
	}
}
void GameScene::pause()
{
	AudioEngine::sharedEngine()->pauseBackgroundMusic();
	this->operateAllSchedulerAndActions(this,k_Operate_Pause);
	this->addChild(_menuLayer);
}

void GameScene::restart()
{
	finalScore=0;
	gameSpeed=0.0f;
	_planeLayer->_sharedPlaneLayer=NULL;
	StartScene* pScene=StartScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionProgressOutIn::create(0.3f,pScene));
}

void GameScene::resume()
{
	AudioEngine::sharedEngine()->resumeBackgroundMusic();
	this->operateAllSchedulerAndActions(this,k_Operate_Resume);
	this->removeChild(_menuLayer,false);
}

void GameScene::over()
{
	this->operateAllSchedulerAndActions(this,k_Operate_Pause);
	AudioEngine::sharedEngine()->pauseBackgroundMusic();
	AudioEngine::sharedEngine()->playEffect("sound/game_over.mp3");
	GameOver* over=GameOver::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInT::create(1.0f,over));
}

void GameScene::quit()
{
	CCDirector::sharedDirector()->end();
}

void GameScene::operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag)
{
	if(node->isRunning()){
		switch (flag) {
		case k_Operate_Pause:
			node->pauseSchedulerAndActions();
			break;
		case k_Operate_Resume:
			node->resumeSchedulerAndActions();
			break;
		default:
			break;
		}
		CCArray* array = node->getChildren();
		if(array != NULL && array->count()>0){
			CCObject* iterator;
			CCARRAY_FOREACH(array, iterator){
				CCNode* child = (CCNode*)iterator;
				if (child!=(CCNode*)_planeLayer)//使得暂停的时候飞机依然能够有飞行动画
				{
					this->operateAllSchedulerAndActions(child, flag);
				}
			}
		}
	}
}

void GameScene::alterScore(EnemyType type)
{
	switch(type)
	{
	case k_Enemy_Type_Small:
		{
			score+=1000;
		}
		break;;
	case k_Enemy_Type_Middle:
		{
			score+=6000;
		}
		break;
	case k_Enemy_Type_Large:
		{
			score+=30000;
		}
		break;
	}
	_panelLayer->alterScore(score);
}