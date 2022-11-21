#include "screen.h"
#include "main/broker.h"

Screen::Screen()
{
}

Screen::~Screen()
{
}

bool Screen::open()
{
	return true;
}

void Screen::close()
{
}

bool Screen::write(const Frame &frame)
{
	Broker::instance()->updateFrame(frame);
	return true;
}

bool Screen::write(const FrameList &frames)
{
	Broker::instance()->updateFrames(frames);
	return true;
}
