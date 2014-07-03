#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

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
    if ( !Layer::init() )
    {
        return false;
    }
    _winSize = Director::getInstance()->getWinSize();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    initPhysics();
    scheduleUpdate();
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::initPhysics()
{
    // 重力を作成
    //    b2Vec2 gravity = b2Vec2(0.0f, -9.8f);
    b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
    // Worldを作成
    _world = new b2World(gravity);
    _world->SetAllowSleeping(true);
    _world->SetContinuousPhysics(true);
    CollisionListener* _listener = new CollisionListener();
    _world->SetContactListener(_listener);
    
    {
        _planet = Sprite::create("planet.png");
        _planet->setPosition(Vec2(_winSize.width * 0.8f, _winSize.height/2));
        this->addChild(_planet);
        
        b2BodyDef planetDef;
        planetDef.type = b2_staticBody;
        planetDef.userData = _planet;
        planetDef.position.Set((_winSize.width * 0.8f)/PTM_RATIO, (_winSize.height/2)/PTM_RATIO);
        
        _bodyPlanet = _world->CreateBody(&planetDef);
        b2CircleShape circle;
        circle.m_radius = 50.0 / PTM_RATIO;
        b2FixtureDef planetFixtureDef;
        planetFixtureDef.shape = &circle;
        planetFixtureDef.density = 0.2f;
        planetFixtureDef.friction = 0.2f;
        planetFixtureDef.restitution = 0.2f;
        _bodyPlanet->CreateFixture(&planetFixtureDef);
    }
    {
        _ball = b2Sprite::create("ball.png");
        _ball->setScale(0.2f);
        _ball->setPosition(Vec2(_winSize.width * 0.2f, _winSize.height/2));
        this->addChild(_ball);
        
        b2BodyDef ballDef;
        ballDef.type = b2_dynamicBody;
        ballDef.userData = _ball;
        ballDef.position.Set((_winSize.width * 0.2f)/PTM_RATIO, (_winSize.height/2)/PTM_RATIO);
        
        _bodyBall = _world->CreateBody(&ballDef);
        b2CircleShape ballShape;
        ballShape.m_radius = 10.0 / PTM_RATIO;
        b2FixtureDef ballFixtureDef;
        ballFixtureDef.shape = &ballShape;
        ballFixtureDef.density = 0.2f;
        ballFixtureDef.friction = 0.2f;
        ballFixtureDef.restitution = 0.2f;
        _bodyBall->CreateFixture(&ballFixtureDef);
        _bodyBall->SetSleepingAllowed(true);
        _bodyBall->ApplyForceToCenter(b2Vec2(16.0, 5.0), true);
    }
}

void HelloWorld::update(float dt)
{
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 10;
    int32 positionIterations = 10;
    _world->Step(timeStep, velocityIterations, positionIterations);
    _world->ClearForces();
    
    for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext()) {
        if (b->GetType() == b2_dynamicBody && b->GetUserData() != nullptr) {
            b2Sprite* actor = (b2Sprite*)b->GetUserData();
            actor->setPosition(Point(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
            /**
             * Box2Dでは角度は時計回りに360°法ですが、
             * Cocos2d-xは反時計回りにラジアン法を用いてるので、
             * CC_RADIANS_TO_DEGREESマクロを使って変換してやる必要があります
             */
            actor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
            b2Vec2 center = _bodyPlanet->GetPosition();
            b2Vec2 position = b->GetPosition();
            b2Vec2 d = center - position;
            float length = d.LengthSquared();
            if (length < 19)
            {
                log("length: %f", length);
                d.Normalize();
                b2Vec2 F;
                F = d;
                b->SetOwnGravity(F);
                b->SetUseOwnGravity(true);
                b->ApplyForceToCenter(F, true);
            }
        }
    }
}