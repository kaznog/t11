#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "b2Sprite.h"
#include "CollisionListener.h"

USING_NS_CC;

#define PTM_RATIO 32.0

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    virtual void update(float dt);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void addMeteorite(float dt);
    Size _winSize;
    void initPhysics();
    b2World* _world;
    Sprite* _planet;
    b2Body* _bodyPlanet;
    b2Sprite* _ball;
    b2Body* _bodyBall;
};

#endif // __HELLOWORLD_SCENE_H__
