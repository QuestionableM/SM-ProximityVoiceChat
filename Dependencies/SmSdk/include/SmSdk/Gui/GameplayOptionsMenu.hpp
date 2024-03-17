#include <SmSdk/Util/Memory.hpp>
#include <SmSdk/offsets.hpp>

#include "OptionsSubMenuBase.hpp"

class GameplayOptionsMenu : public OptionsSubMenuBase
{
public:
	GameplayOptionsMenu()
	{
		OptionsSubMenuBase::GameConstructor(this);
		Memory::OverwriteVftable(this, SM_VTBL_GAMEPLAY_OPTIONS_MENU_OFFSET);
	}

	virtual ~GameplayOptionsMenu() = default;
	void restoreDefaults() override { /* implemented by the game */ }

}; // Size: 0x168

static_assert(sizeof(GameplayOptionsMenu) == 0x168, "GameplayOptionsMenu: Incorrect Size");