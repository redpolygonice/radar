#ifndef STORE_H
#define STORE_H

#include "common/types.h"
#include "ioutput.h"
#include "database.h"

// Store output
class Store : public IOutput
{
private:
	Database _db;

public:
	Store();
	virtual ~Store();

public:
	static OutputPtr create() { return std::make_shared<Store>(); }
	bool open() override;
	void close() override;
	bool write(const Frame &frame) override;
	bool write(const FrameList &frames) override;
};

#endif // STORE_H
