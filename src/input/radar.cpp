#include "radar.h"
#include "common/settings.h"

Radar::Radar()
	: _active(false)
	, _updateFreq(Settings::instance()->value("updateFreq").toInt())
{
}

Radar::~Radar()
{
}

bool Radar::open()
{
	return true;
}

bool Radar::start()
{
	if (_active)
		return true;

	_active = true;
	_thread = std::thread([this]() { run(); });
	return true;
}

void Radar::stop()
{
	_active = false;
	if (_thread.joinable())
		_thread.join();
}

void Radar::run()
{
	while (_active)
	{
		//FramePtr frame = _generator.nextFrame(1);
		//write(frame);
		//emit dataReady();
		//emit frameReady(*frame);

		FrameList frames = _generator.nextFrames();
		emit framesReady(frames);
		std::this_thread::sleep_for(std::chrono::milliseconds(_updateFreq));
	}
}

void Radar::write(const FramePtr &frame)
{
	fwrite(frame->toJsonText().toStdString().c_str(), 1, frame->toJsonText().size(), stdout);
}
