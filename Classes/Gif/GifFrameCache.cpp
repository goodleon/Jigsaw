//
//  GifFrameCache.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-11-5.
//
//

#include "GifFrameCache.h"
#include "GifMovieCache.h"
#include "cocos2d.h"

USING_NS_CC;

using namespace std;

GifFrameCache::GifFrameCache()
{

}

GifFrameCache::~GifFrameCache()
{
    cleanup();
}

GifFrameCache* GifFrameCache::getInstance()
{
    static GifFrameCache instance;
    return &instance;
}

void GifFrameCache::cleanup()
{
    m_cache.clear();
}

const std::vector<GifFrame>& GifFrameCache::getGifFrames(const std::string& file)
{
    auto ret = m_cache.find(file);
    if (ret != m_cache.end()) {
        return ret->second;
    }

    GIFMovie* movie = GifMovieCache::getInstance()->getMovie(file);
    vector<GifFrame> fs;
    for (int i=0; i<movie->getGifCount(); ++i)
    {
        fs.push_back( movie->getGifFrameByIndex(i) );
    }

    return m_cache.insert( make_pair(file, fs) ).first->second;
}

void GifFrameCache::removeFrames(const std::string& file)
{
    m_cache.erase(file);
}


