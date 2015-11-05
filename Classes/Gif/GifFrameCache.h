//
//  GifFrameCache.h
//  Jigsaw
//
//  Created by zhangdw on 15-11-5.
//
//

#ifndef __Jigsaw__GifFrameCache__
#define __Jigsaw__GifFrameCache__

#include "string"
#include "vector"
#include "map"
#include "Bitmap.h"

class GifFrameCache
{
public:
    static GifFrameCache* getInstance();
    void cleanup();

    const std::vector<GifFrame>& getGifFrames(const std::string& file);
    void removeFrames(const std::string& file);
private:
    GifFrameCache();
    ~GifFrameCache();

private:
    std::map< std::string, std::vector<GifFrame> > m_cache;
};

#endif /* defined(__Jigsaw__GifFrameCache__) */
