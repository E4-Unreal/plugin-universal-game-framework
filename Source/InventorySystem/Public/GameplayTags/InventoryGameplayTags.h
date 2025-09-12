#pragma once

#include "NativeGameplayTags.h"

namespace InventoryGameplayTags
{
    namespace Interaction
    {
        INVENTORYSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item)
    }

    namespace Item
    {
        INVENTORYSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)

        namespace Equipment
        {
            INVENTORYSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)

            namespace Weapon
            {
                INVENTORYSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
            }
        }

        namespace Consumable
        {
            INVENTORYSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
        }
    }
}

using namespace InventoryGameplayTags;
