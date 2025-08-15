#pragma once

#include "NativeGameplayTags.h"

namespace InventoryGameplayTags
{
    namespace Currency
    {
        INVENTORYSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
        INVENTORYSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Default)
    }

    namespace Item
    {
        INVENTORYSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)

        namespace Equipment
        {
            INVENTORYSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
        }

        namespace Consumable
        {
            INVENTORYSYSTEM_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)
        }
    }
}

using namespace InventoryGameplayTags;
