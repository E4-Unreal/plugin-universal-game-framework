// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MeshDataInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UMeshDataInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 *
 */
class MESHMANAGER_API IMeshDataInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TSoftObjectPtr<UStaticMesh> GetStaticMesh() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TSoftObjectPtr<USkeletalMesh> GetSkeletalMesh() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TSoftObjectPtr<UMaterialInterface> GetMaterial() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    TSoftClassPtr<UAnimInstance> GetAnimationClass() const;
};
