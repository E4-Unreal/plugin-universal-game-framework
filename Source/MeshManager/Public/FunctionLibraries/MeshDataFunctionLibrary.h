// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MeshDataFunctionLibrary.generated.h"

class UDataDefinitionBase;
/**
 *
 */
UCLASS()
class MESHMANAGER_API UMeshDataFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /* MeshData */

    UFUNCTION(BlueprintPure, Category = "MeshData")
    static bool HasMeshData(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure, Category = "MeshData")
    static TSoftObjectPtr<UStaticMesh> GetStaticMesh(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure, Category = "MeshData")
    static TSoftObjectPtr<USkeletalMesh> GetSkeletalMesh(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure, Category = "MeshData")
    static TSoftObjectPtr<UMaterialInterface> GetMaterial(UDataDefinitionBase* Definition);

    UFUNCTION(BlueprintPure, Category = "MeshData")
    static TSoftClassPtr<UAnimInstance> GetAnimationClass(UDataDefinitionBase* Definition);

protected:
    static UDataAsset* GetMeshData(UDataDefinitionBase* Definition);
};
