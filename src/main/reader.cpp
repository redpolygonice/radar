#include "reader.h"

Reader::Reader()
	: _radar(nullptr)
	, _screen(nullptr)
	, _store(nullptr)
{
}

Reader::~Reader()
{
}

bool Reader::init()
{
	qRegisterMetaType<Frame>("Frame");
	qRegisterMetaType<FrameList>("FrameList");

	if (_radar == nullptr)
		_radar = Radar::create();

	if (!_radar->open())
	{
		std::cout << "Can't init radar device!" << std::endl;
		return false;
	}

	if (_screen == nullptr)
		_screen = Screen::create();

	if (!_screen->open())
	{
		std::cout << "Can't init screen output!" << std::endl;
		return false;
	}

	if (_store == nullptr)
		_store = Store::create();

	if (!_store->open())
	{
		std::cout << "Can't init store output!" << std::endl;
		return false;
	}

	return true;
}

bool Reader::start()
{
	//connect(_radar.get(), SIGNAL(dataReady()), SLOT(dataReady()));
	//connect(_radar.get(), SIGNAL(frameReady(const Frame &)), SLOT(frameReady(const Frame &)));
	connect(_radar.get(), SIGNAL(framesReady(const FrameList &)), SLOT(framesReady(const FrameList &)));
	_radar->start();
	return true;
}

void Reader::stop()
{
	_radar->stop();
	disconnect(_radar.get(), SIGNAL(framesReady(const FrameList &)), this, SLOT(framesReady(const FrameList &)));
}

void Reader::dataReady()
{
	memset(buffer, 0, bufferSize);
#ifdef Q_OS_WIN
	int bytes = read(stdout->_file, buffer, bufferSize);
#else
	int bytes = read(stdout->_fileno, buffer, bufferSize);
#endif
	buffer[bytes] = '\0';
	std::cout << buffer << std::endl;

	Frame frame;
	if (frame.fromJson(buffer))
	{
		_screen->write(frame);
		_store->write(frame);
	}
}

void Reader::frameReady(const Frame &frame)
{
	_screen->write(frame);
	_store->write(frame);
}

void Reader::framesReady(const FrameList &frames)
{
	_screen->write(frames);
	_store->write(frames);
}
