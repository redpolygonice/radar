#ifndef SCREEN_H
#define SCREEN_H

#include "common/types.h"
#include "ioutput.h"

// Screeen output
class Screen : public IOutput
{
public:
	Screen();
	virtual ~Screen();

public:
	static OutputPtr create() { return std::make_shared<Screen>(); }
	bool open() override;
	void close() override;
	bool write(const Frame &frame) override;
	bool write(const FrameList &frames) override;
};

#endif // SCREEN_H
