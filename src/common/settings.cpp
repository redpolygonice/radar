#include "settings.h"

Settings::Settings()
{
}

Settings::~Settings()
{
}

bool Settings::load()
{
	_data["historyDepth"] = 60 *60 * 24 * 30 * 6;
	_data["updateFreq"] = 200;
	_data["objectCount"] = 5;
	return true;
}

bool Settings::save()
{
	return true;
}
