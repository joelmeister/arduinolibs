#ifndef _TAG_H
#define _TAG_H
class Tag{
public:
	Tag()
	Tag(bool);
	virtual ~Tag();
	bool isIt();
	void tagged(); //tag the bot
private:
	bool it;
};
#endif
