// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/CommonButtonStyleAssetAction.h"

#include "CommonButtonBase.h"

UCommonButtonStyleAssetAction::UCommonButtonStyleAssetAction()
{
    SupportedClasses.Emplace(UCommonButtonStyle::StaticClass());

    HalfHeightRadiusName = "HHR";

    RadiusMap.Emplace("R0", FVector4::Zero());
    RadiusMap.Emplace("R1", FVector4(10, 10, 10, 10));
    RadiusMap.Emplace("R2", FVector4(15, 15, 15, 15));
    RadiusMap.Emplace("R3", FVector4(20, 20, 20, 20));
}


bool UCommonButtonStyleAssetAction::SetHalfHeightRadius(FSlateBrush& SlateBrush)
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

bool UCommonButtonStyleAssetAction::SetRadius(FSlateBrush& SlateBrush, const FVector4& Radius)
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
