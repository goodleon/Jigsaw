//
//  TouchPanelEventListener.h
//  Jigsaw
//
//  Created by zhangdw on 15-12-2.
//
//

#ifndef Jigsaw_TouchPanelEventListener_h
#define Jigsaw_TouchPanelEventListener_h

#include "JigAudio.h"

enum TouchPanelEvent
{
    TPE_BeginMove,
    TPE_Moving,
    TPE_EndMove,
    TPE_Dropped,
    TPE_Click
};

class TouchPanel;
class TouchPanelEventListener
{
public:
    TouchPanelEventListener(TouchPanel* panel){ m_panel = panel; };
    virtual ~TouchPanelEventListener(){ m_panel = nullptr; };

    virtual void onEvent(TouchPanelEvent event) = 0;

protected:
    TouchPanel* m_panel;
};

class TouchPanelSound : public TouchPanelEventListener
{
public:
    TouchPanelSound(TouchPanel* panel)
    :TouchPanelEventListener(panel)
    {
    }

    virtual void onEvent(TouchPanelEvent event)
    {
        if (event==TPE_Dropped)
        {
            playEffect(audio_drop_end);
        }
        else if (event==TPE_Click)
        {
            playEffect(audio_btn);
        }
    }
};

#endif
