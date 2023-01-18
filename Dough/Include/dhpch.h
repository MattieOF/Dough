#pragma once

// Utility functions and types
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

// Data types
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// Dough core
#include "Dough/Core/Core.h"
#include "Dough/Core/Log.h"

// Assertion
#include "ppk_assert.h"

// Platform specific
#ifdef DH_PLATFORM_WINDOWS
	#include "Windows.h"
#endif
