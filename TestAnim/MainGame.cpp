//
//  MainGame.cpp
//  TestAnim
//
//  Created by 杨 仑 on 13-9-24.
//
//

#include "MainGame.h"
#include "PlayerSprite.h"

MainGame::MainGame(){
    _targets = new CCArray;
    _projectiles = new CCArray;
    _projectilesDestroyed = 0;
}

MainGame::~MainGame(){
    CC_SAFE_RELEASE_NULL(_targets);
    CC_SAFE_RELEASE_NULL(_projectiles);
}

bool MainGame::init(){
    if (!CCLayerColor::initWithColor(ccc4(255, 255, 255,255))){
        return false;
    }
    return true;
}

void MainGame::onEnter(){
    CCLayer::onEnter();
    CCLog("aaa1");
    CCSprite *player = CCSprite::create("gamesrc/Player.png");
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    player->setPosition(ccp(origin.x + player->getContentSize().width/2,
                            origin.y + visibleSize.height/2) );
    this->addChild(player);
    
    registerWithTouchDispatcher();
    this->schedule( schedule_selector(MainGame::gameLogic), 1.0 );
    this->schedule( schedule_selector(MainGame::updateGame) );
}

void MainGame::onExit(){
    
}

CCScene* MainGame::scene(){
    CCScene* scene = CCScene::create();
    MainGame* game = MainGame::create();
    scene->addChild(game);
    return scene;
}

void MainGame::gameLogic(float dt){
    addTarget();
}

// cpp with cocos2d-x
void MainGame::addTarget()
{
    PlayerSprite* target = PlayerSprite::create();
//    target->setColor(ccc3(50, 50, 50));
    CCSize size =  target->getContentSize();
    CCLog("size width:%f",size.width);
    CCLog("size height:%f",size.height);
    target->run();
    
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
	float minY = target->getContentSize().height/2;
	float maxY = winSize.height -  target->getContentSize().height/2;
	int rangeY = (int)(maxY - minY);
	// srand( TimGetTicks() );
	int actualY = ( rand() % rangeY ) + (int)minY;
    
	target->setPosition(
                        ccp(winSize.width + (target->getContentSize().width/2),
                            CCDirector::sharedDirector()->getVisibleOrigin().y + actualY) );
	this->addChild(target);
    
	int minDuration = (int)2.0;
	int maxDuration = (int)4.0;
	int rangeDuration = maxDuration - minDuration;
    
	int actualDuration = ( rand() % rangeDuration ) + minDuration;
    
	// Create the actions
	CCFiniteTimeAction* actionMove = CCMoveTo::create( (float)actualDuration,
                                                      ccp(0 - target->getContentSize().width/2, actualY) );
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create( this,
                                                             callfuncN_selector(MainGame::spriteMoveFinished));
	target->runAction( CCSequence::create(actionMove, actionMoveDone, NULL) );
    
	// Add to targets array
	target->setTag(1);
	_targets->addObject(target);
}

void MainGame::registerWithTouchDispatcher()
{
	// CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,0,true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}

void MainGame::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	// Choose one of the touches to work with
	CCTouch* touch = (CCTouch*)( touches->anyObject() );
	CCPoint location = touch->getLocation();
    
	CCLog("++++++++after  x:%f, y:%f", location.x, location.y);
    
	// Set up initial location of projectile
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSprite *projectile = CCSprite::create("gamesrc/Projectile.png");
	projectile->setPosition( ccp(origin.x+20, origin.y+winSize.height/2) );
    
	// Determinie offset of location to projectile
	float offX = location.x - projectile->getPosition().x;
	float offY = location.y - projectile->getPosition().y;
    
	// Bail out if we are shooting down or backwards
	if (offX <= 0) return;
    
	// Ok to add now - we've double checked position
	this->addChild(projectile);
    
	// Determine where we wish to shoot the projectile to
	float realX = origin.x+winSize.width + (projectile->getContentSize().width/2);
	float ratio = offY / offX;
	float realY = (realX * ratio) + projectile->getPosition().y;
	CCPoint realDest = ccp(realX, realY);
    
	// Determine the length of how far we're shooting
	float offRealX = realX - projectile->getPosition().x;
	float offRealY = realY - projectile->getPosition().y;
	float length = sqrtf((offRealX * offRealX) + (offRealY*offRealY));
	float velocity = 480/1; // 480pixels/1sec
	float realMoveDuration = length/velocity;
    
    CCSpawn*  action = CCSpawn::create(
                                       CCMoveTo::create(realMoveDuration, realDest),
                                       CCRotateBy::create(1,720),
                                       NULL);
    
    
	// Move projectile to actual endpoint
	projectile->runAction( CCSequence::create(
                                              action,
                                              CCCallFuncN::create(this,
                                                                  callfuncN_selector(MainGame::spriteMoveFinished)),
                                              NULL) );
    
	// Add to projectiles array
	projectile->setTag(2);
	_projectiles->addObject(projectile);
    
    //	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pew-pew-lei.wav");
}

