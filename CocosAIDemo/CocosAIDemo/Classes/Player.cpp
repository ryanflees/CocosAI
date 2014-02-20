//
//  Player.cpp
//  ComicWars
//
//  Created by Bai Ryan on 13-10-10.
//
//

#include "Player.h"
#include "SimpleAudioEngine.h"
#include "func.h"

#define kPlayerDefaultBulletCount 30
#define kPlayerDefaultReloadTime 0.6f

USING_NS_CC;
using namespace CocosDenshion;

Player *Player::createWithSpriteFrameName(const char *frameName)
{
    Player *pRet = new Player();
    if (pRet && pRet->initWithSpriteFrameName(frameName))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

Player::~Player()
{
 //   CC_SAFE_RELEASE(m_recoidAction);
    CC_SAFE_RELEASE(m_flameAnimation);
    unscheduleUpdate();
}

Player *Player::m_instanceOfPlayer = NULL;

bool Player::initWithSpriteFrameName(const char *frameName)
{
    if (!CCSprite::initWithSpriteFrameName(frameName)) {
        return false;
    }
    m_instanceOfPlayer = this;
    m_velocity = ccp(0, 0);
    m_isAlive = true;
    scheduleUpdate();
    return true;
}

bool Player::init()
{
    if (!CCSprite::initWithSpriteFrameName("ryancat.png")) {
        return false;
    }
    
    loadingMagazine = false;
    
    m_fireTimeLimit = 0;
    
    bulletCount = kPlayerDefaultBulletCount;
    m_health = kPlayerDefaultHealth;
    m_arm = CCSprite::createWithSpriteFrameName("ryancat_arm.png");
    addChild(m_arm);
    m_arm->setAnchorPoint(ccp(0, 0.5));
    m_arm->setPosition(ccp(120, 180));
    
    m_fireFlame = CCSprite::createWithSpriteFrameName("muzzleflash_0010.png");
    addChild(m_fireFlame);
    m_fireFlame->setScale(6.0f);
    m_fireFlame->setVisible(false);
    
    m_flameAnimation = CCAnimation::create();
    for(int i=0;i<=9;i++)
    {
        CCString *frameName = CCString::createWithFormat("muzzleflash_001%i.png",i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
        m_flameAnimation->addSpriteFrame(frame);
    }
    m_flameAnimation->setDelayPerUnit(0.02);
    m_flameAnimation->setLoops(1);
    m_flameAnimation->retain();
    
    CCMoveBy *moveBy = CCMoveBy::create(0.04, ccp(-15, 0));
    CCMoveBy *moveByBack = CCMoveBy::create(0.04, ccp(15, 0));
    m_recoidAction = CCSequence::create(moveBy, moveByBack, NULL);
    
    m_instanceOfPlayer = this;
    
    m_velocity = ccp(0, 0);
    m_isAlive = true;
    scheduleUpdate();
    return true;
}

void Player::update(float dt)
{
    CCSprite::update(dt);
    
    if (m_fireTimeLimit > 0) {
        m_fireTimeLimit -= dt;
    }
}

void Player::fireBullteAt(cocos2d::CCPoint targetPos)
{
	//Fire 10 bullets per second
	if(m_fireTimeLimit > 0){
		return;
	}
    
	m_fireTimeLimit = kFireTimeLimit;

    CCPoint fromPos = getPosition()+ ccp(-20,0);
    float angle = atan2f(targetPos.y-fromPos.y, targetPos.x-fromPos.x);
    angle = radiansToDegrees(angle);
    m_arm->setRotation(-angle);
    
    angle = degreesToRadians(angle);
    int r = 70;
    CCPoint offset = ccp(r*cos(angle), r*sin(angle));
    fromPos = fromPos + offset;
    if (m_delegate != NULL) {
        m_delegate->fireFromPointTo(this, fromPos, targetPos);
    }
    
    CCPoint pointInNode = convertToNodeSpace(fromPos);
    m_fireFlame->setPosition(pointInNode);
    m_fireFlame->setVisible(true);
    m_fireFlame->stopAllActions();
    CCAnimate *animate = CCAnimate::create(m_flameAnimation);
    CCFiniteTimeAction *seq = CCSequence::create(animate,
    CCCallFunc::create(this, callfunc_selector(Player::onPlayFlameFinished)),NULL);
    m_fireFlame->runAction(seq);
}

void Player::onPlayFlameFinished()
{
    m_fireFlame->setVisible(false);
}

void Player::reloadMagazine()
{
    loadingMagazine = true;
    SimpleAudioEngine::sharedEngine()->playEffect("reload.caf");
    CCFiniteTimeAction *seq = CCSequence::create(CCDelayTime::create(kPlayerDefaultReloadTime),
        CCCallFunc::create(this, callfunc_selector(Player::reloadFinished)),NULL);
    runAction(seq);
    m_fireTimeLimit = kPlayerDefaultReloadTime*1.2f;
}

void Player::reloadFinished()
{
    bulletCount = kPlayerDefaultBulletCount;
}

cocos2d::CCRect Player::getPlayerRect()
{
    float x = getPositionX() - getContentSize().width*getScaleX()*0.5f;
    float y = getPositionY() - getContentSize().height*getScaleY()*0.5f;
    CCRect rect = CCRectMake(x, y, getContentSize().width*getScaleX()
                             , getContentSize().height*getScaleY());
    return rect;
}

void Player::loseHealth(float damage)
{
    m_health -= damage;
    if (m_health < 0) {
        m_health = 0;
        die();
    }
}

void Player::die()
{
    if (m_delegate) {
        m_delegate->onPlayerDead(this);
    }
}








