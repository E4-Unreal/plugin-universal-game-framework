#include "GameplayTags/WeaponGameplayTags.h"

namespace WeaponManager
{
    namespace Weapon
    {
        UE_DEFINE_GAMEPLAY_TAG(Root, "Weapon")

        namespace Slot
        {
            UE_DEFINE_GAMEPLAY_TAG(Root, "Weapon.Slot")

            UE_DEFINE_GAMEPLAY_TAG(Primary, "Weapon.Slot.Primary")
            UE_DEFINE_GAMEPLAY_TAG(Secondary, "Weapon.Slot.Secondary")
            UE_DEFINE_GAMEPLAY_TAG(Special, "Weapon.Slot.Special")
        }
    }
}