void MainGame::spriteMoveFinished(CCNode* sender)
{
	PlayerSprite *sprite = (PlayerSprite *)sender;
	this->removeChild(sprite, true);
    
	if (sprite->getTag() == 1)  // target
	{
        _targets->removeObject(sprite);
        sprite->removeFromParent();
        
        //		GameOverScene *gameOverScene = GameOverScene::create();
        //		gameOverScene->getLayer()->getLabel()->setString("You Lose :[");
        //		CCDirector::sharedDirector()->replaceScene(gameOverScene);
        
	}
	else if (sprite->getTag() == 2) // projectile
	{
        _projectiles->removeObject(sprite);
        sprite->removeFromParent();
	}
}


void MainGame::updateGame(float dt)
{
	CCArray *projectilesToDelete = new CCArray;
    CCObject* it = NULL;
    CCObject* jt = NULL;
    
	// for (it = _projectiles->begin(); it != _projectiles->end(); it++)
    CCARRAY_FOREACH(_projectiles, it)
	{
		CCSprite *projectile = dynamic_cast<CCSprite*>(it);
		CCRect projectileRect = CCRectMake(
                                           projectile->getPosition().x ,
                                           projectile->getPosition().y ,
                                           projectile->getContentSize().width,
                                           projectile->getContentSize().height);
        
		CCArray* targetsToDelete =new CCArray;
        
		// for (jt = _targets->begin(); jt != _targets->end(); jt++)
        CCARRAY_FOREACH(_targets, jt)
		{
			PlayerSprite *target = dynamic_cast<PlayerSprite*>(jt);
			CCRect targetRect = CCRectMake(
                                           target->getPosition().x ,
                                           target->getPosition().y ,
                                           target->getContentSize().width,
                                           target->getContentSize().height);
            
			// if (CCRect::CCRectIntersectsRect(projectileRect, targetRect))
            if (projectileRect.intersectsRect(targetRect))
			{
				targetsToDelete->addObject(target);
			}
		}
        
		// for (jt = targetsToDelete->begin(); jt != targetsToDelete->end(); jt++)
        CCARRAY_FOREACH(targetsToDelete, jt)
		{
			PlayerSprite *target = dynamic_cast<PlayerSprite*>(jt);
			_targets->removeObject(target);
            
            SEL_CallFuncN selector = callfuncN_selector(MainGame::spriteMoveFinished);
            target->death(this,selector);
            
//			this->removeChild(target, true);

            
			_projectilesDestroyed++;
			if (_projectilesDestroyed >= 5)
			{

//				GameOverScene *gameOverScene = GameOverScene::create();
//				gameOverScene->getLayer()->getLabel()->setString("You Win!");
//				CCDirector::sharedDirector()->replaceScene(gameOverScene);
			}
		}
        
		if (targetsToDelete->count() > 0)
		{
			projectilesToDelete->addObject(projectile);
		}
		targetsToDelete->release();
	}

    CCARRAY_FOREACH(projectilesToDelete, it)
	{
		CCSprite* projectile = dynamic_cast<CCSprite*>(it);
		_projectiles->removeObject(projectile);
		this->removeChild(projectile, true);
	}
	projectilesToDelete->release();
}
