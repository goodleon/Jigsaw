//
//  JigSprite.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-12-9.
//
//

#include "JigSprite.h"

#include "GIFMovie.h"
#include "GifMovieCache.h"
#include "GifFrameCache.h"

USING_NS_CC;

JigSprite::JigSprite()
{
    m_duration = 0;
    m_progress = 0;
    m_currentIndex = UNINITIALIZED_UINT;
}

JigSprite::~JigSprite()
{
    if(m_frameData.size() > 0)
        for(std::vector<GifSprieFrame*>::iterator iter = m_frameData.begin(); iter != m_frameData.end(); )
        {
            GifSprieFrame* sprite = *iter;
            ++iter;

            uint32_t index = sprite->Index();
            std::string gifFrameName = getGifFrameName(index);

            do
            {
                SpriteFrame* spriteFrame   = sprite->getSpriteFrame();
                CC_BREAK_IF(spriteFrame == NULL);

                bool spriteFrameInCache = SpriteFrameCache::getInstance()->getSpriteFrameByName(gifFrameName.c_str()) == spriteFrame;
                //1. just GifSprieFrame retain
                //2. CCSpriteFrameCache and GifSprieFrame retain
                //more. other gif JigSprite retain
                if(spriteFrame->getReferenceCount() == 1 || (spriteFrame->getReferenceCount() ==2 && spriteFrameInCache))
                {
                    Texture2D* texture = sprite->getSpriteFrame()->getTexture();
                    Director::getInstance()->getTextureCache()->removeTexture(texture);
                    SpriteFrameCache::getInstance()->removeSpriteFramesFromTexture(texture);

                }
            } while (0);

            delete sprite;
        }
}

JigSprite* JigSprite::create(const string& file)
{
    JigSprite* ret = new JigSprite();
    ret->init(file);
    ret->autorelease();
    return ret;
}

bool JigSprite::init(const string& file)
{
    m_gif_fullpath = file;

    bool res = false;

    vector<string> ext = cex::split(file, '.');
    if (ext.back()=="gif")
    {
        do
        {
            CC_BREAK_IF(initGifData() == false);
            res = this->initWithSpriteFrame(m_frameData[0]->getSpriteFrame());//init CCSprite with the first frame
        } while (0);

        if(res && m_frameData.size()>0)
        {
            scheduleUpdate();
        }
    }
    else
    {
        res = initWithFile(file);
    }

    return res;
}

std::string JigSprite::getGifFrameName(int index)
{
    const char* frame = CCString::createWithFormat("%s_%d",m_gif_fullpath.c_str(), index)->getCString();
    return frame;
}

// get CCSpriteFrame from cache or create with Bitmap's data
SpriteFrame* JigSprite::getGifSpriteFrame(Bitmap* bm, int index)
{
    std::string gifFrameName = getGifFrameName(index);
    SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(gifFrameName.c_str());
    if(spriteFrame != NULL)
    {
        return spriteFrame;
    }

    do
    {
        Texture2D* texture = createTexture(bm,index,true);
        CC_BREAK_IF(! texture);

        spriteFrame = SpriteFrame::createWithTexture(texture, Rect(0,0,texture->getContentSize().width, texture->getContentSize().height));
        CC_BREAK_IF(! spriteFrame);

        SpriteFrameCache::getInstance()->addSpriteFrame(spriteFrame, gifFrameName.c_str());
    } while (0);


    return spriteFrame;
}

bool JigSprite::initGifData()
{
    GIFMovie* movie = GifMovieCache::getInstance()->getMovie(m_gif_fullpath);
    lazyInitFrame();
    CallFunc* load = CallFunc::create( std::bind(&JigSprite::lazyInitFrame, this) );
    Repeat* repeat = Repeat::create(load, movie->getGifCount());
    this->runAction(repeat);
    return m_frameData.size()>0;
}

void JigSprite::lazyInitFrame()
{
    GIFMovie* movie = GifMovieCache::getInstance()->getMovie(m_gif_fullpath);
    if (m_frameData.size()<movie->getGifCount())
    {
        addGifSpriteFrame(movie->getGifFrameByIndex( m_frameData.size() ));
    }
}

void JigSprite::updateGif(uint32_t delta)
{
    m_progress += delta;

    if(m_progress > m_duration)
    {
        m_progress = m_progress - m_duration;
    }

    uint32_t dur = 0;
    for (int i = 0; i < m_frameData.size(); i++)
    {
        dur += m_frameData[i]->Duration();
        if (dur >= m_progress)// If the progress bigger than sum of pre frame duration，change new CCSpriteFrame to display
        {
            if(m_frameData[i]->Index() != m_currentIndex)
            {
                this->setDisplayFrame(m_frameData[i]->getSpriteFrame());
            }
            m_currentIndex = m_frameData[i]->Index();

            return ;
        }
    }
}

void JigSprite::addGifSpriteFrame(const GifFrame& gifFrame)
{
    if(gifFrame.m_frameData.m_index == UNINITIALIZED_UINT)
    {
        return;
    }

    cocos2d::SpriteFrame* spriteFrame = getGifSpriteFrame(gifFrame.m_bm, gifFrame.m_frameData.m_index);
    
    GifSprieFrame* frame = new GifSprieFrame;
    frame->setFrameData(gifFrame.m_frameData);
    frame->setSpriteFrame(spriteFrame);
    m_frameData.push_back(frame);
    
    m_duration += frame->Duration();
}
