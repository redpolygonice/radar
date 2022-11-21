#ifndef READER_H
#define READER_H

#include "common/types.h"
#include "common/singleton.h"
#include "input/radar.h"
#include "output/screen.h"
#include "output/store.h"
#include "common/frame.h"

#include <QObject>

// The main worker class
class Reader : public QObject, public Singleton<Reader>
{
	friend class Singleton<Reader>;
	Q_OBJECT

private:
	InputPtr _radar;
	OutputPtr _screen;
	OutputPtr _store;

	static constexpr int bufferSize = 4096;
	char buffer[bufferSize];

private:
	Reader();

private slots:
	void dataReady();
	void frameReady(const Frame &frame);
	void framesReady(const FrameList &frames);

public:
	~Reader();

public:
	bool init();
	bool start();
	void stop();
};

#endif // READER_H
