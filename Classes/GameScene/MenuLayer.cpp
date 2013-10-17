#include "GameScene/MenuLayer.h"
#include "GameScene/GameScene.h"
USING_NS_CC;

void MenuLayer::onEnter()
{
	CCDirector* pDirector=CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this,-128,true);
	CCLayer::onEnter();
}

void MenuLayer::onExit()
{
	CCDirector* pDirector=CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

bool MenuLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}
bool MenuLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		CCSize winSize=CCDirector::sharedDirector()->getWinSize();

		//创建一个背景
		CCSprite* bg=CCSprite::create("game/bg.png");
		//缩放
		bg->setScaleX(winSize.width/480);
		bg->setScaleY(winSize.height/854);

		bg->setAnchorPoint(ccp(0,0));
		this->addChild(bg);

		CCSprite* resumeNormal=CCSprite::createWithSpriteFrameName("resume_nor.png");
		CCSprite* resumeSelected=CCSprite::createWithSpriteFrameName("resume_sel.png");

		CCSprite* quitNormal=CCSprite::createWithSpriteFrameName("quit_nor.png");
		CCSprite* quitSelected=CCSprite::createWithSpriteFrameName("quit_sel.png");

		CCSprite* restartNoraml=CCSprite::createWithSpriteFrameName("restart_nor.png");
		CCSprite* restartSelected=CCSprite::createWithSpriteFrameName("restart_sel.png");

		//继续游戏
		CCMenuItemImage* resume=CCMenuItemImage::create();
		resume->initWithNormalSprite(resumeNormal,resumeSelected,NULL,this,menu_selector(MenuLayer::resume_Call_Back));
		resume->setPosition(ccp(winSize.width/2,winSize.height*0.7));

		//重新开始
		CCMenuItemImage* restart=CCMenuItemImage::create();
		restart->initWithNormalSprite(restartNoraml,restartSelected,NULL,this,menu_selector(MenuLayer::restart_Call_Back));
		restart->setPosition(ccp(winSize.width/2,winSize.height*0.6));

		//退出游戏
		CCMenuItemImage* quit=CCMenuItemImage::create();
		quit->initWithNormalSprite(quitNormal,quitSelected,NULL,this,menu_selector(MenuLayer::quit_Call_Back));
		quit->setPosition(ccp(winSize.width/2,winSize.height*0.5));

		CCMenu* pMenu=CCMenu::create(resume,restart,quit,NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu);

		bRet=true;
	} while (0);
	return bRet;
}

void MenuLayer::resume_Call_Back(CCObject* sender)
{
	GameScene* pGameScene=(GameScene*)this->getParent();
	pGameScene->resume();
}

void MenuLayer::restart_Call_Back(CCObject* sender)
{
	GameScene* pGameScene=(GameScene*)this->getParent();
	pGameScene->restart();
}

void MenuLayer::quit_Call_Back(CCObject* sender)
{
	GameScene* pGameScene=(GameScene*)this->getParent();
	pGameScene->quit();
}