#pragma once

#include "NativeGameplayTags.h"

namespace WidgetManager
{
    namespace UI
    {
        WIDGETMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)

        namespace Layer
        {
            WIDGETMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)

            namespace Game
            {
                WIDGETMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)

                WIDGETMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Overlay)
                WIDGETMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Menu)
            }

            namespace System
            {
                WIDGETMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)

                WIDGETMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Menu)
                WIDGETMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Popup)
            }
        }
    }
}

using namespace WidgetManager;
