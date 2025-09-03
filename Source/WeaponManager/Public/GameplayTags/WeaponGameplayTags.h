#pragma once

#include "NativeGameplayTags.h"

namespace WeaponManager
{
    namespace Weapon
    {
        WEAPONMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)

        namespace Slot
        {
            WEAPONMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)

            WEAPONMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Primary)
            WEAPONMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Secondary)
            WEAPONMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Special)
        }
    }
}

using namespace WeaponManager;
