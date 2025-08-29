// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/CommonBorderStyleAssetAction.h"

#include "CommonBorder.h"

UCommonBorderStyleAssetAction::UCommonBorderStyleAssetAction()
{
    SupportedClasses.Emplace(UCommonBorderStyle::StaticClass());

    HalfHeightRadiusName = "HHR";

    RadiusMap.Emplace("R0", FVector4::Zero());
    RadiusMap.Emplace("R1", FVector4(10, 10, 10, 10));
    RadiusMap.Emplace("R2", FVector4(15, 15, 15, 15));
    RadiusMap.Emplace("R3", FVector4(20, 20, 20, 20));
}

void UCommonBorderStyleAssetAction::OnGenerateInstance(const FAssetData& SelectedAsset)
{
    UObject* StyleInstance = GetOrCreateStyleInstance(SelectedAsset, HalfHeightRadiusName.ToString());
    if (UCommonBorderStyle* Style = Cast<UCommonBorderStyle>(StyleInstance))
    {
        if (Style->Background.OutlineSettings.RoundingType != ESlateBrushRoundingType::HalfHeightRadius)
        {
            Style->Background.DrawAs = ESlateBrushDrawType::RoundedBox;
            Style->Background.OutlineSettings.RoundingType = ESlateBrushRoundingType::HalfHeightRadius;
            Style->GetPackage()->MarkPackageDirty();
        }
    }

    for (const auto& [RadiusName, RadiusSize] : RadiusMap)
    {
        StyleInstance = GetOrCreateStyleInstance(SelectedAsset, RadiusName.ToString());
        if (UCommonBorderStyle* Style = Cast<UCommonBorderStyle>(StyleInstance))
        {
            if (Style->Background.OutlineSettings.CornerRadii != RadiusSize)
            {
                Style->Background.DrawAs = RadiusSize == FVector4::Zero() ? ESlateBrushDrawType::Box : ESlateBrushDrawType::RoundedBox;
                Style->Background.OutlineSettings.CornerRadii = RadiusSize;
                Style->GetPackage()->MarkPackageDirty();
            }
        }
    }
}
