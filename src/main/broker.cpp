#include "broker.h"
#include "common/settings.h"
#include "reader.h"

Broker::Broker(QObject *parent)
	: QObject(parent)
{
}

Broker::~Broker()
{
}

bool Broker::init()
{
	if (!Settings::instance()->load())
		return false;

	if (!Reader::instance()->init())
		return false;

	return true;
}

void Broker::updateFrame(const Frame &frame)
{
	_mutex.lock();
	_frame["id"] = frame.id();
	_frame["state"] = frame.state();
	_frame["x"] = frame.x();
	_frame["y"] = frame.y();
	_frame["ts"] = QVariant::fromValue(frame.ts());
	_mutex.unlock();
	emit frameChanged();
}

void Broker::updateFrames(const FrameList &frames)
{
	_mutex.lock();
	_frames.clear();
	for (const Frame &frame : frames)
	{
		QVariantMap map;
		map["id"] = frame.id();
		map["state"] = frame.state();
		map["x"] = frame.x();
		map["y"] = frame.y();
		map["ts"] = QVariant::fromValue(frame.ts());
		_frames.push_back(map);
	}
	_mutex.unlock();
	emit framesChanged();
}

void Broker::start()
{
	Reader::instance()->start();
}

void Broker::stop()
{
	Reader::instance()->stop();
}
