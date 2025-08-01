#include "EquipmentTypeTags.h"

namespace EquipmentTypeTags
{
    /* 장비 */
    namespace Equipment
    {
        UE_DEFINE_GAMEPLAY_TAG(Root, "Equipment") // 루트

        /* 무기 */
        namespace Weapon
        {
            UE_DEFINE_GAMEPLAY_TAG(Root, "Equipment.Weapon") // 루트
        }

        /* 방어구 */
        namespace Armor
        {
            UE_DEFINE_GAMEPLAY_TAG(Root, "Equipment.Armor") // 루트
        }

        /* 장신구 */
        namespace Accessory
        {
            UE_DEFINE_GAMEPLAY_TAG(Root, "Equipment.Accessory") // 루트
        }
    }
}
