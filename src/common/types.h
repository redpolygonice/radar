#ifndef TYPES_H
#define TYPES_H

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <memory>
#include <fstream>
#include <atomic>
#include <any>
#include <variant>
#include <future>

using std::string;
using std::wstring;

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// String list
typedef std::vector<string> StringList;
typedef std::vector<string>::iterator StringListIterator;
typedef std::vector<string>::const_iterator StringListConstIterator;
typedef std::shared_ptr<string> StringPtr;

// Byte array
typedef std::vector<unsigned char> ByteArray;
typedef std::vector<unsigned char>::iterator ByteArrayIterator;
typedef std::vector<unsigned char>::const_iterator ByteArrayConstIterator;

#endif // TYPES_H
