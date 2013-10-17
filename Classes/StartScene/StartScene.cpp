#include "StartScene/StartScene.h"

USING_NS_CC;
bool StartScene::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCScene::init());

		//��ӿ�ʼ��
		_startLayer=StartLayer::create();
		CC_BREAK_IF(!_startLayer);
		this->addChild(_startLayer);

		bRet=true;
	} while (0);
	return bRet;
}