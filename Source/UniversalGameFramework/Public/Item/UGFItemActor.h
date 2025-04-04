// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UGFItemActorInterface.h"
#include "GameFramework/Actor.h"
#include "Types/UGFItem.h"
#include "UGFItemActor.generated.h"

class USphereComponent;

UCLASS(Abstract)
class UNIVERSALGAMEFRAMEWORK_API AUGFItemActor : public AActor, public IUGFItemActorInterface
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USphereComponent> OverlapSphere;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UStaticMeshComponent> DisplayMesh;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<FUGFItem> Items;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bAutoPickup = true;

public:
    AUGFItemActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    UFUNCTION(BlueprintPure)
    FORCEINLINE USphereComponent* GetOverlapSphere() const { return OverlapSphere; }

    /* UGFPickupItem */

    virtual void SetItem_Implementation(const FUGFItem& InItem) override;
    virtual void SetItems_Implementation(const TArray<FUGFItem>& InItems) override;

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    virtual void OnOverlapSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
