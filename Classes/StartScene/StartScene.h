#ifndef __AirPlane__StartScene__
#define __AirPlane__StartScene__

//����ͳһ��
//ÿ��Layer����ľ���������Сд��ͷ
//��ӵ�Scene�����Layer������_(�»���)��ͷ

#include "cocos2d.h"
#include "StartScene/StartLayer.h"
class StartScene:
	public cocos2d::CCScene
{
public:
	CREATE_FUNC(StartScene);
public:
	virtual bool init();
private:
	StartLayer* _startLayer;
};
#endif