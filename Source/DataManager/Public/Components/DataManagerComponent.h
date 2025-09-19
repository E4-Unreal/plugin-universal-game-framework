// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataManagerComponentBase.h"
#include "Components/ActorComponent.h"
#include "DataManagerComponent.generated.h"


UCLASS(Abstract)
class DATAMANAGER_API UDataManagerComponent : public UDataManagerComponentBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "DataInterface"), ReplicatedUsing = OnRep_Data)
    TObjectPtr<UDataAsset> Data;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "DataInstanceInterface"), Instanced, ReplicatedUsing = OnRep_DataInstance)
    TObjectPtr<UObject> DataInstance;

public:
    UDataManagerComponent();

    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
#if WITH_EDITOR
    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

    /* DataManagerComponentBase */

    virtual void Refresh_Implementation() override;

    /* API */

    UFUNCTION(BlueprintPure)
    virtual UDataAsset* GetData() const;

    UFUNCTION(BlueprintCallable)
    virtual void SetData(UDataAsset* NewData);

    UFUNCTION(BlueprintPure)
    virtual UObject* GetDataInstance() const { return DataInstance; }

    UFUNCTION(BlueprintCallable)
    virtual void SetDataInstance(UObject* NewDataInstance);

protected:
    /* Replication */

    UFUNCTION()
    virtual void OnRep_Data(UDataAsset* OldData);

    UFUNCTION()
    virtual void OnRep_DataInstance(UObject* OldDataInstance);
};
