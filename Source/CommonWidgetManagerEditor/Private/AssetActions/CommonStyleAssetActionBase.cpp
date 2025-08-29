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

bool UCommonStyleAssetActionBase::SetHalfHeightRadius(FSlateBrush& SlateBrush)
{
    bool bDirty = false;

    if (SlateBrush.DrawAs != ESlateBrushDrawType::RoundedBox)
    {
        SlateBrush.DrawAs = ESlateBrushDrawType::RoundedBox;
        bDirty = true;
    }

    if (SlateBrush.OutlineSettings.RoundingType != ESlateBrushRoundingType::HalfHeightRadius)
    {
        SlateBrush.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
        bDirty = true;
    }

    return bDirty;
}

bool UCommonStyleAssetActionBase::SetRadius(FSlateBrush& SlateBrush, const FVector4& Radius)
{
    bool bDirty = false;

    if (SlateBrush.OutlineSettings.CornerRadii != Radius)
    {
        SlateBrush.DrawAs = Radius == FVector4::Zero() ? ESlateBrushDrawType::Box : ESlateBrushDrawType::RoundedBox;
        SlateBrush.OutlineSettings.CornerRadii = Radius;

        bDirty = true;
    }

    if (Radius == FVector4::Zero() && SlateBrush.DrawAs != ESlateBrushDrawType::Box)
    {
        SlateBrush.DrawAs = ESlateBrushDrawType::Box;

        bDirty = true;
    }
    else if (Radius != FVector4::Zero() && SlateBrush.DrawAs != ESlateBrushDrawType::RoundedBox)
    {
        SlateBrush.DrawAs = ESlateBrushDrawType::RoundedBox;

        bDirty = true;
    }

    return bDirty;
}

void UCommonStyleAssetActionBase::ApplyValueOffset(FLinearColor& LinearColor, const float ValueOffset)
{
    LinearColor = LinearColor.LinearRGBToHSV();
    LinearColor.B += ValueOffset;
    LinearColor = LinearColor.HSVToLinearRGB();
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

    return UEditorAssetLibrary::DoesAssetExist(NewPackageName) ? GetStyleObject(NewPackageName) : CreateStyleInstance(SelectedAsset.PackageName.ToString(), NewAssetPath, NewAssetName);
}

UObject* UCommonStyleAssetActionBase::GetStyleObject(FString NewPackageName) const
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
