// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataContainerBase.h"
#include "DataInstanceContainer.generated.h"

/**
 *
 */
UCLASS()
class DATAMANAGER_API UDataInstanceContainer : public UDataContainerBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, Replicated)
    TArray<TObjectPtr<UObject>> Instances;

public:
    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* DefinitionContainerBase */

    virtual void SetData_Implementation(UDataAsset* NewData) override;

    /* API */

    UFUNCTION(BlueprintCallable)
    void SetInstances(const TArray<UObject*>& NewInstances) { Instances = NewInstances; }

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UObject* GetInstanceByInterface(TSubclassOf<UInterface> Interface) const;
};
