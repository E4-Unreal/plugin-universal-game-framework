// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataManagerComponentBase.h"
#include "Components/ActorComponent.h"
#include "DataManagerComponent.generated.h"


class UDataInstanceBase;
class UDataDefinitionBase;

UCLASS(Abstract)
class DATAMANAGER_API UDataManagerComponent : public UDataManagerComponentBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", ReplicatedUsing = OnRep_Definition)
    TObjectPtr<UDataDefinitionBase> Definition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Instanced, ReplicatedUsing = OnRep_Instance)
    TObjectPtr<UDataInstanceBase> Instance;

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
    virtual UDataDefinitionBase* GetDefinition() const { return Definition; }

    UFUNCTION(BlueprintCallable)
    virtual void SetDefinition(UDataDefinitionBase* NewDefinition);

    UFUNCTION(BlueprintPure)
    virtual UObject* GetDataInstance() const { return Instance; }

    UFUNCTION(BlueprintCallable)
    virtual void SetDataInstance(UDataInstanceBase* NewInstance);

protected:
    /* Replication */

    UFUNCTION()
    virtual void OnRep_Definition(UDataDefinitionBase* OldDefinition);

    UFUNCTION()
    virtual void OnRep_Instance(UDataInstanceBase* OldInstance);
};
