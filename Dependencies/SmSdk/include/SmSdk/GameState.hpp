#pragma once

#include "Network/SteamNetworkServer.hpp"
#include "Network/SteamNetworkClient.hpp"
#include "Network/NetworkServer.hpp"
#include "Network/ListenServer.hpp"
#include "Base/InputTarget.hpp"

#include <memory>

struct GameState : public InputTarget
{
private:
	/* 0x0008 */ char pad_0x8[0x110];

public:
	static GameState* GetCurrentState();
	static SteamNetworkClient* GetSteamNetworkClient();

}; // Size: 0x118
static_assert(sizeof(GameState) == 0x118, "GameState: Incorrect Size");

struct SimpleTimer
{
	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();

	/* 0x0008 */ char pad_0x8[0xC];
	/* 0x0014 */ float timer_value;
}; // Size: 0x18
static_assert(sizeof(SimpleTimer) == 0x18, "SimpleTimer: Incorrect Size");

struct PlayState : public GameState
{
	/* 0x0118 */ char pad_0x118[0x8];
	/* 0x0120 */ std::shared_ptr<ListenServer> listen_server;
	/* 0x0130 */ std::shared_ptr<SteamNetworkClient> steam_network_client;
	/* 0x0140 */ char pad_0x140[0x8];
	/* 0x0148 */ std::shared_ptr<class GameInstance> game_instance;
	/* 0x0158 */ SimpleTimer some_timer;
	/* 0x0170 */ __int32 m_connectionTimeoutIndex;
	/* 0x0174 */ char pad_0x174[0x1C];
}; // Size: 0x190
static_assert(sizeof(PlayState) == 0x190, "PlayState: Incorrect Size");

struct LoadState : public GameState
{
	/* 0x0118 */ char pad_0x118[0x8];
	/* 0x0120 */ std::shared_ptr<GameState> next_state;
	/* 0x0130 */ std::shared_ptr<GameState> prev_state;
	/* 0x0140 */ struct LoadingScreen* loading_screen;
	/* 0x0148 */ char pad_0x148[0x10];
}; // Size: 0x158
static_assert(sizeof(LoadState) == 0x158, "LoadState: Incorrect Size");