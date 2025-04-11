// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemDatabase.h"

#include "EditorAssetLibrary.h"
#include "Logging.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Data/ItemDefinition.h"
#include "UObject/SavePackage.h"

void UItemDatabase::HardUpdate()
{
    LOG(Log, TEXT("Hard Update ItemDatabase"))

    DeleteAllItemDefinitions();

    Update();
}

void UItemDatabase::DeleteAllItemDefinitions()
{
    for (auto [ID, ItemDefinition] : ItemDefinitionMap)
    {
        FString PackageName = ItemDefinition->GetPathName();
        UEditorAssetLibrary::DeleteAsset(PackageName);
    }

    ItemDefinitionMap.Reset();
}

void UItemDatabase::Update()
{
    if (ItemDataTable == nullptr) return;

    GetPackage()->FullyLoad();

    TArray<FTableRowBase*> Rows;
    const TArray<FName> RowNames = ItemDataTable->GetRowNames();

    for (const auto& RowName : RowNames)
    {
        /* Check ID */
        FString IDString = RowName.ToString();
        if (!IDString.IsNumeric())
        {
            LOG(Error, TEXT("ID should be numeric!"))
            continue;
        }

        int32 ID = FCString::Atoi(*IDString);
        if (ID < 0)
        {
            LOG(Error, TEXT("ID should be positive number!"))
            continue;
        }

        /* Create ItemDefinition */

        UItemDefinition* NewItemDefinition = CreateItemDefinition(ID);
        UpdateItemDefinition(NewItemDefinition, ID, ItemDataTable->FindRow<FTableRowBase>(RowName, ""));
        ItemDefinitionMap.Emplace(ID, NewItemDefinition);
    }

    UEditorAssetLibrary::SaveAsset(GetPackage()->GetPathName());
}

UItemDefinition* UItemDatabase::CreateItemDefinition(int32 ID) const
{
    /* Create Package */
    FString AssetName = GetAssetName(ID);
    FString PackageName = GetPackageName(ID);

    UPackage* Package = CreatePackage(*PackageName);
    Package->FullyLoad();

    /* Create Asset */
    UItemDefinition* NewItemDefinition = NewObject<UItemDefinition>(Package, *AssetName, RF_Public | RF_Standalone | RF_MarkAsRootSet);

    Package->MarkPackageDirty();
    FAssetRegistryModule::AssetCreated(NewItemDefinition);

    /* Save Package */
    FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());

    FSavePackageArgs SavePackageArgs;
    SavePackageArgs.TopLevelFlags = RF_Public | RF_Standalone;
    SavePackageArgs.bForceByteSwapping = true;
    SavePackageArgs.SaveFlags = SAVE_NoError;

    UPackage::SavePackage(Package, NewItemDefinition, *PackageFileName, SavePackageArgs);

    return NewItemDefinition;
}

void UItemDatabase::UpdateItemDefinition(UItemDefinition* ItemDefinition, int32 ID, FTableRowBase* Row)
{
    OnUpdateItemDefinition(ItemDefinition, ID, Row);
    ItemDefinition->MarkPackageDirty();
    UEditorAssetLibrary::SaveLoadedAsset(ItemDefinition);
}

void UItemDatabase::OnUpdateItemDefinition(UItemDefinition* ItemDefinition, int32 ID, FTableRowBase* Row)
{
}

FString UItemDatabase::GetAssetName(int32 ID) const
{
    return Prefix + FString::FromInt(ID);
}

FString UItemDatabase::GetPackageName(int32 ID) const
{
    return Directory + GetAssetName(ID);;
}
