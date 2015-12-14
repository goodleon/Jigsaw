//
//  JigRadio.h
//  Jigsaw
//
//  Created by zhangdw on 15-12-11.
//
//

#ifndef __Jigsaw__JigRadio__
#define __Jigsaw__JigRadio__

#include "JigHeader.h"

class JigRadio
{
public:
    JigRadio();
    ~JigRadio();

    void addItem(CheckBox* item);
    int getSelectedIdx();

    void setSelected(int idx);

    std::function<void(int idx)> onChange;

private:
    void onCheckboxEvent(Ref* check_box,CheckBox::EventType evt);
private:
    vector<CheckBox*> m_items;
};

#endif /* defined(__Jigsaw__JigRadio__) */
