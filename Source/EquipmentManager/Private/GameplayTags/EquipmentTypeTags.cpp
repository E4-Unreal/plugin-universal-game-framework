#include "GameplayTags/EquipmentTypeTags.h"

namespace EquipmentTypeTags
{
    namespace Equipment
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Equipment", "장비")

        namespace Weapon
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Equipment.Weapon", "무기")
        }

        namespace Armor
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Equipment.Armor", "방어구")
        }

        namespace Accessory
        {
            UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Equipment.Accessory", "장신구")
        }
    }
}
