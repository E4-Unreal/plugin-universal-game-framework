// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FlexibleDataObjectBase.h"
#include "FlexibleDataObject.generated.h"

/**
 *
 */
UCLASS()
class DATAMANAGER_API UFlexibleDataObject : public UFlexibleDataObjectBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Instanced, Replicated)
    TArray<TObjectPtr<UDataObjectFragment>> Fragments;

public:
    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* FlexibleDataBase */

    virtual UDataObjectFragment* GetFragmentByInterface(const TSubclassOf<UInterface> InterfaceClass) const override;
};
