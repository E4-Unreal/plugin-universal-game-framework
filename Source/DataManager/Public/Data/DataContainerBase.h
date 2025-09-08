// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReplicatedObject.h"
#include "Interfaces/DataContainerInterface.h"
#include "DataContainerBase.generated.h"

class UDataDefinitionBase;

/**
 *
 */
UCLASS(Abstract)
class DATAMANAGER_API UDataContainerBase : public UReplicatedObject, public IDataContainerInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, Replicated)
    TObjectPtr<UDataAsset> Data;

public:
    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* API */

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    bool IsValid() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    UDataAsset* GetData() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetData(UDataAsset* NewData);
};
