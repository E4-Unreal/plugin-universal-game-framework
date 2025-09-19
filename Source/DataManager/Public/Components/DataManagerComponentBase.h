// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReplicatedComponent.h"
#include "DataManagerComponentBase.generated.h"


UCLASS(Abstract, Blueprintable, meta = (BlueprintSpawnableComponent))
class DATAMANAGER_API UDataManagerComponentBase : public UReplicatedComponent
{
    GENERATED_BODY()

public:
    UDataManagerComponentBase();

    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* API */

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Refresh();
};
