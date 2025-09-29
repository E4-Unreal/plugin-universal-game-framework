// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MeshManagerFunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class MESHMANAGER_API UMeshManagerFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /* MeshData */

    UFUNCTION(BlueprintPure, Category = "MeshData")
    static UDataAsset* GetMeshData(UObject* DataObject);

    UFUNCTION(BlueprintPure, Category = "MeshData")
    static TSoftObjectPtr<UStaticMesh> GetStaticMesh(UObject* DataObject);

    UFUNCTION(BlueprintPure, Category = "MeshData")
    static TSoftObjectPtr<USkeletalMesh> GetSkeletalMesh(UObject* DataObject);

    UFUNCTION(BlueprintPure, Category = "MeshData")
    static TSoftObjectPtr<UMaterialInterface> GetMaterial(UObject* DataObject);

    UFUNCTION(BlueprintPure, Category = "MeshData")
    static TSoftClassPtr<UAnimInstance> GetAnimationClass(UObject* DataObject);
};
