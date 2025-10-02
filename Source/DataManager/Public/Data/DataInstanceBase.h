// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReplicatedObject.h"
#include "DataInstanceBase.generated.h"

class UDataDefinitionBase;
/**
 *
 */
UCLASS(Abstract, EditInlineNew)
class DATAMANAGER_API UDataInstanceBase : public UReplicatedObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Replicated, meta = (DisplayPriority = 0))
    TObjectPtr<UDataDefinitionBase> Definition;

public:
    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* API */

    UFUNCTION(BlueprintPure)
    UDataDefinitionBase* GetDefinition() const { return Definition; }

    UFUNCTION(BlueprintCallable)
    virtual void SetDefinition(UDataDefinitionBase* NewDefinition) { Definition = NewDefinition; }

    UFUNCTION(BlueprintPure)
    virtual UObject* GetDataInstanceByInterface(TSubclassOf<UInterface> InterfaceClass) const;

    template <typename TInterface = UInterface>
    UObject* GetDataInstanceByInterface() const
    {
        return GetDataInstanceByInterface(TInterface::StaticClass());
    }
};
