#include "GameplayTags/SocketGameplayTags.h"

namespace SocketGameplayTags
{
    namespace Socket
    {
        namespace Character
        {
            UE_DEFINE_GAMEPLAY_TAG(Root, "Socket.Character")

            UE_DEFINE_GAMEPLAY_TAG(Head, "Socket.Character.Head")
            UE_DEFINE_GAMEPLAY_TAG(Hair, "Socket.Character.Hair")
            UE_DEFINE_GAMEPLAY_TAG(Face, "Socket.Character.Face")
            UE_DEFINE_GAMEPLAY_TAG(Ear, "Socket.Character.Ear")
            UE_DEFINE_GAMEPLAY_TAG(Beard, "Socket.Character.Beard")
            UE_DEFINE_GAMEPLAY_TAG(UpperBody, "Socket.Character.UpperBody")
            UE_DEFINE_GAMEPLAY_TAG(LowerBody, "Socket.Character.LowerBody")
            UE_DEFINE_GAMEPLAY_TAG(Hand, "Socket.Character.Hand")
            UE_DEFINE_GAMEPLAY_TAG(Foot, "Socket.Character.Foot")
        }

        namespace Equipment
        {
            UE_DEFINE_GAMEPLAY_TAG(Root, "Socket.Equipment")

            UE_DEFINE_GAMEPLAY_TAG(Head, "Socket.Equipment.Head")
            UE_DEFINE_GAMEPLAY_TAG(UpperBody, "Socket.Equipment.UpperBody")
            UE_DEFINE_GAMEPLAY_TAG(LowerBody, "Socket.Equipment.LowerBody")
            UE_DEFINE_GAMEPLAY_TAG(Hand, "Socket.Equipment.Hand")
            UE_DEFINE_GAMEPLAY_TAG(Foot, "Socket.Equipment.Foot")
        }
    }
}
