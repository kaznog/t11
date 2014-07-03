//
//  CollisionListener.h
//  t11
//
//  Created by 野口一也 on 2014/07/03.
//
//

#ifndef __t11__CollisionListener__
#define __t11__CollisionListener__

#include "Box2D/Box2D.h"

class CollisionListener : public b2ContactListener
{
public:
    CollisionListener();
    virtual void BeginContact(b2Contact* contact);
};

#endif /* defined(__t11__CollisionListener__) */
