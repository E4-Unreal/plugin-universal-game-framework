// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemDatabase.h"

#include "EditorAssetLibrary.h"
#include "Logging.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Data/ItemDefinition.h"
#include "Types/ItemDataTableRow.h"
#include "UObject/SavePackage.h"

UItemDefinition* UItemDatabase::GetItemDefinitionByID(int32 ID)
{
    if (ID < 0 || !ItemDefinitionMap.Contains(ID))
    {
        LOG(Error, TEXT("ItemDefinition(ID: %d) is not exist!"), ID)
        return nullptr;
    }

    return ItemDefinitionMap[ID];
}

#if WITH_EDITOR
void UItemDatabase::HardUpdate()
{
    LOG(Log, TEXT("Hard Update ItemDatabase"))

    DeleteAllItemDefinitions();

    Update();
}

void UItemDatabase::Update()
{
    // ItemDataTable 유효성 검사
    if (ItemDataTable == nullptr)
    {
        DeleteAllItemDefinitions();
        return;
    }

    // ItemDataTable로부터 ItemDefinition 생성 및 업데이트
    const TArray<FName> RowNames = ItemDataTable->GetRowNames();
    for (const auto& RowName : RowNames)
    {
        // ID 유효성 검사
        int32 ID;
        if (!CheckRowName(RowName, ID)) continue;

        // ItemDefinition 생성
        CreateItemDefinition(ID);

        // ItemDefinition 업데이트
        UpdateItemDefinition(ID, ItemDataTable->FindRow<FTableRowBase>(RowName, ""));
    }

    // ItemDatabase 저장
    UPackage* Package = GetPackage();
    Package->FullyLoad();
    UEditorAssetLibrary::SaveAsset(Package->GetPathName());
}

void UItemDatabase::CreateItemDefinition(int32 ID)
{
    // 중복 생성 방지
    if (UItemDefinition* OldItemDefinition = GetItemDefinitionByID(ID))
    {
        LOG(Error, TEXT("%s is already exist!"), *OldItemDefinition->GetName());
        return;
    }

    // 패키지 생성
    FString AssetName = GetAssetName(ID);
    FString PackageName = GetPackageName(ID);

    UPackage* Package = CreatePackage(*PackageName);
    Package->FullyLoad();

    // 에셋 생성
    UItemDefinition* NewItemDefinition = NewObject<UItemDefinition>(Package, *AssetName, RF_Public | RF_Standalone | RF_MarkAsRootSet);

    Package->MarkPackageDirty();
    FAssetRegistryModule::AssetCreated(NewItemDefinition);

    // 패키지 저장
    FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());

    FSavePackageArgs SavePackageArgs;
    SavePackageArgs.TopLevelFlags = RF_Public | RF_Standalone;
    SavePackageArgs.bForceByteSwapping = true;
    SavePackageArgs.SaveFlags = SAVE_NoError;

    UPackage::SavePackage(Package, NewItemDefinition, *PackageFileName, SavePackageArgs);

    // ItemDefinitionMap 등록
    ItemDefinitionMap.Emplace(ID, NewItemDefinition);
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

void UItemDatabase::UpdateItemDefinition(int32 ID, FTableRowBase* Row)
{
    if (UItemDefinition* ItemDefinition = GetItemDefinitionByID(ID))
    {
        ItemDefinition->SetData(ID, Row);
        UEditorAssetLibrary::SaveAsset(ItemDefinition->GetPackage()->GetPathName());
    }
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

FString UItemDatabase::GetAssetName(int32 ID) const
{
    return Prefix + FString::FromInt(ID);
}

FString UItemDatabase::GetPackageName(int32 ID) const
{
    return Path + GetAssetName(ID);;
}
#endif
