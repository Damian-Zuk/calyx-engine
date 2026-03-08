#pragma once
#include "Calyx/Scripting/Script.h"
#include "Calyx/Network/Common.h"

namespace Calyx {

	class AppScript : public Calyx::Script
	{
	public:
		AppScript();
		virtual ~AppScript() = default;

		virtual void OnPreInit() override {};
		virtual bool OnCreate() override { return true; }
		virtual void OnDestroy() override {};
		virtual void OnUpdate(float ts) {};
		virtual void OnFixedUpdate(float ts) override {};
		virtual void OnEvent(Event& event) override {};
		virtual void OnImGuiRender() override {};

		// Network
		virtual void Client_OnConnected() {}
		virtual void Server_OnClientConnected(ClientID clientID) {}

		virtual void Client_OnDisconnected(ConnectionEndCode code) {}
		virtual void Server_OnClientDisconnected(ClientID clientID) {}

		virtual void Client_OnCustomMessage(NetworkStreamReader& stream) {};
		virtual void Server_OnCustomMessage(ClientID clientID, NetworkStreamReader& stream) {};

		friend class GameInstance;
	};

}