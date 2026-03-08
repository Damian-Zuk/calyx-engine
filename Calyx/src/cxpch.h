#pragma once

#include <iostream>
#include <functional>
#include <memory>
#include <sstream>
#include <cassert>

#include <string>
#include <vector>
#include <array>
#include <map>
#include <unordered_map>

#if CALYX_PLATFORM_WINDOWS
#include <Windows.h>
#endif

#include "Calyx/Core/Base.h"
#include "Calyx/Debug/Assert.h"
#include "Calyx/Debug/Instrumentor.h"

#include "Calyx/Serialization/JsonGlmAdapters.h"
