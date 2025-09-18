// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/DataManagerComponentBase.h"
#include "ItemComponentBase.generated.h"


UCLASS(Abstract, meta = (BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UItemComponentBase : public UDataManagerComponentBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, Category = "Reference", Transient)
    TWeakObjectPtr<UStaticMeshComponent> DisplayMesh;

public:
    UItemComponentBase();

    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* DataManagerComponentBase */

    virtual void Refresh_Implementation() override;

    /* API */

    UFUNCTION(BlueprintCallable, Category = "Reference")
    virtual void SetDisplayMesh(UStaticMeshComponent* NewDisplayMesh) { DisplayMesh = NewDisplayMesh; }

    UFUNCTION(BlueprintCallable)
    virtual bool AddItemsToInventory(AActor* TargetActor);

protected:
    /* API */

    virtual void FindDisplayMesh();
    virtual UStaticMesh* GetStaticMesh() const;
    virtual TArray<UObject*> GetItems() const { return TArray<UObject*>(); }
};
