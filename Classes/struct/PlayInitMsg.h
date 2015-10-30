
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

};

#endif