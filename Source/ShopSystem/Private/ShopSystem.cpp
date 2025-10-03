#include "ShopSystem.h"

#include "Internationalization/StringTableRegistry.h"

#define LOCTEXT_NAMESPACE "FShopSystemModule"

void FShopSystemModule::StartupModule()
{
    LOCTABLE_FROMFILE_GAME("Shop", "Shop", "../Resources/Localization/Localization - Shop.csv");
}

void FShopSystemModule::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FShopSystemModule, ShopSystem)
