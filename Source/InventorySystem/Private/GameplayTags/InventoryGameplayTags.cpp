#include "GameplayTags/InventoryGameplayTags.h"

namespace InventoryGameplayTags
{
    namespace Item
    {
        UE_DEFINE_GAMEPLAY_TAG(Root, "Item")

        namespace Equipment
        {
            UE_DEFINE_GAMEPLAY_TAG(Root, "Item.Equipment")
        }

        namespace Consumable
        {
            UE_DEFINE_GAMEPLAY_TAG(Root, "Item.Consumable")
        }
    }
}
