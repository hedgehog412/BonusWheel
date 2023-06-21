
#ifndef _BONUSWHEEL_SCENE_H_
#define _BONUSWHEEL_SCENE_H_

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include <iostream>

class BonusWheel : public cocos2d::Scene
{

public:
    

    int getPrize();

    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(BonusWheel);
};

#endif // _BONUSWHEEL_SCENE_H_
