// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlexibleDataInstanceBase.h"
#include "FlexibleDataInstance.generated.h"

/**
 *
 */
UCLASS()
class DATAMANAGER_API UFlexibleDataInstance : public UFlexibleDataInstanceBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Instanced)
    TArray<TObjectPtr<UDataInstanceFragment>> Fragments;

public:
    /* FlexibleDataBase */

    virtual UDataInstanceFragment* GetFragmentByInterface(const TSubclassOf<UInterface> InterfaceClass) const override;
};
