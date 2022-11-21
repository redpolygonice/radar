#ifndef FRAME_H
#define FRAME_H

#include "common/types.h"

#include <QString>

class Frame;
typedef std::shared_ptr<Frame> FramePtr;

// Data frame
class Frame
{
	friend class FrameGenerator;

public:
	enum class State
	{
		Unknown,
		Found,
		Leading,
		Lost
	};

private:
	int _id = 0;
	State _state = State::Lost;
	time_t _ts = 0;
	int _x = 0;
	int _y = 0;

public:
	Frame(int id, State state, time_t ts, int x, int y) : _id(id), _state(state), _ts(ts), _x(x), _y(y) {}
	Frame();

public:
	static FramePtr create() { return std::make_shared<Frame>(); }
	QString toJsonText() const;
	bool fromJson(const QString &text);

	int id() const { return _id; }
	int state() const { return static_cast<int>(_state); }
	time_t ts() const { return _ts; }
	int x() const { return _x; }
	int y() const { return _y; }

private:
	QString stateToString(State state) const;
	State stringToState(const QString &text) const;
};

typedef std::vector<Frame> FrameList;
typedef std::vector<Frame>::iterator FrameListIterator;
typedef std::vector<Frame>::const_iterator FrameListConstIterator;
typedef std::shared_ptr<FrameList> FrameListPtr;

#endif // FRAME_H
