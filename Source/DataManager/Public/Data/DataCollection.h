// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefinitionContainerBase.h"
#include "DataCollection.generated.h"

class UDataDefinitionBase;
class UDataInstanceBase;

/**
 *
 */
UCLASS()
class DATAMANAGER_API UDataCollection : public UDefinitionContainerBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, Replicated)
    TArray<TObjectPtr<UDataInstanceBase>> Instances;

public:
    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* DefinitionContainerBase */

    virtual void SetDefinition_Implementation(UDataDefinitionBase* NewDefinition) override;

    /* API */

    UFUNCTION(BlueprintCallable)
    void SetInstances(const TArray<UDataInstanceBase*>& NewInstances) { Instances = NewInstances; }

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UDataInstanceBase* GetInstanceByInterface(TSubclassOf<UInterface> Interface) const;
};
