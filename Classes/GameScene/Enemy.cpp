#include "GameScene/Enemy.h"
#include "GlobalData/AudioEngine.h"
USING_NS_CC;

Enemy* Enemy::create(EnemyType type)
{
	Enemy* enemy=new Enemy();
	enemy->init(type);
	enemy->autorelease();
	return enemy;
}

bool Enemy::init(EnemyType type/* =k_Enemy_Type_Small */)
{
	_type=type;
	_life=pow((double)type,2)*16+1;
	CCString* frameName=CCString::createWithFormat("enemy%d.png",type);
	_enemy=CCSprite::createWithSpriteFrameName(frameName->getCString());
	this->addChild(_enemy);
	return true;
}

void Enemy::lostLife(int nIdx)
{
	this->setEnemyLife(this->getEnemyLife()-nIdx);
}
CCFiniteTimeAction* Enemy::flyAction()
{
	AudioEngine::sharedEngine()->playEffect("sound/big_spaceship_flying.mp3");
	//·ÉÐÐ¶¯»­
	CCAnimation* e2fly=CCAnimation::create();
	e2fly->setDelayPerUnit(0.05f);
	e2fly->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2.png"));
	e2fly->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_n2.png"));

	CCAnimate* animate=CCAnimate::create(e2fly);
	CCFiniteTimeAction* repreatForever=CCRepeatForever::create(animate);
	return repreatForever;
}

void Enemy::enemyBeHit(Enemy* sender,EnemyType type)
{
	CCAnimation* enemyBeHit=CCAnimation::create();
	enemyBeHit->setDelayPerUnit(0.05f);
	CCString* frameName=CCString::createWithFormat("enemy%d_hit.png",type);
	CCString* frameName2=CCString::createWithFormat("enemy%d.png",type);
	enemyBeHit->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString()));
	enemyBeHit->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName2->getCString()));
	
	CCAnimate* animate=CCAnimate::create(enemyBeHit);

	sender->getEnemySprite()->runAction(animate);
}

CCRect Enemy::getBoundingBox()
{
	CCRect contentBox = _enemy->boundingBox();
	CCPoint point=this->convertToWorldSpace(contentBox.origin);
	CCRect boundingBox=CCRectMake(point.x,point.y,contentBox.size.width,contentBox.size.height);
	return boundingBox;
}

