
#include "JigScene.h"
#include "cex.h"

JigScene::JigScene()
{
}

JigScene::~JigScene()
{
}

bool JigScene::init()
{
    Return_False_If(!Scene::init());
    
    return true;
}

void JigScene::replaceLayer(cocos2d::Layer* layer)
{
    removeChild(m_layers.back());
    m_layers.pop_back();
    pushLayer(layer);
}

void JigScene::pushLayer(cocos2d::Layer* layer)
{
    if( !m_layers.empty() )
        m_layers.back()->setVisible(false);
    alert(layer);
}

void JigScene::alert(cocos2d::Layer* layer)
{
    addChild(layer);
    m_layers.push_back(layer);
}

void JigScene::popLayer()
{
    removeChild( m_layers.back() );
    m_layers.pop_back();
    
    if( !m_layers.empty() )
        m_layers.back()->setVisible(true);
}



