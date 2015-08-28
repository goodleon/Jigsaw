#pragma once
#include "cocos2d.h"
#include "JigScene.h"

namespace lib4cc3x
{
	void logPoint(const cocos2d::Point& pt, const char* tip=nullptr);
	void logSize(const cocos2d::Size& size, const char* tip=nullptr);
	void logRect(const cocos2d::Rect& rect, const char* tip=nullptr);

	bool contain(const cocos2d::ValueMap& cfg, const std::string& key);
	void safe_assign(std::string& val, const cocos2d::ValueMap& cfg, const std::string& key);
	void safe_assign(int& val, const cocos2d::ValueMap& cfg, const std::string& key);
	void safe_assign(float& val, const cocos2d::ValueMap& cfg, const std::string& key);

    cocos2d::SpriteFrame* addSpriteFrameByFile(const std::string& image_name);
    
    cocos2d::Point cocos2array(const cocos2d::Point& pt, cocos2d::Node* parent);
    cocos2d::Point cocos2array(int x, int y, cocos2d::Node* parent);
    
    void centerInParent(cocos2d::Node* node);

    JigScene* getCurScene();
}
