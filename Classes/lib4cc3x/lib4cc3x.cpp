#include "lib4cc3x.h"
#include "cex.h"

using namespace lib4cc3x;

void lib4cc3x::logPoint( const cocos2d::Point& pt, const char* tip/*=nullptr*/ )
{
	if (nullptr != tip)
	{
		CCLOG("%s:(%.3f,%.3f)", tip, pt.x, pt.y);
	}
	else
	{
		CCLOG("(%.3f,%.3f)", pt.x, pt.y);
	}
}

void lib4cc3x::logSize( const cocos2d::Size& size, const char* tip/*=nullptr*/ )
{
	if (nullptr != tip)
	{
		CCLOG("%s:(%.3f,%.3f)", tip, size.width, size.height);
	}
	else
	{
		CCLOG("(%.3f,%.3f)", size.width, size.height);
	}
}

void lib4cc3x::logRect( const cocos2d::Rect& rect, const char* tip/*=nullptr*/ )
{
	if (nullptr != tip)
	{
		CCLOG("%s:(%.3f,%.3f,%.3f,%.3f)", tip, rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
	}
	else
	{
		CCLOG("(%.3f,%.3f,%.3f,%.3f)", rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
	}
}

bool lib4cc3x::contain( const cocos2d::ValueMap& cfg, const std::string& key )
{
	return cfg.find(key)!=cfg.end();
}

void lib4cc3x::safe_assign( std::string& val, const cocos2d::ValueMap& cfg, const std::string& key )
{
	auto iter = cfg.find(key);
	if (iter != cfg.end())
	{
		val = iter->second.asString();
	}
}

void lib4cc3x::safe_assign( int& val, const cocos2d::ValueMap& cfg, const std::string& key )
{
	auto iter = cfg.find(key);
	if (iter != cfg.end())
	{
		val = iter->second.asInt();
	}
}

void lib4cc3x::safe_assign( float& val, const cocos2d::ValueMap& cfg, const std::string& key )
{
	auto iter = cfg.find(key);
	if (iter != cfg.end())
	{
		val = iter->second.asFloat();
	}
}

cocos2d::SpriteFrame* lib4cc3x::addSpriteFrameByFile(const std::string& image_name)
{
    std::string full_name = cocos2d::FileUtils::getInstance()->fullPathForFilename(image_name);
    cocos2d::Texture2D* texture = cocos2d::Director::getInstance()->getTextureCache()->addImage(full_name);
    
    cocos2d::Rect rc;
    rc.size = texture->getContentSize();
    cocos2d::SpriteFrame* sf = cocos2d::SpriteFrame::createWithTexture(texture, rc);
    
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(sf, image_name);
    
    return sf;
}

cocos2d::Point lib4cc3x::cocos2array(const cocos2d::Point& pt, cocos2d::Node* parent)
{
    return cocos2array(pt.x, pt.y, parent);
}

cocos2d::Point lib4cc3x::cocos2array(int x, int y, cocos2d::Node* parent)
{
    cocos2d::Size screen = parent==nullptr ? \
        cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize() \
        : parent->getContentSize();
    return cocos2d::Point(x, screen.height-y);
}

void lib4cc3x::centerInParent(cocos2d::Node* node)
{
    cocos2d::Node* parent = node->getParent();
    Return_If(!parent);
    
    cocos2d::Size size = parent->getContentSize();
    size.width *= parent->getScaleX();
    size.height *= parent->getScaleY();
    
    node->setPosition(size/2);
}

JigScene* lib4cc3x::getCurScene()
{
    return dynamic_cast<JigScene*>( cocos2d::Director::getInstance()->getRunningScene() );
}