#include "GameplayTags/InventoryGameplayTags.h"

namespace InventoryGameplayTags
{
    namespace Interaction
    {
        UE_DEFINE_GAMEPLAY_TAG(Item, "Interaction.Item")
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
