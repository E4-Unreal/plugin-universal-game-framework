// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/DataAssetBuilderAssetAction.h"

#include "AssetSelection.h"
#include "EditorAssetLibrary.h"
#include "ObjectTools.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Interfaces/DataInterface.h"
#include "Data/DataAssetBuilder.h"
#include "Evaluation/EventTriggerControlPlaybackCapability.h"
#include "Subsystems/DataManagerSubsystem.h"
#include "UObject/SavePackage.h"

UDataAssetBuilderAssetAction::UDataAssetBuilderAssetAction()
{
    bIsActionForBlueprints = true;
    SupportedClasses.Emplace(UDataAssetBuilder::StaticClass());
}

void UDataAssetBuilderAssetAction::Build()
{
    TArray<FAssetData> SelectedAssets;
    AssetSelectionUtils::GetSelectedAssets(SelectedAssets);
    for (const auto& SelectedAsset : SelectedAssets)
    {
        if (UClass* BuilderClass = UEditorAssetLibrary::LoadBlueprintClass(SelectedAsset.PackageName.ToString()))
        {
            BuildData(BuilderClass->GetDefaultObject<UDataAssetBuilder>());
        }
    }
}

void UDataAssetBuilderAssetAction::BuildData(UDataAssetBuilder* Builder) const
{
    // 유효성 검사

    if (Builder == nullptr) return;

    TSubclassOf<UDataAsset> DataClass = Builder->GetDataClass();
    UDataTable* DataTable = Builder->GetDataTable();

    if (DataClass == nullptr || DataTable == nullptr) return;

    // 이미 생성된 데이터 에셋 가져오기

    const FName AssetType = DataClass->GetDefaultObject<UDataAsset>()->GetPrimaryAssetId().PrimaryAssetType;
    TMap<int32, UDataAsset*> OldDataAssetMap = GEngine->GetEngineSubsystem<UDataManagerSubsystem>()->GetDataAssetMap(AssetType);
    TArray<int32> OldIDList;
    OldDataAssetMap.GetKeys(OldIDList);

    // 삭제, 업데이트, 생성할 데이터 에셋 분류

    const TSet<int32> NewIDSet = GetIDSet(DataTable);
    const TSet<int32> OldIDSet = TSet<int32>(OldIDList);
    const TSet<int32> IDSetToDelete = OldIDSet.Difference(NewIDSet);
    const TSet<int32> IDSetToUpdate = NewIDSet.Intersect(OldIDSet);
    TSet<int32> IDSetToCreate = NewIDSet.Difference(OldIDSet);

    // 불필요한 데이터 에셋 삭제

    for (int32 IDToDelete : IDSetToDelete)
    {
        UDataAsset* DataToDelete = OldDataAssetMap[IDToDelete];
        if (DataToDelete)
        {
            DeleteDataAsset(DataToDelete);
        }
    }

    // 기존 데이터 에셋 업데이트

    for (int32 IDToUpdate : IDSetToUpdate)
    {
        if (UDataAsset* DataToUpdate = OldDataAssetMap[IDToUpdate])
        {
            // 데이터 에셋 클래스 변경
            if (DataToUpdate->GetClass() != DataClass)
            {
                DataToUpdate = ChangeDataAssetClass(DataToUpdate, DataClass);
            }

            // 업데이트
            if (Builder->UpdateData(DataToUpdate, GetTableRow(DataTable, IDToUpdate)))
            {
                DataToUpdate->MarkPackageDirty();
            }
            UpdatePackageName(DataToUpdate, Builder);
        }
    }

    // 새로운 데이터 에셋 생성

    for (int32 IDToCreate : IDSetToCreate)
    {
        if (UDataAsset* NewData = CreateData(Builder, IDToCreate))
        {
            if (Builder->UpdateData(NewData, GetTableRow(DataTable, IDToCreate)))
            {
                UpdatePackageName(NewData, Builder);
                NewData->MarkPackageDirty();
            }
            else
            {
                DeleteDataAsset(NewData);
            }
        }
    }
}

TSet<int32> UDataAssetBuilderAssetAction::GetIDSet(UDataTable* DataTable)
{
    TSet<int32> IDSet;
    if (DataTable)
    {
        const TArray<FName> RowNames = DataTable->GetRowNames();
        IDSet.Reserve(RowNames.Num());
        for (const auto& RowName : RowNames)
        {
            int32 ID = ConvertRowNameToID(RowName);
            if (ID < 0) continue;

            IDSet.Emplace(ID);
        }
    }

    return IDSet;
}

int32 UDataAssetBuilderAssetAction::ConvertRowNameToID(FName RowName)
{
    FString IDString = RowName.ToString();
    if (IDString.IsNumeric())
    {
        int32 ID = FCString::Atoi(*IDString);

        return ID;
    }

    return -1;
}

