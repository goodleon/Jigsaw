
#ifndef __Jigsaw_JigScene_
#define __Jigsaw_JigScene_

#include "cocos2d.h"

class JigScene : public cocos2d::Scene
{
public:
    JigScene();
    virtual ~JigScene() override;
    
    CREATE_FUNC(JigScene);
    
    virtual bool init() override;
    
    void replaceLayer(cocos2d::Layer* layer);
    void pushLayer(cocos2d::Layer* layer);
    void popLayer();
    
    void alert(cocos2d::Layer* layer);
    void dismiss(cocos2d::Layer* layer);

    void showTip(cocos2d::Layer* layer, const cocos2d::Point& pt);
    
private:
    void pushChild(cocos2d::Layer* layer);
    
private:
    std::vector<cocos2d::Layer*> m_layers;
    
    std::vector<cocos2d::Layer*> m_alerts;
};

#endif