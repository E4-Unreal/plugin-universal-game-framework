// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataContainerBase.h"
#include "DataCollection.generated.h"

/**
 *
 */
UCLASS()
class DATAMANAGER_API UDataCollection : public UDataContainerBase
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
    static UDataCollection* CreateDataCollectionFromData(UDataAsset* InData);

    UFUNCTION(BlueprintCallable)
    void SetInstances(const TArray<UObject*>& NewInstances) { Instances = NewInstances; }

    UFUNCTION(BlueprintPure)
    bool HasDataByInterface(TSubclassOf<UInterface> InterfaceClass) const;

    UFUNCTION(BlueprintPure)
    UDataAsset* GetDataByInterface(TSubclassOf<UInterface> InterfaceClass) const;

    UFUNCTION(BlueprintPure)
    bool HasInstanceByInterface(TSubclassOf<UInterface> InterfaceClass) const;

    UFUNCTION(BlueprintPure)
    UObject* GetInstanceByInterface(TSubclassOf<UInterface> InterfaceClass) const;
};
