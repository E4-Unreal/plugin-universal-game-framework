#include "GameplayTags/InteractionGameplayTags.h"

namespace InteractionSystem
{
    namespace Interaction
    {
        UE_DEFINE_GAMEPLAY_TAG(Root, "Interaction")

        UE_DEFINE_GAMEPLAY_TAG(Open, "Interaction.Open")
        UE_DEFINE_GAMEPLAY_TAG(Pickup, "Interaction.Pickup")
        UE_DEFINE_GAMEPLAY_TAG(Talk, "Interaction.Talk")
        UE_DEFINE_GAMEPLAY_TAG(Move, "Interaction.Move")

        UE_DEFINE_GAMEPLAY_TAG(Woodcutting, "Interaction.Woodcutting")
        UE_DEFINE_GAMEPLAY_TAG(Mining, "Interaction.Mining")
        UE_DEFINE_GAMEPLAY_TAG(Fishing, "Interaction.Fishing")
    }
}
