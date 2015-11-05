//
//  GifMovieCache.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-11-5.
//
//

#include "GifMovieCache.h"
#include "GifFrameCache.h"
#include "cocos2d.h"

USING_NS_CC;

using namespace std;

GifMovieCache::GifMovieCache()
{

}

GifMovieCache::~GifMovieCache()
{
    cleanup();
}

GifMovieCache* GifMovieCache::getInstance()
{
    static GifMovieCache instance;
    return &instance;
}

void GifMovieCache::cleanup()
{
    for (auto it = m_cache.begin(); it != m_cache.end(); ++it)
    {
        delete it->second;
    }
    GifFrameCache::getInstance()->cleanup();
    m_cache.clear();
}

GIFMovie* GifMovieCache::getMovie(const std::string& file)
{
    auto ret = m_cache.find(file);
    if (ret != m_cache.end()) {
        return ret->second;
    }

    Data data = FileUtils::getInstance()->getDataFromFile(file);
    GIFMovie* movie = GIFMovie::create(data.getBytes(), data.getSize());
    m_cache.insert( make_pair(file, movie) );
    return movie;
}


