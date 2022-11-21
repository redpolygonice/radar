#ifndef RADAR_H
#define RADAR_H

#include "common/types.h"
#include "iinput.h"
#include "framegenerator.h"
#include "common/frame.h"

// Radar device implementation
class Radar : public IInput
{
	Q_OBJECT

private:
	std::atomic_bool _active;
	int _updateFreq;
	FrameGenerator _generator;
	std::thread _thread;

public:
	Radar();
	virtual ~Radar();

public:
	static InputPtr create() { return std::make_shared<Radar>(); }
	bool open() override;
	bool start() override;
	void stop() override;

private:
	void run();
	void write(const FramePtr &frame);
};

#endif // RADAR_H
