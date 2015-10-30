//
//  PlayManager.h
//  Jigsaw
//
//  Created by zhangdw on 15-8-25.
//
//

#ifndef __Jigsaw__PlayManager__
#define __Jigsaw__PlayManager__

#include "GameState.h"
#include "cex.h"
#include "PlayInitMsg.h"

class PlayManager : public cex::Singleton<PlayManager>, public GameStateListener
{
public:
    PlayManager();
    ~PlayManager();
    
    virtual void onStateChanged(GameState gs) override;
    
    void enterGame(const PlayInitMsg& msg);
    void exitGame();
    
    void restart();
    void startNextLevel();
    
//    void saveState();
//    void clearState();

    bool finishAllState();

//    int getstar();
private:
    void reloadResource();

//    int lefttime();
};

#endif /* defined(__Jigsaw__PlayManager__) */
