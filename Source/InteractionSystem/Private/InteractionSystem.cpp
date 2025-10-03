#include "InteractionSystem.h"

#include "Internationalization/StringTableRegistry.h"

#define LOCTEXT_NAMESPACE "FInteractionSystemModule"

void FInteractionSystemModule::StartupModule()
{
    LOCTABLE_FROMFILE_GAME("Interaction", "Interaction", "../Resources/Localization/Localization - Interaction.csv");
}

void FInteractionSystemModule::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FInteractionSystemModule, InteractionSystem)
