#include "GameplayTags/WidgetManagerGameplayTags.h"

namespace WidgetManagerGameplayTags
{
    namespace Widget
    {
        UE_DEFINE_GAMEPLAY_TAG(Root, "Widget")

        namespace Layer
        {
            UE_DEFINE_GAMEPLAY_TAG(Root, "Widget.Layer")

            namespace Game
            {
                UE_DEFINE_GAMEPLAY_TAG(Root, "Widget.Layer.Game")

                UE_DEFINE_GAMEPLAY_TAG(Overlay, "Widget.Layer.Game.Overlay")
                UE_DEFINE_GAMEPLAY_TAG(Menu, "Widget.Layer.Game.Menu")
            }

            namespace System
            {
                UE_DEFINE_GAMEPLAY_TAG(Root, "Widget.Layer.System")

                UE_DEFINE_GAMEPLAY_TAG(Popup, "Widget.Layer.System.Popup")
                UE_DEFINE_GAMEPLAY_TAG(Menu, "Widget.Layer.System.Menu")
            }
        }
    }
}
