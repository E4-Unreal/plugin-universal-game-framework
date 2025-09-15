#include "GameplayTags/InventoryGameplayTags.h"

namespace InventorySystem
{
    namespace Interaction
    {
        UE_DEFINE_GAMEPLAY_TAG(Pickup, "Interaction.Pickup")

        namespace Open
        {
            UE_DEFINE_GAMEPLAY_TAG(Box, "Interaction.Open.Box")
        }
    }

    namespace Item
    {
        UE_DEFINE_GAMEPLAY_TAG(Root, "Item")

        namespace Equipment
        {
            UE_DEFINE_GAMEPLAY_TAG(Root, "Item.Equipment")

            namespace Weapon
            {
                UE_DEFINE_GAMEPLAY_TAG(Root, "Item.Equipment.Weapon")
            }
        }

        namespace Consumable
        {
            UE_DEFINE_GAMEPLAY_TAG(Root, "Item.Consumable")
        }
    }
}
