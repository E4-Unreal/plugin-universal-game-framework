// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/DynamicDataSubsystem.h"

#include "Data/DefinitionBase.h"
#include "Engine/AssetManager.h"

bool UDynamicDataSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    TArray<UClass*> ChildClasses;
    GetDerivedClasses(GetClass(), ChildClasses, false);

    return ChildClasses.Num() == 0;
}

UDefinitionBase* UDynamicDataSubsystem::GetDefinition(TSubclassOf<UDefinitionBase> DefinitionClass, int32 ID)
{
    if (!DefinitionClass || ID < 0) return nullptr;

    UDefinitionBase* Definition = nullptr;

    UAssetManager& AssetManager = UAssetManager::Get();
    FPrimaryAssetId AssetID = FPrimaryAssetId(DefinitionClass->GetFName(), FName(FString::FromInt(ID)));
    FAssetData AssetData;
    AssetManager.GetPrimaryAssetData(AssetID, AssetData);

    if (AssetData.IsValid() && AssetData.GetAsset()->IsA(DefinitionClass))
    {
        Definition = Cast<UDefinitionBase>(AssetData.GetAsset());
    }

    return Definition;
}