UDataAsset* UDataAssetBuilderAssetAction::CreateData(UDataAssetBuilder* Builder, int32 ID)
{
    // 유효성 검사

    if (Builder == nullptr || ID < 0) return nullptr;

    TSubclassOf<UDataAsset> DataClass = Builder->GetDataClass();
    if (DataClass == nullptr || !DataClass->ImplementsInterface(UDataInterface::StaticClass())) return nullptr;

    const FString Prefix = Builder->GetPrefix().ToString();
    const FString DataName = Builder->GetDataName().ToString();
    const FString AssetPath = FPackageName::GetLongPackagePath(Builder->GetPackage()->GetPathName()) + "/" + DataName;

    // 패키지 생성
    FString AssetName = Prefix + "_" + DataName + "_" + FString::FromInt(ID);
    FString PackageName = AssetPath + "/" + AssetName;

    UPackage* Package = CreatePackage(*PackageName);
    Package->FullyLoad();

    // 에셋 생성
    UDataAsset* NewData = NewObject<UDataAsset>(Package, DataClass, *AssetName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
    IDataInterface::Execute_SetID(NewData, ID);

    Package->MarkPackageDirty();
    FAssetRegistryModule::AssetCreated(NewData);

    return NewData;
}

FTableRowBase* UDataAssetBuilderAssetAction::GetTableRow(UDataTable* DataTable, int32 ID)
{
    if (DataTable && ID >= 0)
    {
        return DataTable->FindRow<FTableRowBase>(FName(FString::FromInt(ID)), "");
    }

    return nullptr;
}

void UDataAssetBuilderAssetAction::UpdatePackageName(UDataAsset* DataAsset, UDataAssetBuilder* Builder)
{
    if (DataAsset && DataAsset->Implements<UDataInterface>() && Builder)
    {
        // DataAsset

        const FString ID =  FString::FromInt(IDataInterface::Execute_GetID(DataAsset));
        const FString DisplayName = IDataInterface::Execute_GetDisplayName(DataAsset).ToString().Replace(TEXT(" "), TEXT(""));

        // Builder

        const FString Prefix = Builder->GetPrefix().ToString();
        const FString DataName = Builder->GetDataName().ToString();

        // PackageName

        const FString AssetPath = FPackageName::GetLongPackagePath(Builder->GetPackage()->GetPathName()) + "/" + DataName;
        const FString AssetName = Prefix + "_" + DataName + "_" + ID + "_" + DisplayName;
        const FString PackageName = AssetPath + "/" + AssetName;

        // 검사

        if (DataAsset->GetPackage()->GetPathName() != PackageName)
        {
            UEditorAssetLibrary::RenameAsset(DataAsset->GetPackage()->GetPathName(), PackageName);
            FAssetRegistryModule::AssetRenamed(DataAsset, DataAsset->GetPackage()->GetPathName());
            DataAsset->MarkPackageDirty();
        }
    }
}

void UDataAssetBuilderAssetAction::DeleteDataAsset(UDataAsset* DataAsset)
{
    if (DataAsset)
    {
        UEditorAssetLibrary::DeleteAsset(DataAsset->GetPathName());
    }
}

UDataAsset* UDataAssetBuilderAssetAction::ChangeDataAssetClass(UDataAsset* OldDataAsset,
    TSubclassOf<UDataAsset> NewDataAssetClass)
{
    if (OldDataAsset && !OldDataAsset->IsA(NewDataAssetClass))
    {
        FName ObjectName = OldDataAsset->GetFName();
        UObject* Outer = OldDataAsset->GetOuter();
        OldDataAsset->Rename(nullptr, GetTransientPackage(), REN_DoNotDirty | REN_DontCreateRedirectors);

        UDataAsset* NewDataAsset = NewObject<UDataAsset>(Outer, NewDataAssetClass, ObjectName, OldDataAsset->GetFlags());

        NewDataAsset->MarkPackageDirty();

        // 데이터 복사
        UEngine::FCopyPropertiesForUnrelatedObjectsParams CopyOptions;
        CopyOptions.bNotifyObjectReplacement = true;
        UEngine::CopyPropertiesForUnrelatedObjects(OldDataAsset, NewDataAsset, CopyOptions);

        // 리디렉트
        bool bShowDeleteConfirmation = false;
        TArray<UObject*> OldDataAssetArray({ (UObject*)OldDataAsset });
        ObjectTools::ConsolidateObjects(NewDataAsset, OldDataAssetArray, bShowDeleteConfirmation);

        return NewDataAsset;
    }

    return nullptr;
}
