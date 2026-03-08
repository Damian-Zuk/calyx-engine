#pragma once
#include "Calyx/Scene/Entity.h"

namespace Calyx {

	class EntityScript;
	class GameScript;
	class AppScript;

	using AddEntityScriptFn = std::function<EntityScript*(Entity)>;
	using AddGameScriptFn = std::function<GameScript*(Scene*)>;
	using AddAppScriptFn = std::function<AppScript*(GameInstance*)>;

	// Native Script Factory
	class ScriptFactory
	{
	public:
		static ScriptFactory& Get();

		ScriptFactory() = default;
		virtual ~ScriptFactory() = default;

		bool RegisterEntityScript(const std::string& className, const AddEntityScriptFn& addFunction);
		bool RegisterGameScript(const std::string& className, const AddGameScriptFn& addFunction);
		bool RegisterAppScript(const std::string& className, const AddAppScriptFn& addFunction);

		EntityScript* AddScriptToEntity(Entity entity, const std::string& className);
		GameScript* AddScriptToScene(Scene* scene, const std::string& className);
		AppScript* AddScriptToGameInstance(GameInstance* game, const std::string& className);

	private:
		std::unordered_map<std::string, AddEntityScriptFn> m_EntityFuncRegistry;
		std::unordered_map<std::string, AddGameScriptFn> m_GameFuncRegistry;
		std::unordered_map<std::string, AddAppScriptFn> m_AppFuncRegistry;

		friend class InspectorPanel;
		friend class EditorMenuBar;
	};
}

#define _SCRICX_GENERATED_BODY(scriptClass) \
	static inline const std::string __ScriptClassName = #scriptClass; \
	virtual const std::string& GetScriptClassName() override { return __ScriptClassName; } \

#define ENTITY_SCRICX_CLASS(scriptClass) _SCRICX_GENERATED_BODY(scriptClass) \
	static inline const bool __FactoryRegistered = \
		Calyx::ScriptFactory::Get().RegisterEntityScript(__ScriptClassName, \
			[&](Calyx::Entity entity){ return entity.AddScript<scriptClass>(); } \
		); \

#define GAME_SCRICX_CLASS(scriptClass) _SCRICX_GENERATED_BODY(scriptClass) \
	static inline const bool __FactoryRegistered = \
		Calyx::ScriptFactory::Get().RegisterGameScript(__ScriptClassName, \
			[&](Calyx::Scene* scene){ return scene->SetGameScript<scriptClass>(); } \
		); \

#define APP_SCRICX_CLASS(scriptClass) _SCRICX_GENERATED_BODY(scriptClass) \
	static inline const bool __FactoryRegistered = \
		Calyx::ScriptFactory::Get().RegisterAppScript(__ScriptClassName, \
			[&](Calyx::GameInstance* instance){ return instance->SetAppScript<scriptClass>(); } \
		); \
