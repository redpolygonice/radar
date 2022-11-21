#ifndef IINPUT_H
#define IINPUT_H

#include "common/types.h"
#include "common/frame.h"

#include <QObject>

// Input interface
class IInput : public QObject
{
	Q_OBJECT

public:
	IInput() {}
	virtual ~IInput() {}

signals:
	void dataReady();
	void frameReady(const Frame &frame);
	void framesReady(const FrameList &frames);

public:
	virtual bool open() = 0;
	virtual bool start() = 0;
	virtual void stop() {}
};

typedef std::shared_ptr<IInput> InputPtr;

#endif // IINPUT_H
