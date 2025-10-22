#include "GameplayTags/EquipmentTypeTags.h"

namespace EquipmentTypeTags
{
    namespace Equipment
    {
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Root, "Equipment", "장비")

        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Head, "Equipment.Head", "머리")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(UpperBody, "Equipment.UpperBody", "상의")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(LowerBody, "Equipment.LowerBody", "하의")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Hand, "Equipment.Hand", "손")
        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Foot, "Equipment.Foot", "발")

        UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tool, "Equipment.Tool", "도구")
    }
}
