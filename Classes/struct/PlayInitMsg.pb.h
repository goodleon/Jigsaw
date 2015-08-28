
#ifndef __Jigsaw_PlayInitMsg__
#define __Jigsaw_PlayInitMsg__

#include <string>
using namespace std;

class PlayInitMsg
{
public:
	PlayInitMsg();
	~PlayInitMsg();

public:
	void set_choose_level(int val);
	int choose_level();
	int choose_level() const;
private:
	int m_choose_level;

public:
	void set_start_jiglevel(int val);
	int start_jiglevel();
	int start_jiglevel() const;
private:
	int m_start_jiglevel;

public:
	void set_max_level(int val);
	int max_level();
	int max_level() const;
private:
	int m_max_level;

public:
	void set_rotable(bool val);
	bool rotable();
	bool rotable() const;
private:
	bool m_rotable;

public:
	void set_shadow(bool val);
	bool shadow();
	bool shadow() const;
private:
	bool m_shadow;

public:
	void set_max_time(int val);
	int max_time();
	int max_time() const;
private:
	int m_max_time;

};

#endif