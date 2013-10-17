#ifndef __AirPlane__GameScene__
#define __AirPlane__GameScene__

#include "cocos2d.h"
#include "GameScene/PlaneLayer.h"
#include "GameScene/BulletLayer.h"
#include "GameScene/EnemyLayer.h"
#include "GameScene/MenuLayer.h"
#include "GameScene/PanelLayer.h"
#include "GameScene/PropLayer.h"
typedef enum
{
	k_Operate_Pause=0,
	k_Operate_Resume
}OperateFlag;
class GameScene:
	public cocos2d::CCScene
{
public:
	CREATE_FUNC(GameScene);
	CC_SYNTHESIZE(bool,_Double,DPStatus);
	CC_SYNTHESIZE(int,_number,BombNumber);
	GameScene();
	~GameScene();
    virtual bool init();

	//�����ײ���Ķ�ʱ��
	void update(float dt);
	void collisionBetweenBulletAndEnemy();
	void collisionBetweenHeroAndEnemy(bool enable);
	void collisionBetweenHeroAndProp();

	//ʹ��ը������
	void useBomb();
	//��Ϸ�÷�
	void alterScore(EnemyType type);

	//��Ϸ����
	void pause();
	void operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag);
	void resume();
	void restart();
	void quit();
	void over();
protected:
	//��ʱ���õĺ�����ʵ�ֱ�������
	void backgroundMove(float dt);
	//��ʱ��ӵ���
	void addProp(float dt);

	//��������
	cocos2d::CCSprite* bg1;
	cocos2d::CCSprite* bg2;
	//Ӣ�۷ɻ�
	PlaneLayer* _planeLayer;
	//�ӵ�
	BulletLayer* _bulletLayer;
	//�л�
	EnemyLayer* _enemyLayer;
	//�˵�
	MenuLayer* _menuLayer;
	//panel
	PanelLayer* _panelLayer;
	//����
	PropLayer* _propLayer;

	int score;
	int bulletLastTime;
};

#endif