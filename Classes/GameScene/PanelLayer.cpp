#include "GameScene/PanelLayer.h"
#include "GameScene/GameScene.h"
#include "GlobalData/GlobalData.h"
#include "GlobalData/AudioEngine.h"
USING_NS_CC;


PanelLayer::PanelLayer()
{
	clicked=false;
}
PanelLayer::~PanelLayer()
{

}

bool PanelLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		this->setTouchEnabled(true);

		CCSize winSize=CCDirector::sharedDirector()->getWinSize();

		//暂停开关
		CCSprite* pauseNormal=CCSprite::createWithSpriteFrameName("game_pause_nor.png");

		CCSprite* pauseSelected=CCSprite::createWithSpriteFrameName("game_pause_pressed.png");

		CCSize pauseSize=pauseNormal->getContentSize();
		CCMenuItemImage* pause=CCMenuItemImage::create();
		CC_BREAK_IF(!pause);

		pause->initWithNormalSprite(pauseNormal,pauseSelected,NULL,this,menu_selector(PanelLayer::pause_Call_Back));
		pause->setPosition(ccp(pauseSize.width/2,winSize.height-pauseSize.height/2));

		CCMenu* pMenu=CCMenu::create(pause,NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu);

		//得分显示
		scoreLabel=CCLabelBMFont::create("0","fonts/font.fnt");
		scoreLabel->setScale(0.6f);
		CCSize labelSize=scoreLabel->getContentSize();
		scoreLabel->setColor(ccc3(143,146,147));
		scoreLabel->setAnchorPoint(ccp(0,0));
		scoreLabel->setPosition(ccp(pauseSize.width,winSize.height-labelSize.height*1.1));
		this->addChild(scoreLabel);

		//炸弹道具
		CCSprite* bomb=CCSprite::createWithSpriteFrameName("bomb.png");
		bomb->setTag(800);
		bomb->setPosition(ccp(bomb->getContentSize().width/2,bomb->getContentSize().height/2));
		bomb->setVisible(false);
		this->addChild(bomb);

		//炸弹道具数量的显示
		bombNumber=CCLabelBMFont::create("X1","fonts/font.fnt");
		bombNumber->setColor(ccc3(143,146,147));
		bombNumber->setTag(801);
		bombNumber->setAnchorPoint(ccp(0,0));
		bombNumber->setPosition(ccp(bomb->getContentSize().width,10));
		bombNumber->setVisible(false);
		this->addChild(bombNumber);

		bRet=true;

	} while (0);
	return bRet;
}

void PanelLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	if (clicked)
	{
		clicked=false;
		GameScene* pGameScene=(GameScene*)this->getParent();
		pGameScene->useBomb();
	}
	else
	{
		this->scheduleOnce(schedule_selector(PanelLayer::click),0.25f);
		clicked=true;
	}
}

void PanelLayer::click(float dt)
{
	if (clicked)
	{
		clicked=false;
	}
}

void PanelLayer::pause_Call_Back(CCObject* sender)
{
	GameScene* pGameScene=(GameScene*)this->getParent();
	pGameScene->pause();
}

void PanelLayer::alterScore(int socre)
{
	CCString* strScore=CCString::createWithFormat("%d",socre);
	scoreLabel->setString(strScore->m_sString.c_str());
	finalScore=socre;
	float spe=gameSpeed;
	if (socre>200000*(spe+0.1f))
	{
		spe+=0.03f;
	}
}

void PanelLayer::alterBomb(int bomb)
{
	CCString* strBomb=CCString::createWithFormat("X%d",bomb);
	bombNumber->setString(strBomb->m_sString.c_str());
}


bool GameOver::init()
{
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();

	//背景
	CCSprite* bg=CCSprite::createWithSpriteFrameName("gameover.png");
	bg->setScaleX(winSize.width/480);
	bg->setScaleY(winSize.height/854);
	bg->setPosition(ccp(winSize.width/2,winSize.height/2));
	this->addChild(bg);

	CCSprite* quitNormal=CCSprite::createWithSpriteFrameName("quit_nor.png");
	CCSprite* quitSelected=CCSprite::createWithSpriteFrameName("quit_sel.png");

	CCSprite* restartNoraml=CCSprite::createWithSpriteFrameName("restart_nor.png");
	CCSprite* restartSelected=CCSprite::createWithSpriteFrameName("restart_sel.png");

	CCSize menuSize=quitNormal->getContentSize();
	//重新开始
	CCMenuItemImage* restart=CCMenuItemImage::create();
	restart->initWithNormalSprite(restartNoraml,restartSelected,NULL,this,menu_selector(GameOver::restart_Call_Back));
	restart->setPosition(ccp(winSize.width-menuSize.width/2,winSize.height*0.2));

	//退出游戏
	CCMenuItemImage* quit=CCMenuItemImage::create();
	quit->initWithNormalSprite(quitNormal,quitSelected,NULL,this,menu_selector(GameOver::quit_Call_Back));
	quit->setPosition(ccp(winSize.width-menuSize.width/2,winSize.height*0.1));

	CCMenu* pMenu=CCMenu::create(restart,quit,NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);

	//历史最高
	highScore=CCUserDefault::sharedUserDefault()->getIntegerForKey("HighScore");
	if (highScore>finalScore)
	{
		CCString* strHighScore=CCString::createWithFormat("%d",highScore);
		CCLabelBMFont* high=CCLabelBMFont::create(strHighScore->m_sString.c_str(),"fonts/font.fnt");
		high->setColor(ccc3(143,146,147));
		high->setPosition((ccp(winSize.width/2,winSize.height*0.65)));
		this->addChild(high);
	}
	else if(highScore<finalScore)
	{
		AudioEngine::sharedEngine()->playEffect("sound/achievement.mp3");
		CCUserDefault::sharedUserDefault()->setIntegerForKey("HighScore",finalScore);
		CCString* strHighScore=CCString::createWithFormat("%d",finalScore);
		CCLabelBMFont* high=CCLabelBMFont::create(strHighScore->m_sString.c_str(),"fonts/font.fnt");
		high->setColor(ccc3(143,146,147));
		high->setPosition((ccp(winSize.width/2,winSize.height*0.65)));
		this->addChild(high);
	}


	//最终得分
	CCString* strScore=CCString::createWithFormat("%d",finalScore);
	CCLabelBMFont* scoreLabel=CCLabelBMFont::create(strScore->m_sString.c_str(),"fonts/font.fnt");
	scoreLabel->setString(strScore->m_sString.c_str());

	scoreLabel->setScale(0.6f);
	scoreLabel->setColor(ccc3(143,146,147));
	scoreLabel->setPosition(ccp(winSize.width/2,winSize.height*0.3));
	this->addChild(scoreLabel);

	return true;
}

void GameOver::restart_Call_Back(CCObject* sender)
{
	GameScene* pGameScene=(GameScene*)this->getParent();
	pGameScene->restart();
}

void GameOver::quit_Call_Back(CCObject* sender)
{
	GameScene* pGameScene=(GameScene*)this->getParent();
	pGameScene->quit();
}