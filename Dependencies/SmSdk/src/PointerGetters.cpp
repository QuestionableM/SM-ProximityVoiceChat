#include "SmSdk/Harvestable/HarvestableManager.hpp"
#include "SmSdk/Creation/CreationManager.hpp"
#include "SmSdk/Gui/GuiSystemManager.hpp"
#include "SmSdk/Gui/InGameGuiManager.hpp"
#include "SmSdk/DirectoryManager.hpp"
#include "SmSdk/CharacterManager.hpp"
#include "SmSdk/PlayerManager.hpp"
#include "SmSdk/NetObjManager.hpp"
#include "SmSdk/AudioManager.hpp"
#include "SmSdk/InputManager.hpp"
#include "SmSdk/StaticValues.hpp"
#include "SmSdk/GameSettings.hpp"
#include "SmSdk/MyPlayer.hpp"
#include "SmSdk/GameState.hpp"

#include "SmSdk/config.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#if defined(SMSDK_ENABLE_PHYSICS)
#include "SmSdk/Physics/Physics.hpp"
#endif

//A file that contains all the offsets
#include "SmSdk/offsets.hpp"

/////////USEFUL MACROS

#define GET_GLOBAL_PTR(type, val) *reinterpret_cast<type**>(std::uintptr_t(GetModuleHandle(NULL)) + val)

#define PTR_GETTER_DEFINE(type, func_name, val) type* type::func_name() { return GET_GLOBAL_PTR(type, val); }
#define GET_INSTANCE_DEFINE(type, val) PTR_GETTER_DEFINE(type, GetInstance, val)

/////////GETTER DEFINITIONS

GET_INSTANCE_DEFINE(HarvestableManager, SM_HARVESTABLE_MANAGER_OFFSET);
GET_INSTANCE_DEFINE(DirectoryManager, SM_DIRECTORY_MANAGER_OFFSET);
GET_INSTANCE_DEFINE(InGameGuiManager, SM_IN_GAME_GUI_MANAGER_OFFSET);
GET_INSTANCE_DEFINE(GuiSystemManager, SM_GUI_SYSTEM_MANAGER_OFFSET);
GET_INSTANCE_DEFINE(CharacterManager, SM_CHARACTER_MANAGER_OFFSET);
GET_INSTANCE_DEFINE(CreationManager, SM_CREATION_MANAGER_OFFSET);
GET_INSTANCE_DEFINE(PlayerManager, SM_PLAYER_MANAGER_OFFSET);
GET_INSTANCE_DEFINE(NetObjManager, SM_NET_OBJ_MANAGER_OFFSET);
GET_INSTANCE_DEFINE(AudioManager, SM_AUDIO_MANAGER_OFFSET);
GET_INSTANCE_DEFINE(InputManager, SM_INPUT_MANAGER_OFFSET);
GET_INSTANCE_DEFINE(GameSettings, SM_GAME_SETTINGS_OFFSET);
GET_INSTANCE_DEFINE(MyPlayer, SM_MY_PLAYER_OFFSET);

#if defined(SMSDK_ENABLE_PHYSICS)
GET_INSTANCE_DEFINE(Physics, SM_PHYSICS_OFFSET);
#endif

PTR_GETTER_DEFINE(GameState, GetCurrentState, SM_CURRENT_GAME_STATE_OFFSET);

//STATIC VARIABLE DEFINITIONS

StaticValues::PaintToolEraseLimiterType StaticValues::sm_paintToolEraseLimiter{};
StaticValues::PaintToolPaintLimiterType StaticValues::sm_paintToolPaintLimiter{};