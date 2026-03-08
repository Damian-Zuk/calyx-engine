#include "cxpch.h"
#include "Calyx/Physics/PhysicsCommon.h"
#include "Calyx/Scene/Entity.h"
#include "Calyx/Scripting/EntityScript.h"

namespace Calyx {

	bool PhysicsContact::OtherCompare(Entity* entity)
	{
		return *Other == *entity;
	}

	bool PhysicsContact::OtherCompare(EntityScript* script)
	{
		return Other->m_Handle == script->m_Handle;
	}

}
