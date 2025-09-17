// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemContainerComponent.h"
#include "ItemComponent.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UItemComponent : public UItemContainerComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UStaticMesh> DefaultStaticMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText ItemNameFormat;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Reference", Transient)
    TWeakObjectPtr<UStaticMeshComponent> DisplayMesh;

public:
    UItemComponent(const FObjectInitializer& ObjectInitializer);

    /* Object */

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

    /* ActorComponent */

    virtual void InitializeComponent() override;

    /* ItemContainerComponent */

    virtual void SetItems(const TArray<UObject*>& NewItemInstances) override;

    /* API */

    UFUNCTION(BlueprintPure)
    virtual FText GetItemName() const;

    UFUNCTION(BlueprintPure)
    virtual UStaticMesh* GetStaticMesh() const;

    UFUNCTION(BlueprintCallable)
    virtual void SetDisplayMesh(UStaticMeshComponent* NewDisplayMesh);

    UFUNCTION(BlueprintCallable)
    virtual void Refresh();

protected:
    /* API */

    virtual void FindDisplayMesh();
};
