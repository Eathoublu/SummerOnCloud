#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "gameScene1.cpp"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}



bool HelloWorld::init()
{
 
    auto bg = Sprite::create("/Users/eathoublu/Desktop/game/云里的夏天/Mobile.png");
    bg->setPosition(180,320);
    this->addChild(bg);
    auto start = Sprite::create("/Users/eathoublu/Desktop/game/云里的夏天/Artboard.png");
    start->setPosition(180,350);
    this->addChild(start);
    auto setting = Sprite::create("/Users/eathoublu/Desktop/game/Artboard.png");
    setting->setPosition(180,250);
    this->addChild(setting);
    auto help = Sprite::create("/Users/eathoublu/Desktop/game/Artboard的副本 2.png");
    help->setPosition(180,160);
    this->addChild(help);
//    ActionInterval* jumpBy = JumpBy ::create(3, ccp(0, 0), 20, 4 );
//    RepeatForever* repeatforeverAction=RepeatForever::create(jumpBy);
//   
    
    help->runAction(RepeatForever::create( JumpBy ::create(5, ccp(0, 0), 10, 4 )));
    start->runAction(RepeatForever::create( JumpBy ::create(2, ccp(0, 0), 15, 4 )));
    setting->runAction(RepeatForever::create( JumpBy ::create(4, ccp(0, 0), 10, 4 )));
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("/Users/eathoublu/Music/酷狗音乐/BQ/三輪学 - -遠い空へ- (ヨスガノソラ メインテーマ).mp3", true);
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan=[start](Touch *t,Event *e){
        if(start->getBoundingBox().containsPoint(t->getLocation())){
            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            Director::getInstance()->replaceScene(gameScene1::createScene());
        }
        
        
        return true;
    };
    
    
    
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,start);
    
    
    
    
    
    
    
    return true;
}



