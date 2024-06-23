//
//  gameScene1.cpp
//  SummerOnCloud
//
//  Created by 蓝一潇 on 2017/12/24.
//
//

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class gameScene1:cocos2d::Scene{
public:
     static cocos2d::Scene* createScene();
     virtual void update(float dt);
     virtual bool init();
     int score;
     int life;
     void updatelife();
     void enermy(float dt);
   //  void updatescore(float dt);
     CREATE_FUNC(gameScene1);
};
cocos2d::Scene* gameScene1::createScene()
{
    auto scene = cocos2d::Scene::create();
     auto layer = gameScene1::create();
    scene->addChild(layer);
    return scene;
}
bool gameScene1::init(){
    score = 1;
    life = 6;
    schedule(schedule_selector(gameScene1::enermy),0.5f);
    
  //  schedule(schedule_selector(gameScene1::updatescore),1.0f);
    
    updatelife();
    auto bg = Sprite::create("/Users/eathoublu/Desktop/game/云里的夏天/Mobile5.png");
    bg->setPosition(180,320);
    this->addChild(bg);
    auto player = Sprite::create("/Users/eathoublu/Desktop/game/云里的夏天/Mobile4.png");
    player->setPosition(180,100);
    this->addChild(player);
    player->setTag(1);
    player->runAction(RepeatForever::create( JumpBy ::create(6, ccp(0, 0), 5, 4 )));
    
    
    auto up = Sprite::create("/Users/eathoublu/Desktop/game/Mobile7 4.png");
    up->setPosition(80,120);
    this->addChild(up);
    
    auto left = Sprite::create("/Users/eathoublu/Desktop/game/Mobile7 2.png");
    left->setPosition(50,80);
    this->addChild(left);
    
    auto right = Sprite::create("/Users/eathoublu/Desktop/game/Mobile7 5.png");
    right->setPosition(110,80);
    this->addChild(right);
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan=[up,left,player,right](Touch *t,Event *e){
        if(up->getBoundingBox().containsPoint(t->getLocation())){
         //   player->stopAllActions();
         //   player->runAction(CCMoveBy::create(50,ccp(0,10000)));
          //   player->setTag(1);
            
            
        }
        if(left->getBoundingBox().containsPoint(t->getLocation())){
            player->stopAllActions();
            player->runAction(CCMoveBy::create(50,ccp(-10000,0)));
             player->setTag(1);
        }
        
        if(right->getBoundingBox().containsPoint(t->getLocation())){
            player->stopAllActions();
            player->runAction(CCMoveBy::create(50,ccp(10000,0)));
            player->setTag(1);
        }
        
        
        return true;
    };
    
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,up);
    
    
    
    scheduleUpdate();
    
    
    return true;
}
void gameScene1::update(float dt){
    
    auto player = getChildByTag(1);
    player->setPosition(player->getPosition());
    auto enermy = getChildByTag(2);
    if(enermy){//用if可以判断获取对象是否为空，为空则返回false，该结构体可以起到销毁，回收精灵的作用。
    enermy->setPosition(enermy->getPosition());
    
    if(enermy->getPosition().y<20){
        enermy->removeFromParent();
    }
    if(player->getBoundingBox().containsPoint(enermy->getPosition())){
        player->stopAllActions();
        player->runAction(RepeatForever::create( JumpBy ::create(6, ccp(0, 0), 5, 4 )));
        player->setPosition(180,100);
        enermy->removeFromParent();
        updatelife();
        }
    }
    
    if(player->getPosition().x<=10||player->getPosition().x>=350||player->getPosition().y>=630||player->getPosition().y<=0){
        player->stopAllActions();//如果判别位置反过来会出错，我也不知道为什么
         player->runAction(RepeatForever::create( JumpBy ::create(6, ccp(0, 0), 5, 4 )));
        player->setPosition(180,100);
    }
    
}

void gameScene1::enermy(float dt){//该回调函数可以产生enermy
    auto enermy = Sprite::create("/Users/eathoublu/Desktop/game/云里的夏天/Mobile3.png");
    enermy->setPosition(CCRANDOM_0_1()*300+20,600);
    this->addChild(enermy);
    enermy->setTag(2);
    
    enermy->runAction(CCMoveBy::create(50,ccp(0,-10000)));
    enermy->setTag(2);
    
    this->score++;
    Node * n2 = this->getChildByTag(4);
    if(n2){
        this->removeChildByTag(4);
    }
    if(this->score<0){
        score=0;
    }
    if(score == 0){
        Director::getInstance()->replaceScene(HelloWorld::createScene());
    }
    __String * scoreS = __String::createWithFormat("%d",score);
    auto score1 = LabelTTF::create(scoreS->getCString(), "courier", 30);
    score1->setPosition(100,580);
    this->addChild(score1,100,4);
    

    
    

}

void gameScene1::updatelife(){
    this->life--;
    Node * n = this->getChildByTag(3);
    if(n){
        this->removeChildByTag(3);
    }
    if(this->life<0){
        life=0;
    }
    if(life == 0){
        Director::getInstance()->replaceScene(HelloWorld::createScene());
    }
    __String * lifeS = __String::createWithFormat("%d",life);
    auto life1 = LabelTTF::create(lifeS->getCString(), "courier", 100);
    life1->setPosition(300,80);
    this->addChild(life1,100,3);
    
}

//void gameScene1::updatescore(float dt){
//    this->score++;
//    Node * n = this->getChildByTag(4);
//    if(n){
//        this->removeChildByTag(4);
//    }
//    if(this->score<0){
//        score=0;
//    }
//    if(score == 0){
//        Director::getInstance()->replaceScene(HelloWorld::createScene());
//    }
//    __String * scoreS = __String::createWithFormat("%d",score);
//    auto score1 = LabelTTF::create(scoreS->getCString(), "courier", 30);
//    score1->setPosition(100,600);
//    this->addChild(score1,100,4);
//}
