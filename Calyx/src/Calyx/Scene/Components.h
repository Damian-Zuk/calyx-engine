#pragma once

#include "Calyx/Core/UUID.h"
#include "Calyx/Graphics/Sprite.h"
#include "Calyx/Graphics/ResizableSprite.h"
#include "Calyx/Graphics/Camera.h"
#include "Calyx/Graphics/SpriteAnimation.h"
#include "Calyx/Graphics/Renderer/Font.h"
#include "Calyx/Scripting/ScriptField.h"
#include "Calyx/Physics/PhysicsCommon.h"
#include "Calyx/Network/Common.h"
#include "Calyx/Network/NetTransform.h"
#include "Calyx/Network/ReplicatedScript.h"

#include <entt/entity/entity.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <box2d/b2_body.h>

namespace Calyx {

	#define CX_COMPONENT_CLASS(TComponent) \
		static constexpr std::string_view _ClassName() { return #TComponent; }

	struct IDComponent
	{
		CX_COMPONENT_CLASS(IDComponent)

		UUID ID;
		UUID RefID = 0;
	};

	struct TagComponent
	{
		CX_COMPONENT_CLASS(TagComponent)

		std::string Tag;
	};

	struct TransformComponent
	{
		CX_COMPONENT_CLASS(TransformComponent)

		glm::vec3 WorldPosition { 0.0f, 0.0f, 0.0f };
		glm::vec3 LocalPosition { 0.0f, 0.0f, 0.0f };
		float Rotation { 0.0f };
		glm::vec2 Scale { 1.0f, 1.0f };
	};

	struct PrefabComponent
	{
		CX_COMPONENT_CLASS(PrefabComponent)

		UUID PrefabUUID;
	};

	struct RelationshipComponent
	{
		CX_COMPONENT_CLASS(RelationshipComponent)

		uint32_t ChildrenCount = 0;
		entt::entity First  { entt::null };
		entt::entity Prev   { entt::null };
		entt::entity Next   { entt::null };
		entt::entity Parent { entt::null };
	};

	struct CameraComponent
	{
		CX_COMPONENT_CLASS(CameraComponent)

		Camera Camera;
		glm::vec2 PositionOffset{ 0.0f, 0.0f };
	};

	struct SpriteComponent
	{
		CX_COMPONENT_CLASS(SpriteComponent)

		SpriteComponent() = default;
		SpriteComponent(const std::string& filepath)
		{
			if (filepath.size())
				Sprite.SetTextureFromPath(filepath);
		}

		Sprite Sprite;
		glm::vec4 Color { 1.0f, 1.0f, 1.0f, 1.0f };
		float TilingFactor = 1.0f;
	};

	struct ResizableSpriteComponent
	{
		CX_COMPONENT_CLASS(ResizableSpriteComponent)

		ResizableSprite ResizableSprite;
		glm::vec4 Color { 1.0f, 1.0f, 1.0f, 1.0f };
	};

	struct CircleRendererComponent
	{
		CX_COMPONENT_CLASS(CircleRendererComponent)

		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
		float Thickness = 1.0f;
		float Fade = 0.005f;
	};

	struct TextComponent
	{
		CX_COMPONENT_CLASS(TextComponent)

		Shared<Font> FontAsset = Font::GetDefault();
		std::string TextString;
		glm::vec4 Color{ 1.0f };
		float Kerning = 0.0f;
		float LineSpacing = 0.0f;
		bool Hidden = false;
	};

	struct SpriteAnimationComponent
	{
		CX_COMPONENT_CLASS(SpriteAnimationComponent)

		SpriteAnimation SpriteAnimation;
	};

	class EntityScript; // forward declaration

	struct ScriptComponent
	{
		CX_COMPONENT_CLASS(ScriptComponent)

		std::unordered_map<std::string, EntityScript*> Scripts;
	};

	struct RigidbodyComponent
	{
		CX_COMPONENT_CLASS(RigidbodyComponent)

		b2Body* RuntimeBody = nullptr;
		b2BodyType Type = b2_staticBody;
		float LinearDamping = 0.0f;
		float AngularDamping = 0.0f;
		float GravityScale = 1.0f;
		bool IsBullet = false;
		bool FixedRotation = false;
		bool AttachToParent = false; // Revolute Joint
	};

	struct BoxColliderComponent
	{
		CX_COMPONENT_CLASS(BoxColliderComponent)

		b2Fixture* RuntimeFixture = nullptr;
		glm::vec2 Size { 1.0f, 1.0f };
		glm::vec2 Offset { 0.0f, 0.0f };
		PhysicsMaterial Material;
		PhysicsContactCallback ContactCallback;
		b2Filter Filter;
		bool IsSensor = false;
		bool AttachToParent = false;
	};

	struct CircleColliderComponent
	{
		CX_COMPONENT_CLASS(CircleColliderComponent)

		b2Fixture* RuntimeFixture = nullptr;
		glm::vec2 Offset = { 0.0f, 0.0f };
		float Radius = 1.0f;
		PhysicsMaterial Material;
		PhysicsContactCallback ContactCallback;
		bool IsSensor = false;
		bool AttachToParent = false;
	};

	struct NetworkComponent
	{
		CX_COMPONENT_CLASS(NetworkComponent)

		bool SimulateOnClient = true;
		bool WasReplicated = false;
		NetTransform NetTransform;
		ReplicatedScripts ReplicatedScripts;

		// Server-only data (todo: store in separate EnTT component)
		std::unordered_map<ClientID, NetTransform::SequencedValue> ClientDataMap;
	};

	template<typename... Component>
	struct ComponentGroup
	{
	};

}
