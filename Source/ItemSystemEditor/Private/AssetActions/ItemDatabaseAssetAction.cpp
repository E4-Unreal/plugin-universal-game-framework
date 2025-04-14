// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/ItemDatabaseAssetAction.h"

#include "AssetSelection.h"
#include "EditorAssetLibrary.h"
#include "Data/ItemDatabase.h"
#include "Logging.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "UObject/SavePackage.h"

UItemDatabaseAssetAction::UItemDatabaseAssetAction()
{
    SupportedClasses.Emplace(UItemDatabase::StaticClass());
}

void UItemDatabaseAssetAction::HardUpdate()
{
    TArray<FAssetData> SelectedAssets;
    AssetSelectionUtils::GetSelectedAssets(SelectedAssets);
    for (auto SelectedAsset : SelectedAssets)
    {
        auto ItemDatabase = Cast<UItemDatabase>(SelectedAsset.GetAsset());
        DeleteAllItemDefinitions(ItemDatabase);
        Update(ItemDatabase);
    }
}

void UItemDatabaseAssetAction::SoftUpdate()
{
    TArray<FAssetData> SelectedAssets;
    AssetSelectionUtils::GetSelectedAssets(SelectedAssets);
    for (auto SelectedAsset : SelectedAssets)
    {
        auto ItemDatabase = Cast<UItemDatabase>(SelectedAsset.GetAsset());
        Update(ItemDatabase);
    }
}

void UItemDatabaseAssetAction::Update(UItemDatabase* ItemDatabase)
{
    if (ItemDatabase == nullptr) return;

    if (ItemDatabase->ItemDataTable == nullptr)
    {
        DeleteAllItemDefinitions(ItemDatabase);
        return;
    }

    // ItemDataTable로부터 ItemDefinition 생성 및 업데이트
    const TArray<FName> RowNames = ItemDatabase->ItemDataTable->GetRowNames();
    for (const auto& RowName : RowNames)
    {
        // ID 유효성 검사
        int32 ID;
        if (!CheckRowName(RowName, ID)) continue;

        // Row 가져오기
        FTableRowBase* Row = ItemDatabase->ItemDataTable->FindRow<FTableRowBase>(RowName, "");

        // ItemDefinition 업데이트 및 저장
        UItemDefinition* ItemDefinition = GetOrCreateItemDefinition(ItemDatabase, ID);
        if (ItemDefinition)
        {
            ItemDefinition->Update(ID, Row);
            UEditorAssetLibrary::SaveAsset(ItemDefinition->GetPathName());
        }
    }

    // ItemDatabase 저장
    ItemDatabase->GetPackage()->FullyLoad();
    UEditorAssetLibrary::SaveAsset(ItemDatabase->GetPathName());
}

void UItemDatabaseAssetAction::DeleteAllItemDefinitions(UItemDatabase* ItemDatabase)
{
    if (ItemDatabase == nullptr) return;

    for (auto [ID, ItemDefinition] : ItemDatabase->ItemDefinitionMap)
    {
        UEditorAssetLibrary::DeleteAsset(ItemDefinition->GetPathName());
    }

    ItemDatabase->ItemDefinitionMap.Reset();
}

UItemDefinition* UItemDatabaseAssetAction::GetOrCreateItemDefinition(UItemDatabase* ItemDatabase, int32 ID)
{
    // 유효성 검사
    if (ItemDatabase == nullptr) return nullptr;

    /* Get ItemDefinition */
    UItemDefinition* ItemDefinition = ItemDatabase->GetItemDefinitionByID(ID);
    if (ItemDefinition != nullptr) return ItemDefinition;

    /* Create ItemDefinition */
    if (ItemDatabase->ItemDefinitionClass == nullptr) return nullptr;

    // 패키지 생성
    FString AssetName = GetAssetName(ItemDatabase, ID);
    FString PackageName = GetPackageName(ItemDatabase, ID);

    UPackage* Package = CreatePackage(*PackageName);
    Package->FullyLoad();

    // 에셋 생성
    ItemDefinition = NewObject<UItemDefinition>(Package, ItemDatabase->ItemDefinitionClass, *AssetName, RF_Public | RF_Standalone | RF_MarkAsRootSet);

    Package->MarkPackageDirty();
    FAssetRegistryModule::AssetCreated(ItemDefinition);

    // 패키지 저장
    FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());

    FSavePackageArgs SavePackageArgs;
    SavePackageArgs.TopLevelFlags = RF_Public | RF_Standalone;
    SavePackageArgs.bForceByteSwapping = true;
    SavePackageArgs.SaveFlags = SAVE_NoError;

    UPackage::SavePackage(Package, ItemDefinition, *PackageFileName, SavePackageArgs);

    // ItemDefinitionMap 등록
    ItemDatabase->ItemDefinitionMap.Emplace(ID, ItemDefinition);

    return ItemDefinition;
}

bool UItemDatabaseAssetAction::CheckRowName(FName RowName, int32& ID)
{
    FString IDString = RowName.ToString();
    if (!IDString.IsNumeric())
    {
        LOG(Error, TEXT("ID should be numeric!"))
        return false;
    }

    ID = FCString::Atoi(*IDString);
    if (ID < 0)
    {
        LOG(Error, TEXT("ID should be positive number!"))
        return false;
    }

    return true;
}

FString UItemDatabaseAssetAction::GetAssetName(UItemDatabase* ItemDatabase, int32 ID)
{
    if (ItemDatabase == nullptr) return FString();

    return ItemDatabase->Prefix + FString::FromInt(ID);
}

FString UItemDatabaseAssetAction::GetPackageName(UItemDatabase* ItemDatabase, int32 ID)
{
    if (ItemDatabase == nullptr) return FString();

    return ItemDatabase->Path + GetAssetName(ItemDatabase, ID);
}
