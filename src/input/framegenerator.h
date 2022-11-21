#ifndef FRAMEGENERATOR_H
#define FRAMEGENERATOR_H

#include "common/types.h"
#include "common/frame.h"

// Generates data frames for radar
class FrameGenerator
{
private:
	FrameList _data;

	const int objectCount = 5;
	const int maxWidth = 1200;
	const int maxHeight = 800;

	int _xPos = 0;
	int _yPos = 0;

public:
	FrameGenerator();

public:
	FramePtr nextFrame(int id);
	FrameList nextFrames();

private:
	void init();
};

#endif // FRAMEGENERATOR_H
