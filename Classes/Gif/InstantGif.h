#ifndef INSTANTGIF_H
#define INSTANTGIF_H

#include "GIFMovie.h"
#include "GifBase.h"
#include "cex.h"

/*
 InstantGif will just decode some raw data when it init.
 The bitmap data will be parsed when need which be used to create CCTexture.
 */
class InstantGif : public GifBase
{
public:
	CREATE_CCOBJ_WITH_PARAM(InstantGif,const char*);
	virtual bool init(const char*);

private:
	virtual bool initWithGifData(const uchar* gif_data, size_t size);
	InstantGif();
	~InstantGif();
	virtual void updateGif(uint32_t delta);
	virtual std::string getGifFrameName(int index);
private:
	GIFMovie* m_movie;
	uint32_t m_instantGifId;
};



#endif//INSTANTGIF_H