// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReplicatedObject.h"
#include "DataInstanceBase.generated.h"

/**
 *
 */
UCLASS(Abstract, EditInlineNew)
class DATAMANAGER_API UDataInstanceBase : public UReplicatedObject
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Replicated)
    TObjectPtr<UDataAsset> Data;

public:
    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* API */

    UFUNCTION(BlueprintPure)
    FORCEINLINE UDataAsset* GetData() const { return Data; }

    UFUNCTION(BlueprintCallable)
    virtual void SetData(UDataAsset* NewData) { Data = NewData; }

    UFUNCTION(BlueprintCallable)
    virtual UDataInstanceBase* GetDataInstanceByInterface(TSubclassOf<UInterface> InterfaceClass) const;
};
