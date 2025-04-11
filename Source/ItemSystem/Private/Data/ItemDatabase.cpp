// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemDatabase.h"

#include "EditorAssetLibrary.h"
#include "Logging.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Data/ItemDefinition.h"
#include "Types/ItemDataTableRow.h"
#include "UObject/SavePackage.h"

void UItemDatabase::HardUpdate()
{
    LOG(Log, TEXT("Hard Update ItemDatabase"))

    DeleteAllItemDefinitions();

    Update();
}

bool UItemDatabase::CheckRowName(FName RowName, int32& ID)
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
    if (ItemDataTable == nullptr || !ItemDataTable->GetRowStruct()->IsChildOf(FItemDataTableRow::StaticStruct())) return;

    TArray<FTableRowBase*> Rows;
    const TArray<FName> RowNames = ItemDataTable->GetRowNames();

    for (const auto& RowName : RowNames)
    {
        /* Check ID */

        int32 ID;
        bool bValid = CheckRowName(RowName, ID);
        if (!bValid) continue;

        /* Create ItemDefinition */

        // ItemDefinition 생성
        UItemDefinition* NewItemDefinition = CreateItemDefinition(ID);

        // ItemDefinition 업데이트 및 저장
        FItemDataTableRow* Row = ItemDataTable->FindRow<FItemDataTableRow>(RowName, "");
        if (NewItemDefinition->Update(ID, Row))
        {
            NewItemDefinition->GetPackage()->FullyLoad();
            UEditorAssetLibrary::SaveLoadedAsset(NewItemDefinition);
        }

        // ItemDefinition 유효성 검사
        if (NewItemDefinition->IsNotValid())
        {
            UEditorAssetLibrary::DeleteLoadedAsset(NewItemDefinition);
        }
        else
        {
            ItemDefinitionMap.Emplace(ID, NewItemDefinition);
        }
    }

    GetPackage()->FullyLoad();
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

FString UItemDatabase::GetAssetName(int32 ID) const
{
    return Prefix + FString::FromInt(ID);
}

FString UItemDatabase::GetPackageName(int32 ID) const
{
    return Directory + GetAssetName(ID);;
}
