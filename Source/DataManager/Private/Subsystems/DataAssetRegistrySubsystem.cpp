// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/DataAssetRegistrySubsystem.h"

#include "Data/DataAssetRegistry.h"
#include "Settings/DataManagerSettings.h"

bool UDataAssetRegistrySubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    TArray<UClass*> ChildClasses;
    GetDerivedClasses(GetClass(), ChildClasses, false);

    return ChildClasses.Num() == 0;
}

TSoftObjectPtr<UDataAsset> UDataAssetRegistrySubsystem::GetDataByClass(TSubclassOf<UDataAsset> DataAssetClass, int32 ID) const
{
    if (DataAssetClass && ID >= 0)
    {
        for (const auto& DataAssetRegistry : UDataManagerSettings::Get()->GetDataAssetRegistries())
        {
            if (DataAssetRegistry->IsChildOf(DataAssetClass))
            {
                return DataAssetRegistry->GetDataByID(ID);
            }
        }
    }

    return nullptr;
}

TSoftObjectPtr<UDataAsset> UDataAssetRegistrySubsystem::GetDataByInterface(TSubclassOf<UInterface> InterfaceClass, int32 ID) const
{
    if (InterfaceClass && ID >= 0)
    {
        for (const auto& DataAssetRegistry : UDataManagerSettings::Get()->GetDataAssetRegistries())
        {
            if (DataAssetRegistry->Implements(InterfaceClass))
            {
                return DataAssetRegistry->GetDataByID(ID);
            }
        }
    }

    return nullptr;
}
