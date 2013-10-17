#include "StartScene/StartLayer.h"
#include "GameScene/GameScene.h"
#include "GameScene/Enemy.h"
#include "GlobalData/AudioEngine.h"
#include "GlobalData/GlobalData.h"
USING_NS_CC;

bool StartLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		CCSize winSize=CCDirector::sharedDirector()->getWinSize();
		//ʹ�þ���֡���棬��Ϊ��ʼ�����ı���ͼ����Ϸ�����ı���ͼ
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bg/bg.plist","bg/bg.png");
		//��ӿ�ʼ����ı���ͼ
		startBG=CCSprite::createWithSpriteFrameName("background.png");
		CC_BREAK_IF(!startBG);
		startBG->setScaleX(winSize.width/480);
		startBG->setScaleY(winSize.height/850);
		startBG->setAnchorPoint(ccp(0,0));
		startBG->setPosition(ccp(0,0));
		this->addChild(startBG);

		//���appName
		appName=CCSprite::createWithSpriteFrameName("name.png");
		CC_BREAK_IF(!appName);
		appName->setScaleX(winSize.width/441);
		appName->setPosition(ccp(winSize.width/2,winSize.height*0.6));
		this->addChild(appName);
		
		//���Ⱦ���
		loadingSprite=CCSprite::createWithSpriteFrameName("game_loading1.png");
		loadingSprite->setPosition(ccp(winSize.width*0.5,winSize.height*0.4));
		this->addChild(loadingSprite);

		CCTextureCache::sharedTextureCache()->addImageAsync("game/shoot.png",this,callfuncO_selector(StartLayer::loading));

		//this->cacheInit();
		bRet=true;
	} while (0);
	return bRet;
}

void StartLayer::loading(CCObject* sender)
{
	CCLog("StartLayer::loading");
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	
	//���鶯��
	CCArray* animatFrams=CCArray::createWithCapacity(4);
	char str[20]={0};
	for (int i=1;i<5;i++)
	{
		sprintf(str,"game_loading%i.png",i);
		//CCLog(str);
		CCSpriteFrame* frame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		animatFrams->addObject(frame);
	}
	CCAnimation* loadingAnimation=CCAnimation::createWithSpriteFrames(animatFrams);
	loadingAnimation->setDelayPerUnit(0.5f);
	CCAnimate* animate=CCAnimate::create(loadingAnimation);

	//һϵ�и��϶���
	CCRepeat* repeatAction=CCRepeat::create(animate,2);
	CCCallFuncN* loadingEnd=CCCallFuncN::create(this,callfuncN_selector(StartLayer::loadingFinished));
	CCSequence* seq=CCSequence::create(repeatAction,loadingEnd,NULL);
	loadingSprite->runAction(seq);	
}
void StartLayer::loadingFinished(CCNode* node)
{
	this->cacheInit();
	this->enterGame();
	AudioEngine::sharedEngine();
	GlobalData::sharedGlobalDate();
}

void StartLayer::cacheInit()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("game/shoot.plist");
	int animationFrame=0;
	//�����ַɻ����������ֲ�ͬ�ı�ը����
	//������еȷɻ��ʹ�ɻ������а��򶯻�
	//��ɻ��з��ж���
	for(int type=k_Enemy_Type_Small;type<k_Enemy_Type_Count;type++)
	{
		CCArray* array=CCArray::createWithCapacity(8);
		if (type==k_Enemy_Type_Small)
		{
			animationFrame=5;
		}
		else if (type==k_Enemy_Type_Middle)
		{
			animationFrame=5;
			
		}
		else if (type==k_Enemy_Type_Large)
		{
			animationFrame=7;
		}
		char str[100]={0};
		for(int i=1;i<animationFrame;i++)
		{
			sprintf(str,"enemy%d_down%d.png",type,i);
			array->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str));
		}
		CCAnimation* enemyBlowUpAnimation=CCAnimation::createWithSpriteFrames(array);
		enemyBlowUpAnimation->setDelayPerUnit(0.1f);
		CCString* animationName=CCString::createWithFormat("enemy%d_blow_up",type);
		CCAnimationCache::sharedAnimationCache()->addAnimation(enemyBlowUpAnimation,animationName->getCString());
	}

}

void StartLayer::enterGame()
{
	//��������Ϸ��Դ�ͽ�����Ϸ
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.3f,GameScene::create()));
}