#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include <iostream>

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    
    std::vector<std::string> searchPaths;
    searchPaths.push_back("sound");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("1.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("2.wav");
    //cocos2d::log("%f", director->getVisibleSize().height);
    std::cout << director->getVisibleSize().height << std::endl;
    if (director->getVisibleSize().height == 960) {
        
        auto glview = director->getOpenGLView();
        if(!glview) {
            glview = GLViewImpl::createWithRect("OneOrZero", Rect(0, 0, 960, 640));
            director->setOpenGLView(glview);
        }
        
        searchPaths.push_back("res/iP4S");
        director->getOpenGLView()->setDesignResolutionSize(640, 960, ResolutionPolicy::SHOW_ALL);
        cocos2d::FileUtils::getInstance()->setSearchPaths(searchPaths);
    } else if (director->getVisibleSize().height == 1136) { // iPhone5 or iPhone5S or iPod touch 5
        
        auto glview = director->getOpenGLView();
        if(!glview) {
            glview = GLViewImpl::createWithRect("OneOrZero", Rect(0, 0, 1136, 640));
            director->setOpenGLView(glview);
        }
        
        searchPaths.push_back("res/iP5");
        director->getOpenGLView()->setDesignResolutionSize(640, 1136, ResolutionPolicy::SHOW_ALL);
        cocos2d::FileUtils::getInstance()->setSearchPaths(searchPaths);
    } else if (director->getVisibleSize().height == 1334) {
        
        auto glview = director->getOpenGLView();
        if(!glview) {
            glview = GLViewImpl::createWithRect("OneOrZero", Rect(0, 0, 1334, 750));
            director->setOpenGLView(glview);
        }
        
        searchPaths.push_back("res/iP6");
        director->getOpenGLView()->setDesignResolutionSize(750, 1334, ResolutionPolicy::SHOW_ALL);
        cocos2d::FileUtils::getInstance()->setSearchPaths(searchPaths);
    } else if (director->getVisibleSize().height == 2208) {
        
        auto glview = director->getOpenGLView();
        if(!glview) {
            glview = GLViewImpl::createWithRect("OneOrZero", Rect(0, 0, 2208, 1242));
            director->setOpenGLView(glview);
        }
        
        searchPaths.push_back("res/iP6P");
        director->getOpenGLView()->setDesignResolutionSize(1242, 2208, ResolutionPolicy::SHOW_ALL);
        cocos2d::FileUtils::getInstance()->setSearchPaths(searchPaths);
    }
    
    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");

    // create a scene. it's an autorelease object
    auto scene = IndexScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
