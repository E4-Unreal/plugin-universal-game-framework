#pragma once

#include "NativeGameplayTags.h"

namespace EquipmentTypeTags
{
    /* 장비 */
    namespace Equipment
    {
        EQUIPMENTMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트

        /* 무기 */
        namespace Weapon
        {
            EQUIPMENTMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
        }

        /* 방어구 */
        namespace Armor
        {
            EQUIPMENTMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
        }

        /* 장신구 */
        namespace Accessory
        {
            EQUIPMENTMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root) // 루트
        }
    }
}

using namespace EquipmentTypeTags;
