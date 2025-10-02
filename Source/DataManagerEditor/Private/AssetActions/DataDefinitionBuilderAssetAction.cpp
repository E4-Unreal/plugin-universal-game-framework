// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/DataDefinitionBuilderAssetAction.h"

#include "AssetSelection.h"
#include "EditorAssetLibrary.h"
#include "ObjectTools.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Data/DataDefinitionBase.h"
#include "Data/DataDefinitionBuilder.h"
#include "Subsystems/DataManagerSubsystem.h"

UDataDefinitionBuilderAssetAction::UDataDefinitionBuilderAssetAction()
{
    bIsActionForBlueprints = true;
    SupportedClasses.Emplace(UDataDefinitionBuilder::StaticClass());
}

void UDataDefinitionBuilderAssetAction::Build()
{
    TArray<FAssetData> SelectedAssets;
    AssetSelectionUtils::GetSelectedAssets(SelectedAssets);
    for (const auto& SelectedAsset : SelectedAssets)
    {
        if (UClass* BuilderClass = UEditorAssetLibrary::LoadBlueprintClass(SelectedAsset.PackageName.ToString()))
        {
            BuildData(BuilderClass->GetDefaultObject<UDataDefinitionBuilder>());
        }
    }
}

void UDataDefinitionBuilderAssetAction::BuildData(UDataDefinitionBuilder* Builder) const
{
    // 유효성 검사

    if (Builder == nullptr) return;

    auto DefinitionClass = Builder->GetDefinitionClass();

    if (DefinitionClass == nullptr) return;

    // 이미 생성된 데이터 에셋 가져오기

    const FName AssetType = DefinitionClass->GetDefaultObject<UDataAsset>()->GetPrimaryAssetId().PrimaryAssetType;
    auto OldDataAssetMap = GEngine->GetEngineSubsystem<UDataManagerSubsystem>()->GetDataAssetMap<UDataDefinitionBase>(AssetType);
    TArray<int32> OldIDList;
    OldDataAssetMap.GetKeys(OldIDList);

    // 삭제, 업데이트, 생성할 데이터 에셋 분류

    const TSet<int32> NewIDSet = Builder->GetIDSet();
    const TSet<int32> OldIDSet = TSet<int32>(OldIDList);
    const TSet<int32> IDSetToDelete = OldIDSet.Difference(NewIDSet);
    const TSet<int32> IDSetToUpdate = NewIDSet.Intersect(OldIDSet);
    TSet<int32> IDSetToCreate = NewIDSet.Difference(OldIDSet);

    // 불필요한 데이터 에셋 삭제

    for (int32 IDToDelete : IDSetToDelete)
    {
        auto DataToDelete = OldDataAssetMap[IDToDelete];
        if (!DataToDelete.IsNull())
        {
            UEditorAssetLibrary::DeleteAsset(DataToDelete->GetPathName());
        }
    }

    // 기존 데이터 에셋 업데이트

    for (int32 IDToUpdate : IDSetToUpdate)
    {
        if (auto DataToUpdate = OldDataAssetMap[IDToUpdate].LoadSynchronous())
        {
            // 데이터 에셋 클래스 변경
            if (DataToUpdate->GetClass() != DefinitionClass)
            {
                DataToUpdate = ChangeDataAssetClass(DataToUpdate, DefinitionClass);
            }

            // 업데이트
            if (Builder->UpdateData(DataToUpdate, IDToUpdate))
            {
                DataToUpdate->MarkPackageDirty();
            }
            UpdatePackageName(DataToUpdate, Builder, IDToUpdate);
        }
    }

    // 새로운 데이터 에셋 생성

    for (int32 IDToCreate : IDSetToCreate)
    {
        if (auto NewData = CreateData(Builder, IDToCreate))
        {
            Builder->UpdateData(NewData, IDToCreate);
        }
    }
}

UDataDefinitionBase* UDataDefinitionBuilderAssetAction::CreateData(UDataDefinitionBuilder* Builder, int32 ID)
{
    // 유효성 검사

    if (Builder == nullptr || ID < 0) return nullptr;

    auto DefinitionClass = Builder->GetDefinitionClass();
    if (DefinitionClass == nullptr || !DefinitionClass->ImplementsInterface(UDataInterface::StaticClass())) return nullptr;

    // 패키지 생성
    const FString AssetPath = Builder->GetAssetPath();
    FString AssetName = Builder->GetAssetName(ID);
    FString PackageName = AssetPath + "/" + AssetName;

    UPackage* Package = CreatePackage(*PackageName);
    Package->FullyLoad();

    // 에셋 생성
    auto NewData = NewObject<UDataDefinitionBase>(Package, DefinitionClass, *AssetName, RF_Public | RF_Standalone | RF_MarkAsRootSet);

    Package->MarkPackageDirty();
    FAssetRegistryModule::AssetCreated(NewData);

    return NewData;
}

void UDataDefinitionBuilderAssetAction::UpdatePackageName(UDataDefinitionBase* Definition, UDataDefinitionBuilder* Builder, int32 ID)
{
    if (Definition && Definition->Implements<UDataInterface>() && Builder)
    {
        // Builder

        const FString DataName = Builder->GetDataName();

        // PackageName

        const FString AssetPath = FPackageName::GetLongPackagePath(Builder->GetPackage()->GetPathName()) + "/" + DataName;
        const FString AssetName = Builder->GetAssetName(ID);
        const FString PackageName = AssetPath + "/" + AssetName;

        // 검사

        if (Definition->GetPackage()->GetPathName() != PackageName)
        {
            UEditorAssetLibrary::RenameAsset(Definition->GetPackage()->GetPathName(), PackageName);
            FAssetRegistryModule::AssetRenamed(Definition, Definition->GetPackage()->GetPathName());
            Definition->MarkPackageDirty();
        }
    }
}

UDataDefinitionBase* UDataDefinitionBuilderAssetAction::ChangeDataAssetClass(UDataDefinitionBase* OldDefinition,
    TSubclassOf<UDataDefinitionBase> NewDefinitionClass)
{
    if (OldDefinition && !OldDefinition->IsA(NewDefinitionClass))
    {
        FName ObjectName = OldDefinition->GetFName();
        UObject* Outer = OldDefinition->GetOuter();
        OldDefinition->Rename(nullptr, GetTransientPackage(), REN_DoNotDirty | REN_DontCreateRedirectors);

        auto NewDataAsset = NewObject<UDataDefinitionBase>(Outer, NewDefinitionClass, ObjectName, OldDefinition->GetFlags());

        NewDataAsset->MarkPackageDirty();

        // 데이터 복사
        UEngine::FCopyPropertiesForUnrelatedObjectsParams CopyOptions;
        CopyOptions.bNotifyObjectReplacement = true;
        UEngine::CopyPropertiesForUnrelatedObjects(OldDefinition, NewDataAsset, CopyOptions);

        // 리디렉트
        bool bShowDeleteConfirmation = false;
        TArray<UObject*> OldDataAssetArray({ (UObject*)OldDefinition });
        ObjectTools::ConsolidateObjects(NewDataAsset, OldDataAssetArray, bShowDeleteConfirmation);

        return NewDataAsset;
    }

    return nullptr;
}
