#pragma once
#include "Observer.h"
#include "Singleton.h"

enum GameState
{
	gs_none,
	gs_prepare,
	gs_playing,
    gs_pause,
	gs_dead,
	gs_win
};

class GameStateListener
{
public:
	GameStateListener();
	virtual ~GameStateListener();
	virtual void onStateChanged(GameState gs) = 0;
};

class GameStateMgr
	: public cex::Monitor<GameStateListener, GameState>
	, public cex::Singleton<GameStateMgr>
{
public:
	GameStateMgr();

	/*
	 *	notify �Ƿ�֪ͨ��������״̬�Ѿ��ı䣬��ʱ����Ҫ���ĸı����״̬
	 */
	void change(GameState gs, bool notify = true);

	GameState curState() const;
	GameState lastState() const;

private:
	GameState m_curState;
	GameState m_lastState;

    GameStateListener* m_keyListener;
};
