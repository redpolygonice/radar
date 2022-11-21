#include "store.h"

Store::Store()
{
}

Store::~Store()
{
}

bool Store::open()
{
	if (!_db.open())
	{
		std::cout << "Can't open database!" << std::endl;
		return false;
	}

	return true;
}

void Store::close()
{
	_db.close();
}

bool Store::write(const Frame &frame)
{
	if (!_db.isOpen())
		return false;

	_db.add(frame);
	return true;
}

bool Store::write(const FrameList &frames)
{
	if (!_db.isOpen())
		return false;

	_db.add(frames);
	return true;
}
