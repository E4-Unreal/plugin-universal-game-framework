// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/CommonStyleAssetActionBase.h"

#include "AssetSelection.h"
#include "CommonBorder.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "EditorAssetLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Kismet2/KismetEditorUtilities.h"

UCommonStyleAssetActionBase::UCommonStyleAssetActionBase()
{
    bIsActionForBlueprints = true;

    FolderName = "Instances";
    StringToReplace.Emplace("Base", "");
}

void UCommonStyleAssetActionBase::GenerateInstances()
{
    TArray<FAssetData> SelectedAssets;
    AssetSelectionUtils::GetSelectedAssets(SelectedAssets);
    for (const auto& SelectedAsset : SelectedAssets)
    {
        OnGenerateInstance(SelectedAsset);
    }
}

bool UCommonStyleAssetActionBase::IsChildOfStyle(UClass* Class)
{
    if (Class == nullptr) return false;

    return Class->IsChildOf(UCommonBorderStyle::StaticClass()) || Class->IsChildOf(UCommonTextStyle::StaticClass()) || Class->IsChildOf(UCommonButtonStyle::StaticClass());
}

void UCommonStyleAssetActionBase::OnGenerateInstance(const FAssetData& SelectedAsset)
{

}

FString UCommonStyleAssetActionBase::GetNewAssetName(const FAssetData& SelectedAsset) const
{
    FString NewAssetName = SelectedAsset.AssetName.ToString();

    for (const auto& [SourceString, DestinationString] : StringToReplace)
    {
        NewAssetName = NewAssetName.Replace(*SourceString, *DestinationString);
    }

    return NewAssetName;
}

FString UCommonStyleAssetActionBase::GetNewAssetPath(const FAssetData& SelectedAsset) const
{
    return FolderName.IsEmpty() ? SelectedAsset.PackagePath.ToString() : SelectedAsset.PackagePath.ToString() + "/" + FolderName;
}

UObject* UCommonStyleAssetActionBase::GetOrCreateStyleInstance(const FAssetData& SelectedAsset, FString Suffix)
{
    const FString NewAssetPath = GetNewAssetPath(SelectedAsset);
    const FString NewAssetName = GetNewAssetName(SelectedAsset) + "_" + Suffix;
    const FString NewPackageName = NewAssetPath + "/" + NewAssetName;

    return UEditorAssetLibrary::DoesAssetExist(NewPackageName) ? GetStyleInstance(NewPackageName) : CreateStyleInstance(SelectedAsset.PackageName.ToString(), NewAssetPath, NewAssetName);
}

UObject* UCommonStyleAssetActionBase::GetStyleInstance(FString NewPackageName) const
{
    UClass* InstanceClass = UEditorAssetLibrary::LoadBlueprintClass(NewPackageName);

    return IsChildOfStyle(InstanceClass) ? InstanceClass->GetDefaultObject() : nullptr;
}

UObject* UCommonStyleAssetActionBase::CreateStyleInstance(FString AssetPackageName, FString NewAssetPath, FString NewAssetName)
{
    UClass* ParentClass = UEditorAssetLibrary::LoadBlueprintClass(AssetPackageName);
    UObject* StyleInstance = nullptr;

    if (IsChildOfStyle(ParentClass))
    {
        FString NewPackageName = NewAssetPath + "/" + NewAssetName;
        UPackage* NewPackage = CreatePackage(*NewPackageName);
        UBlueprint* NewBlueprint = FKismetEditorUtilities::CreateBlueprint(ParentClass, NewPackage, *NewAssetName, BPTYPE_Normal, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass());
        UClass* ChildClass = UEditorAssetLibrary::LoadBlueprintClass(NewBlueprint->GetPathName());

        FAssetRegistryModule::AssetCreated(NewBlueprint);
        NewPackage->MarkPackageDirty();

        StyleInstance = ChildClass->GetDefaultObject();
    }

    return StyleInstance;
}
