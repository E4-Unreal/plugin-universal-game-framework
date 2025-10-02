// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Flexible/DataFragment.h"
#include "Interfaces/MeshDataInterface.h"
#include "MeshDataFragment.generated.h"

/**
 *
 */
UCLASS()
class MESHMANAGER_API UMeshDataFragment : public UDataFragment, public IMeshDataInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UStaticMesh> StaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<USkeletalMesh> SkeletalMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UMaterialInterface> Material;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftClassPtr<UAnimInstance> AnimationClass;

public:
    /* MeshDataInterface */

    virtual TSoftObjectPtr<UStaticMesh> GetStaticMesh_Implementation() const override { return  StaticMesh; }
    virtual TSoftObjectPtr<USkeletalMesh> GetSkeletalMesh_Implementation() const override { return SkeletalMesh; }
    virtual TSoftObjectPtr<UMaterialInterface> GetMaterial_Implementation() const override { return Material; }
    virtual TSoftClassPtr<UAnimInstance> GetAnimationClass_Implementation() const override { return AnimationClass; }
};
