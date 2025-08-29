// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetActions/CommonTextStyleAssetAction.h"

#include "CommonTextBlock.h"

UCommonTextStyleAssetAction::UCommonTextStyleAssetAction()
{
    SupportedClasses.Emplace(UCommonTextStyle::StaticClass());

    FontSizeMap.Emplace("H1", 32.0f);
    FontSizeMap.Emplace("H2", 24.0f);
    FontSizeMap.Emplace("H3", 19.0f);
    FontSizeMap.Emplace("H4", 16.0f);
}

void UCommonTextStyleAssetAction::OnGenerateInstance(const FAssetData& SelectedAsset)
{
    for (const auto& [FontName, FontSize] : FontSizeMap)
    {
        UObject* StyleInstance = GetOrCreateStyleInstance(SelectedAsset, FontName.ToString());
        if (UCommonTextStyle* Style = Cast<UCommonTextStyle>(StyleInstance))
        {
            float NewFontSize = FontSize * 0.75;
            if (Style->Font.Size != NewFontSize)
            {
                Style->Font.Size = NewFontSize;
                StyleInstance->GetPackage()->MarkPackageDirty();
            }
        }
    }
}
