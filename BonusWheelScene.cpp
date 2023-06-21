
#include "BonusWheelScene.h"

USING_NS_CC;

enum prizes 
    {
        life30 = 0,
        brush3 = 1,
        gems35 = 2,
        hammer3 = 3,
        coins750 = 4,
        brush1 = 5,
        gems75 = 6,
        hammer1 = 7,
        END
    };

// drop chances divided by 5
int chances[END] = {4, 2, 2, 2, 1, 4, 1, 4};

int BonusWheel::getPrize(){
    // find total sum of drop chances
    int sum = 0;
    for(int i = 0; i < END; i++){
        sum += chances[i];
    }

    // find prize with weighted random
    int randChance = rand() % sum;
    int prize = 0;
    for(int i = 0; i < END; i++){
        if (randChance > chances[i]){
            randChance -= chances[i];
        }
        else {
            return prize;
        }
    }
}

Scene* BonusWheel::createScene()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height/8)); // actual playing size to work with
    
    auto scene = Scene::create();

    auto wheelSections = Sprite::create("wheel_sections_8.png");
    wheelSections->setAnchorPoint(Vec2(0.5, 0.5));
    wheelSections->setPosition(visibleSize.width / 2, visibleSize.height / 2);

    auto secLife30 = Sprite::create("heart.png");

    auto secBrush3 = Sprite::create("brush.png");

    auto secGems35 = Sprite::create("gem.png");

    auto secHammer3 = Sprite::create("hammer.png");

    auto secCoins750 = Sprite::create("coin.png");

    auto secBrush1 = Sprite::create("brush.png");

    auto secGems75 = Sprite::create("gem.png");

    auto secHammer1 = Sprite::create("hammer.png");

    auto wheelBorder = Sprite::create("wheel_border.png");

    auto button = ui::Button::create("spin_button.png", "spin_button.png", "spin_button.png");
    button->setTitleText("Play On");
    button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                    break;
            case ui::Widget::TouchEventType::ENDED:
                    std::cout << "Button 1 clicked" << std::endl;
                    break;
            default:
                    break;
        }
    });

    scene->addChild(wheelSections, 0);
    scene->addChild(wheelSections, 1);

    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in BonusWheelScene.cpp\n");
}

bool BonusWheel::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(BonusWheel::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    

    return true;
}


void BonusWheel::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

}
