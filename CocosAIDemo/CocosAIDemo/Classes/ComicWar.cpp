//
//  ComicWar.cpp
//  CocosAIDemo
//
//  Created by Bai Ryan on 14-2-12.
//
//

#include "ComicWar.h"
#include "Enemy.h"
#include "Bullet.h"
#include "func.h"

#define kPlayerBulletSpeed 1000

ComicWar::ComicWar():m_touchedForFiring()
{

}

ComicWar::~ComicWar()
{

}

bool ComicWar::init()
{
    if (!CCNode::init())
    {
        return false;
    }
    loadResource();
    addBackground();
    addBullets();
    addPlayer();
    addEnemy();
    return true;
}

void ComicWar::onEnter()
{
    CCNode::onEnter();
    scheduleUpdate();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0, false);
}

void ComicWar::onExit()
{
    CCNode::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void ComicWar::loadResource()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("comicwar/enemy_tp.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("comicwar/ryancat_gun.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("comicwar/muzzleflash.plist");
}

void ComicWar::addBackground()
{
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCLayerColor* layer = CCLayerColor::create(ccc4(255, 255, 255, 255), screenSize.width, screenSize.height);
    addChild(layer);
}

void ComicWar::addEnemy()
{
    m_enemyTroops = EnemyCache::createWithCount(200);
    addChild(m_enemyTroops);
    for (int i=0; i<m_enemyTroops->getUnitCount(); i++) {
        Enemy *unit = (Enemy*)m_enemyTroops->getUnitByIndex(i);
        float x = (int)(arc4random()%960);
        float y = (int)(arc4random()%640);
    //    unit->setVisible(true);
    //    unit->setPosition(ccp(x,y));
    
        unit->setVisible(false);
        unit->setScale(0.2f);
        unit->setPosition(ccp(2000,y));
        addBehaviorTreeForEnemy(unit);
        unit->setDelegate(this);
    }
}

void ComicWar::addBehaviorTreeForEnemy(Enemy* enemy)
{
    BTParallel* parallel = enemy->getBehavior();
    
    BTSequence* seqCharge = BTSequence::create();
    parallel->addBTNode(seqCharge);
    
    //charge
    BTCondition* canCharge = BTCondition::create();
    canCharge->setTag(kEnemyCondCanCharge);
    canCharge->setDelegate(enemy);
    seqCharge->addBTNode(canCharge);
    
    BTAction *chargeAction = BTAction::create();
    chargeAction->setDelegate(enemy);
    chargeAction->setTag(kEnemyActionCharge);
    seqCharge->addBTNode(chargeAction);
    
    //take cover
    BTSequence *seqTakeCover = BTSequence::create();
    parallel->addBTNode(seqTakeCover);
    
    BTCondition *dectDanger = BTCondition::create();
    dectDanger->setTag(kEnemyCondDetectDanger);
    dectDanger->setDelegate(enemy);
    seqTakeCover->addBTNode(dectDanger);
    
    BTAction *proneAction = BTAction::create();
    proneAction->setDelegate(enemy);
    proneAction->setTag(kEnemyActionProne);
    seqTakeCover->addBTNode(proneAction);
    
    //stand up
    BTSequence *seqStandUp = BTSequence::create();
    parallel->addBTNode(seqStandUp);
    
    BTCondition *canStandup = BTCondition::create();
    canStandup->setTag(kEnemyCondCanStandup);
    canStandup->setDelegate(enemy);
    seqStandUp->addBTNode(canStandup);
    
    BTAction *standAction = BTAction::create();
    standAction->setDelegate(enemy);
    standAction->setTag(kEnemyActionStand);
    seqStandUp->addBTNode(standAction);
    
    //fire at player
    BTSequence *seqFireAtPlayer = BTSequence::create();
    parallel->addBTNode(seqFireAtPlayer);
    BTCondition* checkPlayerInsight = BTCondition::create();
    checkPlayerInsight->setDelegate(enemy);
    checkPlayerInsight->setTag(kEnemyCondPlayerInsight);
    seqFireAtPlayer->addBTNode(checkPlayerInsight);
    
    BTAction *shootAction = BTAction::create();
    shootAction->setDelegate(enemy);
    shootAction->setTag(kEnemyActionShoot);
    seqFireAtPlayer->addBTNode(shootAction);
    
}

void ComicWar::addBullets()
{
    m_bullets = BulletCache::create();
    addChild(m_bullets);
}

void ComicWar::addPlayer()
{
    m_player = Player::create();
    m_player->setScale(0.2f);
    m_player->setDelegate(this);
    addChild(m_player);
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    m_player->setPosition(ccp(30, screenSize.height/2));
}

void ComicWar::update(float dt)
{
    CCNode::update(dt);
    
    time_t t;
    srand((unsigned) time(&t));
    unsigned int randValue = rand()%20;
	//
    randValue = arc4random()%20;
    if (randValue == 0) {
        Enemy *enemy = dynamic_cast<Enemy*>(m_enemyTroops->getNexInactiveUnit());
        if (enemy) {
            CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
            float x = screenSize.width + 20;
            float y = (arc4random()%((int)screenSize.height));
#define kDefaultEnemyHealth 100.0f
            enemy->spawnAtPosition(ccp(x,y));
            enemy->setZOrder(screenSize.height - enemy->getPositionY());
        }
    }
    
    CCArray *enemies = m_enemyTroops->getActiveEnemy();
    CCObject *object = NULL;
    CCARRAY_FOREACH(enemies, object)
    {
        Enemy *enemy = dynamic_cast<Enemy*>(object);
        if (enemy->getIsAlive() == false) {
            continue;
        }
        enemy->behave();
        
        CCPoint position = enemy->getPosition();
        CCPoint velocity = enemy->getVelocity();
        CCPoint newPos = ccp(position.x+dt*velocity.x,position.y + dt*velocity.y);
        enemy->setPosition(newPos);
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        if (enemy->getZOrder() != screenSize.height - enemy->getPositionY()) {
            CCSpriteBatchNode *batch = dynamic_cast<CCSpriteBatchNode*>(enemy->getParent());
            batch->reorderChild(enemy, screenSize.height - enemy->getPositionY());
        }
        if(newPos.x < -40)
        {
            enemy->setIsActive(false);
        }
    }
    
    if (m_touchedForFiring) {
        m_player->fireBullteAt(m_touchedForFiringPoint);
    }
    
    CCArray *bullets = m_bullets->getActiveBullets();
    CCARRAY_FOREACH(bullets, object)
    {
        Bullet *bullet = dynamic_cast<Bullet*>(object);
        
        CCPoint newPos = bullet->getPosition()+bullet->getVelocity()*dt;
        bullet->setPosition(newPos);
        if (bullet->getPositionX() > 1300 || bullet->getPositionX() < -100) {
            bullet->setIsActive(false);
            bullet->setVisible(false);
        }
    }
}

void ComicWar::fireFromPointTo(cocos2d::CCNode *node,cocos2d::CCPoint fromPos, cocos2d::CCPoint targetPos)
{
    Bullet *bullet = m_bullets->getNexInactiveNode();
    
    if (!bullet) {
        return;
    }
    
    float bulletSpeed= kPlayerBulletSpeed;
    if (node == (CCNode*)m_player) {
        bullet->setBulletType(kBulletFriendly);
    }
    else
    {
        bullet->setBulletType(kBulletHostile);
    }
    bullet->setVisible(true);
    bullet->setPosition(fromPos);
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint vectorDistance = ccp(targetPos.y - fromPos.y,targetPos.x - fromPos.x);
    float radians = vectorToRadians(vectorDistance);
    float degrees = radiansToDegrees(radians);
    
    float radius = screenSize.width;
    CCPoint newTargetPoint = getPositionOnTheCircle(fromPos, radius, degrees);
    
    float duration = 1.0f;
    Enemy *enemy = dynamic_cast<Enemy*>(node);
    if (enemy) {
        float distance = distanceBetweenPoints(newTargetPoint, fromPos);
        bulletSpeed = enemy->getBulletSpeed();
        duration = distance/bulletSpeed;
    }
    
    bullet->setRotation(90-degrees);
    
    float angle = atan2f(targetPos.y-fromPos.y, targetPos.x-fromPos.x);
    angle = radiansToDegrees(angle);
    if (node != m_player) {
        float offset = 0;
        offset += CCRANDOM_MINUS1_1()*2;
        angle += offset;
    }
    angle = degreesToRadians(angle);
    CCPoint velocity = ccp(bulletSpeed*cos(angle), bulletSpeed*sin(angle));
    bullet->setVelocity(velocity);
}

CCArray* ComicWar::getActiveBullets(Enemy* enemy)
{
    return m_bullets->getActiveBullets();
}

void ComicWar::onEnemyFall(Enemy* enemy)
{

}

bool ComicWar::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint touchPoint = pTouch->getLocation();
    m_touchedForFiring = true;
    m_touchedForFiringPoint = touchPoint;
    return true;
}

void ComicWar::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint touchPoint = pTouch->getLocation();
    m_touchedForFiring = true;
    m_touchedForFiringPoint = touchPoint;
}

void ComicWar::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    m_touchedForFiring = false;
}

void ComicWar::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    m_touchedForFiring = false;
}
