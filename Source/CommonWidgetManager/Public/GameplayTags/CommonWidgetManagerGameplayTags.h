#pragma once

#include "NativeGameplayTags.h"

namespace CommonWidgetManager
{
    namespace UI
    {
        COMMONWIDGETMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)

        namespace Layer
        {
            COMMONWIDGETMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)

            namespace Game
            {
                COMMONWIDGETMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)

                COMMONWIDGETMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Overlay)
                COMMONWIDGETMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Menu)
            }

            namespace System
            {
                COMMONWIDGETMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Root)

                COMMONWIDGETMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Menu)
                COMMONWIDGETMANAGER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Popup)
            }
        }
    }
}

using namespace CommonWidgetManager;
