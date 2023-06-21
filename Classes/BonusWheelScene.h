
#ifndef _BONUSWHEEL_SCENE_H_
#define _BONUSWHEEL_SCENE_H_

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <functional>
#include <stdlib.h>
#include <random>
#include <time.h>

class BonusWheel : public cocos2d::Scene
{

public:
    
    /**
        @brief generates weighted random prize
        @return generated prize enum value
     */
    static int getPrize();

    /**
        @brief converts degree to radians
        @param float angle in degrees
        @return angle in radians
     */
    static float getRad(float deg);
    
    /**
        @brief returns initial rotation of prize
        @param int prize enum value
        @return angle in degrees
     */
    static float getRot(int prize);

    /**
        @brief sets prize sprite position and rotation
        @param int prize enum value
        @param float r, radius of wheel
        @param prize sprite
        @param origin of wheel
     */
    static void setPrizePos(int prize, float r, cocos2d::Sprite* sprite, cocos2d::Vec2 origin);

    /**
        @brief spins wheel
        @param wheel node
        @return result of spin with prize enum value
     */
    static int spinWheel(cocos2d::Node* wheel);
    
    /**
        @brief initializes wheel in scene (if already existing wheel, replaces)
        @param parent scene
     */
    static void initWheel(cocos2d::Scene* scene);
    
    /**
        @brief creates bonus wheel scene
        @return bonus wheel scene
     */
    static cocos2d::Scene* createScene();
    
    /**
        @brief tests drop chance of wheel
        @param parent scene
     */
    static void testSpin(cocos2d::Scene* scene);

    /**
        @brief initializes BonusWheel
        @return true Initialize success
        @return false Initialize fail
     */
    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);

    
    CREATE_FUNC(BonusWheel);
};

#endif // _BONUSWHEEL_SCENE_H_
