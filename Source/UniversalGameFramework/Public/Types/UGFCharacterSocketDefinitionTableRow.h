// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Types/DataDefinitionTableRowBase.h"
#include "UGFCharacterSocketDefinitionTableRow.generated.h"

USTRUCT(BlueprintType)
struct UNIVERSALGAMEFRAMEWORK_API FUGFCharacterSocketDefinitionTableRow : public FDataDefinitionTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Socket"))
    FGameplayTag SocketType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SocketName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Socket"))
    FGameplayTagContainer SocketTypesToHide;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UStaticMesh> StaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<USkeletalMesh> SkeletalMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftClassPtr<AActor> ActorClass;
};
