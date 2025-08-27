#include "GameplayTags/CommonWidgetManagerGameplayTags.h"

namespace CommonWidgetManager
{
    namespace UI
    {
        UE_DEFINE_GAMEPLAY_TAG(Root, "UI")

        namespace Layer
        {
            UE_DEFINE_GAMEPLAY_TAG(Root, "UI.Layer")

            namespace Game
            {
                UE_DEFINE_GAMEPLAY_TAG(Root, "UI.Layer.Game")

                UE_DEFINE_GAMEPLAY_TAG(Overlay, "UI.Layer.Game.Overlay")
                UE_DEFINE_GAMEPLAY_TAG(Menu, "UI.Layer.Game.Menu")
            }

            namespace System
            {
                UE_DEFINE_GAMEPLAY_TAG(Root, "UI.Layer.System")

                UE_DEFINE_GAMEPLAY_TAG(Popup, "UI.Layer.System.Popup")
                UE_DEFINE_GAMEPLAY_TAG(Menu, "UI.Layer.System.Menu")
            }
        }
    }
}
