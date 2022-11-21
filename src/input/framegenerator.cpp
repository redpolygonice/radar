#include "framegenerator.h"

FrameGenerator::FrameGenerator()
{
	init();
}

FramePtr FrameGenerator::nextFrame(int id)
{
	FramePtr frame =  Frame::create();
	frame->_id = id;
	frame->_x = _xPos;
	frame->_y = _yPos;
	frame->_state = Frame::State::Leading;
	frame->_ts = time(nullptr);
	return frame;
}

FrameList FrameGenerator::nextFrames()
{
	for (Frame &frame : _data)
	{
		if (frame._y >= maxHeight)
			frame._y = 0;
		frame._y += 2;
		frame._ts = time(nullptr);
	}

	return _data;
}

void FrameGenerator::init()
{
	Frame frame1 { 1, Frame::State::Leading, 0, maxWidth / 2 - 30, 100 };
	Frame frame2 { 2, Frame::State::Leading, 0, maxWidth / 2, 100 };
	Frame frame3 { 3, Frame::State::Leading, 0, maxWidth / 2 - 20, 50 };
	Frame frame4 { 4, Frame::State::Leading, 0,  maxWidth / 2 - 30, 10 };
	Frame frame5 { 5, Frame::State::Leading, 0,  maxWidth / 2 + 10, 60 };
	_data.push_back(frame1);
	_data.push_back(frame2);
	_data.push_back(frame3);
	_data.push_back(frame4);
	_data.push_back(frame5);
}

