#include <SmSdk/Util/Memory.hpp>
#include <SmSdk/offsets.hpp>

#include "SmSdk/Gui/OptionsSubMenuBase.hpp"

SMSDK_BEGIN_NAMESPACE

class GameplayOptionsMenu : public OptionsSubMenuBase
{
	SDK_PUB SMSDK_API static GameplayOptionsMenu* New();
	SDK_PRI SMSDK_API GameplayOptionsMenu();

	SDK_PUB virtual ~GameplayOptionsMenu() = default;
	SDK_PUB void restoreDefaults() override { /* implemented by the game */ }

#if _SM_VERSION_NUM >= 070771
	SDK_MEM_PRI char m_someData[16];
#endif
}; // Size: 0x168

#if _SM_VERSION_NUM >= 070771
SMSDK_CHECK_STRUCT_SIZE(GameplayOptionsMenu, 0x178);
#else
SMSDK_CHECK_STRUCT_SIZE(GameplayOptionsMenu, 0x168);
#endif

SMSDK_END_NAMESPACE