
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
	void set_main_level(int val);
	int main_level();
	int main_level() const;
private:
	int m_main_level;

public:
	void set_start_level(int val);
	int start_level();
	int start_level() const;
private:
	int m_start_level;

public:
	void set_level_count(int val);
	int level_count();
	int level_count() const;
private:
	int m_level_count;

public:
	void set_rotable(bool val);
	bool rotable();
	bool rotable() const;
private:
	bool m_rotable;

};

#endif