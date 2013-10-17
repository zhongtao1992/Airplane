#ifndef __AirPlane__PlaneLayer__
#define __AirPlane__PlaneLayer__

//�ɻ��㡣Ҫ��ӷɻ�;
//�ɻ�Ҫ�ƶ������ݴ����ƶ����뷨��ֱ���������Ӵ����¼������ǵ�������Ϸ��Ҫ�����Ķ������ǿ��Ʒɻ��ƶ�����˲���һ�������Ĵ�����;
//������Ҫ���÷ɻ�����ײ���򣬵���ΪӢ�۵ķɻ�����ײ������л�����ײ�����ཻ֮�󣬱䴥����ײ�¼�;
//��ײ�¼�������Ӣ�۷ɻ���ײ�Ķ�����ɾ��Ӣ�۷ɻ�;

static int AirPlane=999;//�����ɻ���tag���Ա����ҵ��ɻ�
#include "cocos2d.h"
class PlaneLayer:
	public cocos2d::CCLayer
{
public:
	static PlaneLayer* sharedPlaneLayer();//���ɵ����¼����������
	static PlaneLayer* _sharedPlaneLayer;
	PlaneLayer():plane(NULL){}
	~PlaneLayer(){}
	bool init();
	//�����¼�����������Ϊ�������ȼ��Ĵ����¼�
	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	//���ɻ��ķ��е��������һ������
	void moveTo(cocos2d::CCPoint pos);
	//��ײ����
	void isCollision();
	cocos2d::CCRect getBoundingBox();
	cocos2d::CCSprite* plane;
	cocos2d::CCPoint m_tTouchesBegin;
};
#endif