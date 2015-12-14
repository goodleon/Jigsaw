//
//  JigRadio.cpp
//  Jigsaw
//
//  Created by zhangdw on 15-12-11.
//
//

#include "JigRadio.h"

JigRadio::JigRadio()
{

}

JigRadio::~JigRadio()
{

}

void JigRadio::addItem(cocos2d::ui::CheckBox *item)
{
    item->addEventListener( std::bind(&JigRadio::onCheckboxEvent, this, placeholders::_1, placeholders::_2) );
    m_items.push_back(item);
}

void JigRadio::onCheckboxEvent(cocos2d::Ref *check_box, CheckBox::EventType evt)
{
    CheckBox* box = static_cast<CheckBox*>(check_box);
    if (evt == CheckBox::EventType::UNSELECTED)
    {
        auto cur_selected = std::count_if(m_items.begin(), m_items.end(), std::mem_fun(&CheckBox::isSelected));
        if (cur_selected==0) {
            box->setSelected(true);
        }
    }
    else
    {
        for (auto it=m_items.begin(); it!=m_items.end(); ++it)
        {
            if ((*it)!=box)
            {
                (*it)->setSelected(false);
            }
        }
    }

    if (onChange) {
        onChange( getSelectedIdx() );
    }
}

int JigRadio::getSelectedIdx()
{
    auto target = std::find_if(m_items.begin(), m_items.end(), std::mem_fun(&CheckBox::isSelected));
    return std::distance(m_items.begin(), target);
}

void JigRadio::setSelected(int idx)
{
    std::for_each(m_items.begin(), m_items.end(), std::bind( std::mem_fun(&CheckBox::setSelected), placeholders::_1, false));
    m_items.at(idx)->setSelected(true);
    if (onChange) {
        onChange( getSelectedIdx() );
    }
}

