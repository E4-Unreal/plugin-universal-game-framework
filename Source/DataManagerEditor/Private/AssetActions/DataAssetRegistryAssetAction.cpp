// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/DataAssetRegistryAssetAction.h"

#include "AssetSelection.h"
#include "EditorAssetLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Data/DataAssetRegistry.h"
#include "Interfaces/DataDefinitionInterface.h"
#include "Objects/DataAssetBuilder.h"
#include "UObject/SavePackage.h"

UDataAssetRegistryAssetAction::UDataAssetRegistryAssetAction()
{
    SupportedClasses.Emplace(UDataAssetRegistry::StaticClass());
}

void UDataAssetRegistryAssetAction::Build()
{
    TArray<FAssetData> SelectedAssets;
    AssetSelectionUtils::GetSelectedAssets(SelectedAssets);
    for (const auto& SelectedAsset : SelectedAssets)
    {
        if (UDataAssetRegistry* Registry = Cast<UDataAssetRegistry>(SelectedAsset.GetAsset()))
        {
            BuildData(Registry);
        }
    }
}

void UDataAssetRegistryAssetAction::BuildData(UDataAssetRegistry* DataAssetRegistry) const
{
    if (DataAssetRegistry && DataAssetRegistry->BuilderClass)
    {
        auto BuilderClass = DataAssetRegistry->BuilderClass;
        auto Builder = Cast<UDataAssetBuilder>(BuilderClass->GetDefaultObject());
        DataAssetRegistry->DataClass = Builder->GetDataClass();
        DataAssetRegistry->DataTable = Builder->GetDataTable();

        UDataTable* DataTable = DataAssetRegistry->DataTable.LoadSynchronous();
        TSubclassOf<UDataAsset> DataClass = DataAssetRegistry->DataClass;

        TArray<int32> OldIDList;
        DataAssetRegistry->DataMap.GetKeys(OldIDList);

        const TSet<int32> NewIDSet = GetIDSet(DataTable);
        const TSet<int32> OldIDSet = TSet<int32>(OldIDList);
        const TSet<int32> IDSetToDelete = OldIDSet.Difference(NewIDSet);
        const TSet<int32> IDSetToUpdate = NewIDSet.Intersect(OldIDSet);
        TSet<int32> IDSetToCreate = NewIDSet.Difference(OldIDSet);

        // Delete Old Data
        for (int32 IDToDelete : IDSetToDelete)
        {
            TSoftObjectPtr<UDataAsset> DataToDelete = DataAssetRegistry->DataMap[IDToDelete];
            if (DataToDelete && !DataToDelete.IsNull())
            {
                UEditorAssetLibrary::DeleteAsset(DataToDelete->GetPathName());
            }

            DataAssetRegistry->DataMap.Remove(IDToDelete);
        }

        // Update Old Data

        for (int32 IDToUpdate : IDSetToUpdate)
        {
            UDataAsset* DataToUpdate = DataAssetRegistry->DataMap[IDToUpdate].LoadSynchronous();
            if (DataToUpdate == nullptr) continue;

            if (DataToUpdate->GetClass() == DataClass)
            {
                if (Builder->UpdateData(DataToUpdate))
                {
                    DataToUpdate->MarkPackageDirty();
                }
            }
            else
            {
                UEditorAssetLibrary::DeleteAsset(DataToUpdate->GetPathName());
                DataAssetRegistry->DataMap.Remove(IDToUpdate);
                IDSetToCreate.Emplace(IDToUpdate);
            }
        }

        // Create New Data

        for (int32 IDToCreate : IDSetToCreate)
        {
            if (UDataAsset* NewData = CreateData(DataClass, IDToCreate, DataAssetRegistry->GetPackage()->GetPathName()))
            {
                if (Builder->UpdateData(NewData))
                {
                    NewData->MarkPackageDirty();
                    DataAssetRegistry->DataMap.Emplace(IDToCreate, NewData);
                }
                else
                {
                    UEditorAssetLibrary::DeleteAsset(NewData->GetPathName());
                }
            }
        }
    }
}

TSet<int32> UDataAssetRegistryAssetAction::GetIDSet(UDataTable* DataTable)
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

int32 UDataAssetRegistryAssetAction::ConvertRowNameToID(FName RowName)
{
    FString IDString = RowName.ToString();
    if (IDString.IsNumeric())
    {
        int32 ID = FCString::Atoi(*IDString);

        return ID;
    }

    return -1;
}

UDataAsset* UDataAssetRegistryAssetAction::CreateData(TSubclassOf<UDataAsset> DataClass, int32 ID, FString AssetPath)
{
    if (DataClass == nullptr || !DataClass->ImplementsInterface(UDataDefinitionInterface::StaticClass()) || ID < 0) return nullptr;

    // 패키지 생성
    FString AssetName = "DA_" + DataClass->GetName() + "_" + FString::FromInt(ID);
    FString PackageName = AssetPath + "/" + AssetName;

    UPackage* Package = CreatePackage(*PackageName);
    Package->FullyLoad();

    // 에셋 생성
    UDataAsset* NewData = NewObject<UDataAsset>(Package, DataClass, *AssetName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
    IDataDefinitionInterface::Execute_SetID(NewData, ID);

    Package->MarkPackageDirty();
    FAssetRegistryModule::AssetCreated(NewData);

    // 패키지 저장
    FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());

    FSavePackageArgs SavePackageArgs;
    SavePackageArgs.TopLevelFlags = RF_Public | RF_Standalone;
    SavePackageArgs.bForceByteSwapping = true;
    SavePackageArgs.SaveFlags = SAVE_NoError;

    UPackage::SavePackage(Package, NewData, *PackageFileName, SavePackageArgs);

    return NewData;
}
