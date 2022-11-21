#ifndef TARGET_H
#define TARGET_H

#include "common/types.h"

// Target object
class Target
{
private:
	int _id;

public:
	Target(int id);

public:
	int id() const { return _id; }
};

typedef std::shared_ptr<Target> TargetPtr;
typedef std::vector<TargetPtr> TargetList;
typedef std::vector<TargetPtr>::iterator TargetListIterator;
typedef std::vector<TargetPtr>::const_iterator TargetListConstIterator;

#endif // TARGET_H
