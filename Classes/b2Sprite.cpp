//
//  b2Sprite.cpp
//  t11
//
//  Created by 野口一也 on 2014/07/03.
//
//

#include "b2Sprite.h"

b2Sprite::b2Sprite()
: _isLanding(false)
{
    
}

b2Sprite* b2Sprite::create(const std::string &filename)
{
    b2Sprite* sprite = new b2Sprite();
    if (sprite && sprite->initWithFile(filename)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}