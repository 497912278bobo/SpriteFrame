#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    // 精灵创建方式1
    CCTexture2D* texture=CCTextureCache::sharedTextureCache()->addImage("s_hurt.png");// 取图片速度快，多次取图片效率高
    CCSprite* sp=CCSprite::createWithTexture(texture);
    sp->setPosition(ccp(200, 200));
    this->addChild(sp);
    //方式2
//    CCSprite* sp2=CCSprite::create("s_hurt.png");
    
    //this->testSpriteBatchNode();//两层，不会卡
    
    this->testSpriteFrame();
    return true;
}
void HelloWorld::testSpriteBatchNode()
{
    CCSpriteBatchNode* batchNode=CCSpriteBatchNode::create("Icon-57.png", 1000);
    batchNode->setPosition(CCPointZero);
    this->addChild(batchNode);//两层，不会卡
    for (int i=0; i<500; ++i) {
        int x=arc4random()%960;
        int y=arc4random()%640;
        CCSprite* testIcon=CCSprite::createWithTexture(batchNode->getTexture());
        testIcon->setPosition(ccp(x, y));
       batchNode->addChild(testIcon);//两层，不会卡
    }
}
void HelloWorld::testSpriteFrame()
{
    CCSpriteFrameCache* cache=CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("Zombie_default.plist");
    CCSprite* sp=CCSprite::createWithSpriteFrameName("Zombie1.png");
    sp->setPosition(ccp(500,300));
    CCSprite* sp1=CCSprite::createWithSpriteFrameName("Zombie10.png");
    sp1->setPosition(ccp(300,200));
    CCSprite* sp2=CCSprite::createWithSpriteFrameName("Zombie11.png");
    sp2->setPosition(ccp(400,500));
    CCSprite* sp3=CCSprite::createWithSpriteFrameName("Zombie12.png");
    sp3->setPosition(ccp(700,300));


    this->addChild(sp);
    this->addChild(sp1);
    this->addChild(sp2);
    this->addChild(sp3);
    
    //将文件中的数据用字典读出来
    CCDictionary* dic=CCDictionary::createWithContentsOfFile("Zombie_default.plist");
    CCDictionary* framedic=(CCDictionary*)dic->objectForKey("frames");
    int num=framedic->allKeys()->count();
    CCArray* allFrames=CCArray::createWithCapacity(20);
    for (int i=0; i<num; ++i) {
        char frame[50];
        sprintf(frame, "Zombie%d.png",i+1);
        CCSpriteFrame* frameName=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frame);
        allFrames->addObject(frameName);
       
    }
    CCAnimation* animation=CCAnimation::createWithSpriteFrames(allFrames,0.08);
    CCAnimate* animate=CCAnimate::create(animation);
    CCRepeatForever* forever=CCRepeatForever::create(animate);
    sp->runAction(forever);
   }
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
