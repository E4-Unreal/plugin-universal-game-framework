// Fill out your copyright notice in the Description page of Project Settings.


#include "DefinitionGenerator.h"

#include "EditorAssetLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Data/DefinitionBase.h"
#include "Subsystems/DynamicDataSubsystem.h"
#include "UObject/SavePackage.h"

void UDefinitionGenerator::Update()
{
    if (!DefinitionClass || !DataTable) return;

    // ID 추출
    const TArray<FName> RowNames = DataTable->GetRowNames();
    TArray<int32> IDList;
    IDList.Reserve(RowNames.Num());
    for (const auto& RowName : RowNames)
    {
        FString RowString = RowName.ToString();
        if (RowString.IsNumeric())
        {
            int32 ID = FCString::Atoi(*RowString);
            if (ID >= 0)
            {
                IDList.Emplace(ID);
            }
        }
    }

    // 업데이트
    for (int32 ID : IDList)
    {
        UDefinitionBase* Definition = GetOrCreateDefinition(ID);
        UpdateDefinition(Definition, DataTable->FindRow<FTableRowBase>(FName(FString::FromInt(ID)), ""));
    }
}

UDefinitionBase* UDefinitionGenerator::GetOrCreateDefinition(int32 ID) const
{
    if (auto DataSubsystem = GEngine->GetEngineSubsystem<UDynamicDataSubsystem>())
    {
        if (UDefinitionBase* Definition = DataSubsystem->GetDefinition(DefinitionClass, ID))
        {
            return Definition;
        }
    }

    // 패키지 생성
    FString AssetName = GetPrefix() + FString::FromInt(ID);
    FString PackageName = GetPath() + AssetName;

    UPackage* Package = CreatePackage(*PackageName);
    Package->FullyLoad();

    // 에셋 생성
    UDefinitionBase* Definition = NewObject<UDefinitionBase>(Package, DefinitionClass, *AssetName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
    Definition->SetID(ID);

    Package->MarkPackageDirty();
    FAssetRegistryModule::AssetCreated(Definition);

    // 패키지 저장
    FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());

    FSavePackageArgs SavePackageArgs;
    SavePackageArgs.TopLevelFlags = RF_Public | RF_Standalone;
    SavePackageArgs.bForceByteSwapping = true;
    SavePackageArgs.SaveFlags = SAVE_NoError;

    UPackage::SavePackage(Package, Definition, *PackageFileName, SavePackageArgs);

    return Definition;
}

void UDefinitionGenerator::UpdateDefinition(UDefinitionBase* Definition, FTableRowBase* Row)
{
    OnUpdateDefinition(Definition, Row);

    UEditorAssetLibrary::SaveAsset(Definition->GetPathName());
}

FString UDefinitionGenerator::GetPath() const
{
    FString SubDirectory = DefinitionClass ? DefinitionClass->GetName() : "Default";
    return Path + SubDirectory + "/";
}

FString UDefinitionGenerator::GetPrefix() const
{
    FString SubPrefix = DefinitionClass ? DefinitionClass->GetName() : "Default";
    return Prefix + SubPrefix + "_";
}
