// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataContainerBase.h"
#include "Interfaces/DataInstanceInterface.h"
#include "DataCollection.generated.h"

/**
 *
 */
UCLASS()
class DATAMANAGER_API UDataCollection : public UDataContainerBase, public IDataInstanceInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, Replicated)
    TArray<TObjectPtr<UObject>> Instances;

public:
    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* DataInstanceInterface */

    virtual bool IsValid_Implementation() const override;
    virtual void SetData_Implementation(UDataAsset* NewData) override;
    virtual UDataAsset* GetDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const override;
    virtual UObject* GetInstanceByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const override;

    /* API */

    UFUNCTION(BlueprintCallable)
    static UDataCollection* CreateDataCollectionFromData(UDataAsset* InData);
};
