#ifndef __AirPlane__EnemyLayer__
#define __AirPlane__EnemyLayer__


/*
   1�����ֲ�ͬ���͵ķɻ�Ҫ�в�ͬ������ֵ
   2��������Ϸ���������ӣ����ӷɻ���ʱ����Ҳ��Ҫ�ı�
   3���ɻ��ķ���ʱ��Ҳ������
   4��ÿ�ַɻ��в�ͬ��ˢ�º���
   5��ÿ�ַɻ�Ҳ�в�ͬ���Ƴ�����
   6��ÿ�ַɻ��в�ͬ�ı�ը�ص�����remove
   7���û�ʹ��ը�����߿�������removeall
*/


#include "cocos2d.h"
#include "GameScene/Enemy.h"

class EnemyLayer:
	public cocos2d::CCLayer
{
public:
	CREATE_FUNC(EnemyLayer);
	CC_SYNTHESIZE_READONLY(cocos2d::CCArray*,allEnemys,Enemys);
	EnemyLayer();
	~EnemyLayer();

	bool init();
	//���ӵл��Ķ�ʱ��
	void update(float delta);
	void flyTo(Enemy* sender,float speed);
	void moveDone(cocos2d::CCNode* sender);

	//�ɻ��ı�ը����
	void enemyBlowUp(Enemy* sender,EnemyType type);
	//��ը���Ƴ��ɻ�
	void remove(cocos2d::CCNode* sender,void* data);
	void allBlowUp(cocos2d::CCArray* enemys);

	cocos2d::CCRect getBoundingBox(int type);

	//��Ϸ�ٶȿ���
	float time;
	int addSmall;
	int addMiddle;
	int addLarge;
};
#endif