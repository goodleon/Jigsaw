//
//  JigSprite.h
//  Jigsaw
//
//  Created by zhangdw on 15-12-9.
//
//

#ifndef __Jigsaw__JigSprite__
#define __Jigsaw__JigSprite__

#include "CacheGif.h"
#include "JigHeader.h"

class JigSprite : public GifBase
{
public:
    static JigSprite* create(const string& file);
private:
    JigSprite();
    virtual ~JigSprite();

    virtual bool init(const string& file);

private:
    virtual void updateGif(uint32_t delta);

    bool initGifData();
    void lazyInitFrame();
protected:
    virtual std::string getGifFrameName(int index);
    virtual cocos2d::SpriteFrame* getGifSpriteFrame(Bitmap* bm, int index);
    void addGifSpriteFrame(const GifFrame& frame);
private:
    int m_duration;
    int m_progress;
    int m_currentIndex;
    std::vector<GifSprieFrame*> m_frameData;
};

#endif /* defined(__Jigsaw__JigSprite__) */
