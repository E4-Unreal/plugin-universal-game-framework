#pragma once

#include "NativeGameplayTags.h"

namespace EquipmentTypeTags
{
    namespace Equipment
    {
        EQUIPMENTMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)

        namespace Weapon
        {
            EQUIPMENTMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
        }

        namespace Armor
        {
            EQUIPMENTMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
        }

        namespace Accessory
        {
            EQUIPMENTMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
        }
    }
}

using namespace EquipmentTypeTags;
