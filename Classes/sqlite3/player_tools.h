//
//  player_tools.h
//  Jigsaw
//
//  Created by zhangdw on 15-12-29.
//
//

#ifndef __Jigsaw__player_tools__
#define __Jigsaw__player_tools__

#include "sql_common.h"
#include "DBRecord.h"

namespace player_tools {

    int get_next_imgid();
    int get_max_finished_imgid();

    bool check_save_record(const DBRecord& rd);

    int calc_score(int image_conf);
}

#endif /* defined(__Jigsaw__player_tools__) */
