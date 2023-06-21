
#include "BonusWheelScene.h"

USING_NS_CC;

// enum for prizes
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

// sprite image
std::string images[END] = {"heart.png", "brush.png", "gem.png", "hammer.png", "coin.png", "brush.png", "gem.png", "hammer.png"};

// drop chances
int chances[END] = {20, 10, 10, 10, 5, 20, 5, 20};

// text for each prize
std::string text[END] = {"30 mins","x3", "x35", "x3", "x750", "x1", "x75", "x1"};

// maximum number of spins
int maxSpins = 4;

// radius of prize circle relative to wheel
float in_r = 0.6;

int BonusWheel::getPrize(){
    // find total sum of drop chances
    int sum = 0;
    for(int i = 0; i < END; i++){
        sum += chances[i];
    }

    // find prize with weighted random
    std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_int_distribution<int> distribution(1,sum);
    int randChance = distribution(generator);
    log("rand chance %d", randChance);
    for(int i = 0; i < END; i++){
        if (randChance <= chances[i]){
            log("prize is %d", i);
            return i;
        }
        randChance -= chances[i];
    }
}

float BonusWheel::getRad(float deg){
    float pi = 3.14159265359;
    return (deg * (pi / 180));
}

float BonusWheel::getRot(int prize){
    return 360 / END * prize + 180 / END;
}

void BonusWheel::setPrizePos(int prize, float r, Sprite* sprite, Vec2 origin){
    float rot = getRot(prize);
    sprite->setRotation(rot);
    sprite->setPosition(in_r * r * sin(getRad(rot)) + r, in_r * r * cos(getRad(rot)) + r);
}

void BonusWheel::initWheel(Scene* scene){
    scene->removeChildByName("wheel");
    scene->removeChildByName("arrow");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height/8)); // actual playing size to work with
    Size buttonSize = scene->getChildByName("button")->getContentSize();
    
    // create wheel background as parent
    auto wheelSections = Sprite::create("wheel_sections_8.png");
    wheelSections->setAnchorPoint(Vec2(0.5, 0.5));
    wheelSections->setPosition(playingSize.width / 2 + origin.x, playingSize.height / 2 + origin.y + buttonSize.height / 2);
    wheelSections->setName("wheel");
    scene->addChild(wheelSections, 0);
    Size wheelSize = wheelSections->getContentSize();
    float r = wheelSize.width / 2;
    
    // creates sprites for all prizes
    for(int i = 0; i < END; i++){
        auto sprite = Sprite::create(images[i]);
        sprite->setAnchorPoint(Vec2(0.5, 0.5));
        Size spriteSize = sprite->getContentSize();
        
        auto label = Label::createWithSystemFont(text[i], "Arial", 75);
        label->setAnchorPoint(Vec2(0.5, 0));
        label->setPosition(Vec2(spriteSize.width / 2, 0));
        label->enableOutline(Color4B::BLACK, 1);
        
        sprite->addChild(label);
        wheelSections->addChild(sprite, i);
        
        setPrizePos(i, r, sprite, origin);
    }

    auto wheelBorder = Sprite::create("wheel_border.png");
    wheelBorder->setAnchorPoint(Vec2(0.5, 0.5));
    wheelSections->addChild(wheelBorder, 8);
    wheelBorder->setPosition(r, r);
    
    auto arrow = Sprite::create("wheel_arrow.png");
    arrow->setAnchorPoint(Vec2(0.5, 0.5));
    arrow->setPosition(origin.x + playingSize.width / 2, origin.y + playingSize.height / 2 + r);
    arrow->setName("arrow");
    
    arrow->setScale(0.75);
    wheelSections->setScale(0.75);


    scene->addChild(arrow, 1);
}

int BonusWheel::spinWheel(Node* wheel){
    int prize = getPrize();
    log("prize is %d", prize);
    
    float toSpin = (END - prize - 1) % END;

    // spin wheel and stop at prize
    int numSpins = rand() % maxSpins + 1;
    auto spin_ease = EaseCubicActionOut::create(RotateBy::create(maxSpins * 0.75, 360 * numSpins + getRot(toSpin)));
    wheel->runAction(Sequence::create(spin_ease, DelayTime::create(2), NULL));
    return prize;
}

Scene* BonusWheel::createScene()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height/8)); // actual playing size to work with

    auto scene = Scene::create();
    
    auto button = ui::Button::create("spin_button.png", "spin_button.png", "spin_button.png");
    button->setTitleText("Play On");
    button->setTitleFontSize(100);
    button->setScale(0.4);
    Size buttonSize = button->getContentSize();
    button->setPosition(Vec2(origin.x + playingSize.width / 2, origin.y + buttonSize.height / 2));
    scene->addChild(button, 2);
    button->setName("button");

    button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:{
                    break;
                    }
            case ui::Widget::TouchEventType::ENDED:{
                    std::cout << "Button 1 clicked"<<sender<<" "<<button << &button<< std::endl;
                    auto scene = ((ui::Button *)sender)->getParent();
                    spinWheel(scene->getChildByName("wheel"));
                    ((ui::Button *) sender)->removeFromParent();
                    break;
                    }
            default:
                    break;
        }
    });

    initWheel(scene);
    
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
    Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height/8));

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

void BonusWheel::testSpin(Scene* scene){
    int results[8] = {};
    int numTests = 1000;
    
    for (int i = 0; i < numTests; i++){
        initWheel(scene);
        results[spinWheel(scene->getChildByName("wheel"))]++;
    }
    
    std::cout
    <<"\nNumber of tests: " << numTests << "\n"
    << "Life 30: " << results[life30] << "\n"
    << "Brush 3: " << results[brush3] << "\n"
    << "Gems 35: " << results[gems35] << "\n"
    << "Hammer 3: " << results[hammer3] << "\n"
    << "Coins 750: " << results[coins750] << "\n"
    << "Brush 1: " << results[brush1] << "\n"
    << "Gems 75: " << results[gems75] << "\n"
    << "Hammer 1: " << results[hammer1] << "\n"
    << std::endl;
    
    log("tested");
    
    initWheel(scene);
    
}


void BonusWheel::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

}
