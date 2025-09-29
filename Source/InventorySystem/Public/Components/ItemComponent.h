// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemComponentBase.h"
#include "ItemComponent.generated.h"

/**
 * 단일 아이템 데이터를 관리하는 컴포넌트
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UItemComponent : public UItemComponentBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (MustImplement = "ItemInstanceInterface"), Instanced, ReplicatedUsing = OnRep_Items)
    TArray<TObjectPtr<UObject>> Items;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UStaticMesh> DefaultItemMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSoftObjectPtr<UStaticMesh> DefaultItemPackageMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FText ItemNameFormat;

public:
    UItemComponent();

    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
#if WITH_EDITOR
    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

    /* ItemComponentBase */

    virtual bool AddItemsToInventory(AActor* TargetActor) override;

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void SetItems(const TArray<UObject*> NewItems);

    UFUNCTION(BlueprintPure)
    FText GetItemName() const;

protected:
    /* ItemComponentBase */

    virtual UStaticMesh* GetStaticMesh() const override;
    virtual UMaterialInterface* GetMaterial() const override;
    virtual TArray<UObject*> GetItems() const override { return Items; }

    /* API */

    virtual void ClearItems();
    virtual UStaticMesh* GetDefaultItemMesh() const;
    virtual UStaticMesh* GetDefaultItemPackageMesh() const;

    /* Replication */

    UFUNCTION()
    virtual void OnRep_Items(TArray<UObject*> OldItems);
};
