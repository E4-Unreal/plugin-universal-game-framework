#include "GameplayTags/InventoryGameplayTags.h"

namespace InventoryGameplayTags
{
    namespace Currency
    {
        UE_DEFINE_GAMEPLAY_TAG(Root, "Currency")
        UE_DEFINE_GAMEPLAY_TAG(Default, "Currency.Default")
    }

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
