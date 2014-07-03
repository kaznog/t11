//
//  b2Sprite.h
//  t11
//
//  Created by 野口一也 on 2014/07/03.
//
//

#ifndef __t11__b2Sprite__
#define __t11__b2Sprite__

#include "cocos2d.h"

USING_NS_CC;

class b2Sprite : public Sprite
{
public:
    b2Sprite();

    static b2Sprite* create(const std::string& filename);
    CC_SYNTHESIZE(bool, _isLanding, IsLanding);
};

#endif /* defined(__t11__b2Sprite__) */
