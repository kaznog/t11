//
//  CollisionListener.cpp
//  t11
//
//  Created by 野口一也 on 2014/07/03.
//
//

#include "CollisionListener.h"
#include "b2Sprite.h"

CollisionListener::CollisionListener()
{
    
}

void CollisionListener::BeginContact(b2Contact* contact)
{
    b2Body * bodyA = contact->GetFixtureA()->GetBody();
    b2Body * bodyB = contact->GetFixtureB()->GetBody();
    if (bodyA->GetType() == b2_dynamicBody) {
        b2Sprite* spriteA = (b2Sprite*) bodyA->GetUserData();
        if (!spriteA->getIsLanding()) {
            spriteA->setIsLanding(true);
            auto func = CallFunc::create([bodyA](){
                bodyA->ResetMassData();
                bodyA->SetLinearVelocity(b2Vec2_zero);
                bodyA->SetAngularVelocity(0);
            });
            spriteA->runAction(Sequence::create(DelayTime::create(5),func, NULL) );
        }
    }
    if (bodyB->GetType() == b2_dynamicBody) {
        b2Sprite* spriteB = (b2Sprite*)bodyB->GetUserData();
        if (!spriteB->getIsLanding()) {
            spriteB->setIsLanding(true);
            auto func = CallFunc::create([bodyB](){
                bodyB->ResetMassData();
                bodyB->SetLinearVelocity(b2Vec2_zero);
                bodyB->SetAngularVelocity(0);
            });
            spriteB->runAction(Sequence::create(DelayTime::create(5),func, NULL) );
        }
    }
}