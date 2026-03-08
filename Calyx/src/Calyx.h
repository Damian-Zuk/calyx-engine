#pragma once

#include "Calyx/Core/Base.h"
#include "Calyx/Core/Application.h"
#include "Calyx/Core/GameInstance.h"
#include "Calyx/Core/Layer.h"
#include "Calyx/Core/Input.h"
#include "Calyx/Core/Timer.h"

#include "Calyx/Debug/Assert.h"
#include "Calyx/Debug/Instrumentor.h"

#include "Calyx/Utils/Random.h"
#include "Calyx/Utils/Utils.h"

#include "Calyx/Core/AssetManager.h"
#include "Calyx/Scene/SceneSerializer.h"

#include "Calyx/Events/KeyEvents.h"
#include "Calyx/Events/MouseEvents.h"
#include "Calyx/Events/WindowEvents.h"

#include "Calyx/Scene/SceneManager.h"
#include "Calyx/Scene/PrefabManager.h"

#include "Calyx/Scripting/EntityScript.h"
#include "Calyx/Scripting/AppScript.h"
#include "Calyx/Scripting/GameScript.h"
#include "Calyx/Scripting/ScriptFactory.h"

#include "Calyx/Network/NetworkManager.h"

#include <glm/gtc/type_ptr.hpp>
#include <nlohmann/json.hpp>

#include "Calyx/Serialization/JsonGlmAdapters.h"

#ifdef CX_EDITOR
#include <imgui/imgui.h>
#endif
