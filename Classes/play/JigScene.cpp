
#include "JigScene.h"
#include "cex.h"
#include "TipsLayer.h"

USING_NS_CC;

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

    pushChild(layer);
}

void JigScene::popLayer()
{
    removeChild( m_layers.back() );
    m_layers.pop_back();
    
    if( !m_layers.empty() )
        m_layers.back()->setVisible(true);
}

void JigScene::alert(cocos2d::Layer* layer)
{
    assert( std::find(m_alerts.begin(), m_alerts.end(), layer)==m_alerts.end() );

    if (!m_alerts.empty())
    {
        m_alerts.back()->setVisible(false);
    }

    m_alerts.push_back(layer);
    addChild(layer);
    
    layer->setScale(0.5f);
    
    Sequence* seq = Sequence::create( ScaleTo::create(0.1, 1.1f), ScaleTo::create(0.05, 1.0f), NULL);
    layer->runAction( seq );
}

void JigScene::dismiss(cocos2d::Layer* layer)
{
    auto target = std::find(m_alerts.begin(), m_alerts.end(), layer);
    assert(target!=m_alerts.end());
    m_alerts.erase(target);
    
    auto remove = [=](){
        this->removeChild(layer);
        if (!m_alerts.empty()) {
            m_alerts.back()->setVisible(true);
        }
    };
    Sequence* seq = Sequence::create( ScaleTo::create(0.05, 1.1f), ScaleTo::create(0.1, 0.5f), CallFunc::create(remove), NULL);
    layer->runAction( seq );
}

void JigScene::showTip(cocos2d::Layer* layer, const Point& pt)
{
    layer->setPosition(pt);

    TipsLayer* tip = TipsLayer::create();
    tip->addContent(layer);
    addChild(tip);
}

void JigScene::pushChild(cocos2d::Layer* layer)
{
    addChild(layer);
    m_layers.push_back(layer);
}

