#pragma once

// This file will contain all global definition and types for the engine

#include "Log.hpp"
#include "Types.hpp"

#ifdef MASTER_DEBUG
#include <assert.h>
#define MASTER_CORE_ASSERT(cond, ...)\
if (!(cond))\
{\
MASTER_CORE_CRITICAL(__VA_ARGS__);\
assert(cond);\
}

#define MASTER_ASSERT(cond, ...)\
if (!(cond))\
{\
MASTER_CRITICAL(__VA_ARGS__);\
assert(cond);\
}

#else

#define MASTER_CORE_ASSERT(cond, ...)
#define MASTER_ASSERT(cond, ...)

#endif