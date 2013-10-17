#include "GlobalData/GlobalData.h"

USING_NS_CC;
static GlobalData* _sharedGlobalData=NULL;

GlobalData* GlobalData::sharedGlobalDate()
{
	if (_sharedGlobalData=NULL)
	{
		_sharedGlobalData=new GlobalData();
		_sharedGlobalData->init();
	}
	return _sharedGlobalData;
}

bool GlobalData::init()
{
	return true;
}