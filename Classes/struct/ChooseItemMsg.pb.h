
#ifndef __Jigsaw_ChooseItemMsg__
#define __Jigsaw_ChooseItemMsg__

#include <string>
using namespace std;

class ChooseItemMsg
{
public:
	ChooseItemMsg();
	~ChooseItemMsg();

public:
	void set_level(int val);
	int level();
	int level() const;
private:
	int m_level;

public:
	void set_star(int val);
	int star();
	int star() const;
private:
	int m_star;

public:
	void set_canchoose(bool val);
	bool canchoose();
	bool canchoose() const;
private:
	bool m_canchoose;

};

#endif