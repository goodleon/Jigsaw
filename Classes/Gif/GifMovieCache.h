//
//  GifMovieCache.h
//  Jigsaw
//
//  Created by zhangdw on 15-11-5.
//
//

#ifndef __Jigsaw__GifMovieCache__
#define __Jigsaw__GifMovieCache__

#include "string"
#include "map"
#include "GIFMovie.h"

class GifMovieCache
{
public:
    static GifMovieCache* getInstance();
    void cleanup();

    GIFMovie* getMovie(const std::string& file);

private:
    GifMovieCache();
    ~GifMovieCache();

private:
    std::map<std::string, GIFMovie*> m_cache;
};

#endif /* defined(__Jigsaw__GifMovieCache__) */
