// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReplicatedObject.h"
#include "DefinitionContainerBase.generated.h"

class UDataDefinitionBase;

/**
 *
 */
UCLASS(Abstract)
class DATAMANAGER_API UDefinitionContainerBase : public UReplicatedObject
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, Replicated)
    TObjectPtr<UDataDefinitionBase> Definition;

public:
    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* API */

    UFUNCTION(BlueprintPure)
    bool IsValid() const { return Definition != nullptr; }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UDataDefinitionBase* GetDefinition() const { return Definition; }

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetDefinition(UDataDefinitionBase* NewDefinition);
};
