// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/CommonButtonStyleAssetAction.h"

#include "AssetSelection.h"
#include "CommonButtonBase.h"

UCommonButtonStyleAssetAction::UCommonButtonStyleAssetAction()
{
    SupportedClasses.Emplace(UCommonButtonStyle::StaticClass());

    HalfHeightRadiusName = "HHR";

    RadiusMap.Emplace("R0", FVector4::Zero());
    RadiusMap.Emplace("R1", FVector4(10, 10, 10, 10));
    RadiusMap.Emplace("R2", FVector4(15, 15, 15, 15));
    RadiusMap.Emplace("R3", FVector4(20, 20, 20, 20));

    HoveredValueOffset = 0.2f;
    PressedValueOffset = -0.2f;
}

void UCommonButtonStyleAssetAction::CopyBrushToHoveredAndPressed()
{
    TArray<FAssetData> SelectedAssets;
    AssetSelectionUtils::GetSelectedAssets(SelectedAssets);
    for (const auto& SelectedAsset : SelectedAssets)
    {
        if (UObject* Style = GetStyleObject(SelectedAsset.PackageName.ToString()))
        {
            if (UCommonButtonStyle* ButtonStyle = Cast<UCommonButtonStyle>(Style))
            {
                bool bDirty = false;
                bDirty = SetBrush(ButtonStyle->NormalHovered, ButtonStyle->NormalBase) || bDirty;
                bDirty = SetBrush(ButtonStyle->NormalPressed, ButtonStyle->NormalBase) || bDirty;
                bDirty = SetBrush(ButtonStyle->SelectedHovered, ButtonStyle->SelectedBase) || bDirty;
                bDirty = SetBrush(ButtonStyle->SelectedPressed, ButtonStyle->SelectedBase) || bDirty;

                if (bDirty) ButtonStyle->GetPackage()->MarkPackageDirty();
            }
        }
    }
}

void UCommonButtonStyleAssetAction::UpdateValueForHoveredAndPressed()
{
    TArray<FAssetData> SelectedAssets;
    AssetSelectionUtils::GetSelectedAssets(SelectedAssets);
    for (const auto& SelectedAsset : SelectedAssets)
    {
        if (UObject* Style = GetStyleObject(SelectedAsset.PackageName.ToString()))
        {
            if (UCommonButtonStyle* ButtonStyle = Cast<UCommonButtonStyle>(Style))
            {
                FSlateColor NewNormalHoveredColor = ApplyValueOffset(ButtonStyle->NormalBase.TintColor, HoveredValueOffset);
                FSlateColor NewNormalPressedColor = ApplyValueOffset(ButtonStyle->NormalBase.TintColor, PressedValueOffset);
                FSlateColor NewSelectedHoveredColor = ApplyValueOffset(ButtonStyle->SelectedBase.TintColor, HoveredValueOffset);
                FSlateColor NewSelectedPressedColor = ApplyValueOffset(ButtonStyle->SelectedBase.TintColor, PressedValueOffset);

                bool bDirty = false;
                bDirty = SetSlateColor(ButtonStyle->NormalHovered.TintColor, NewNormalHoveredColor) || bDirty;
                bDirty = SetSlateColor(ButtonStyle->NormalPressed.TintColor, NewNormalPressedColor) || bDirty;
                bDirty = SetSlateColor(ButtonStyle->SelectedHovered.TintColor, NewSelectedHoveredColor) || bDirty;
                bDirty = SetSlateColor(ButtonStyle->SelectedPressed.TintColor, NewSelectedPressedColor) || bDirty;

                if (bDirty) ButtonStyle->GetPackage()->MarkPackageDirty();
            }
        }
    }
}

void UCommonButtonStyleAssetAction::OnGenerateInstance(const FAssetData& SelectedAsset)
{
    UObject* StyleInstance = GetOrCreateStyleInstance(SelectedAsset, HalfHeightRadiusName.ToString());
    if (UCommonButtonStyle* Style = Cast<UCommonButtonStyle>(StyleInstance))
    {
        bool bDirty = false;
        bDirty = SetHalfHeightRadius(Style->NormalBase) || bDirty;
        bDirty = SetHalfHeightRadius(Style->NormalHovered) || bDirty;
        bDirty = SetHalfHeightRadius(Style->NormalPressed) || bDirty;
        bDirty = SetHalfHeightRadius(Style->SelectedBase) || bDirty;
        bDirty = SetHalfHeightRadius(Style->SelectedHovered) || bDirty;
        bDirty = SetHalfHeightRadius(Style->SelectedPressed) || bDirty;
        bDirty = SetHalfHeightRadius(Style->Disabled) || bDirty;

        if (bDirty) Style->GetPackage()->MarkPackageDirty();
    }

    for (const auto& [RadiusName, RadiusSize] : RadiusMap)
    {
        StyleInstance = GetOrCreateStyleInstance(SelectedAsset, RadiusName.ToString());
        if (UCommonButtonStyle* Style = Cast<UCommonButtonStyle>(StyleInstance))
        {
            bool bDirty = false;
            bDirty = SetRadius(Style->NormalBase, RadiusSize) || bDirty;
            bDirty = SetRadius(Style->NormalHovered, RadiusSize) || bDirty;
            bDirty = SetRadius(Style->NormalPressed, RadiusSize) || bDirty;
            bDirty = SetRadius(Style->SelectedBase, RadiusSize) || bDirty;
            bDirty = SetRadius(Style->SelectedHovered, RadiusSize) || bDirty;
            bDirty = SetRadius(Style->SelectedPressed, RadiusSize) || bDirty;
            bDirty = SetRadius(Style->Disabled, RadiusSize) || bDirty;

            if (bDirty) Style->GetPackage()->MarkPackageDirty();
        }
    }
}
