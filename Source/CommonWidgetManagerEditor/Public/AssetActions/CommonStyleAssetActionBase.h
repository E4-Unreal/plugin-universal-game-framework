// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "CommonStyleAssetActionBase.generated.h"

/**
 *
 */
UCLASS(Abstract)
class COMMONWIDGETMANAGEREDITOR_API UCommonStyleAssetActionBase : public UAssetActionUtility
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FString FolderName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TMap<FString, FString> StringToReplace;

public:
    UCommonStyleAssetActionBase();

    UFUNCTION(CallInEditor)
    void GenerateInstances();

protected:
    static bool IsChildOfStyle(UClass* Class);
    static bool SetHalfHeightRadius(FSlateBrush& SlateBrush);
    static bool SetRadius(FSlateBrush& SlateBrush, const FVector4& Radius);
    static void ApplyValueOffset(FLinearColor& LinearColor, const float ValueOffset);

    virtual void OnGenerateInstance(const FAssetData& SelectedAsset);

    FString GetNewAssetName(const FAssetData& SelectedAsset) const;
    FString GetNewAssetPath(const FAssetData& SelectedAsset) const;

    UObject* GetOrCreateStyleInstance(const FAssetData& SelectedAsset, FString Suffix);
    UObject* GetStyleObject(FString NewPackageName) const;
    UObject* CreateStyleInstance(FString AssetPackageName, FString NewAssetPath, FString NewAssetName);
};
