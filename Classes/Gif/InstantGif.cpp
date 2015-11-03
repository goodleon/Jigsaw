#include "InstantGif.h"

static uint32_t InstantGifId = 0;

bool InstantGif::init(const char* fileName)
{
    m_gif_fullpath = fileName;
    cocos2d::Data data = cocos2d::FileUtils::getInstance()->getDataFromFile(fileName);
	return initWithGifData(data.getBytes(), data.getSize());
}

bool InstantGif::initWithGifData(const uchar* gif_data, size_t size)
{
	if(GifUtils::isGifFile(gif_data) == false)
	{
		return false;
	}

	m_movie = GIFMovie::create(gif_data, size);
	if(m_movie == NULL || m_movie->getGifCount() <= 0)
	{
		return false;
	}

	if(m_movie->getGifCount()>1)
	{
		scheduleUpdate();
	}
	m_movie->setTime(0);
	cocos2d::Texture2D* texture = createTexture(m_movie->bitmap(),0,false);

	return initWithTexture(texture);
}

InstantGif::InstantGif()
{
	m_movie = NULL;

	InstantGifId++;
	if(InstantGifId == UNINITIALIZED_UINT)
	{
		InstantGifId = 0;
	}
	m_instantGifId = InstantGifId;// gif id.
}

std::string InstantGif::getGifFrameName(int index)
{
    // Use id to create framename or texturename, to ensure multiple gifs created under the same path, not confusion in the texture cache
	return cocos2d::CCString::createWithFormat("%s_instant_%u",m_gif_fullpath.c_str(),m_instantGifId)->getCString();
}

InstantGif::~InstantGif()
{
	CC_SAFE_DELETE(m_movie);
	std::string texture = getGifFrameName(0);
    cocos2d::Director::getInstance()->getTextureCache()->removeTextureForKey(texture.c_str());
}

void InstantGif::updateGif(uint32_t delta)
{
	if(m_movie->appendTime(delta))
	{
		cocos2d::Texture2D* texture = createTexture(m_movie->bitmap(),0,false);
		this->setTexture(texture);
	}
}

