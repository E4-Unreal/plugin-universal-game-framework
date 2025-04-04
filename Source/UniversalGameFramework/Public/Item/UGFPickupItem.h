// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/UGFItem.h"
#include "UGFPickupItem.generated.h"

class USphereComponent;

UCLASS(Abstract)
class UNIVERSALGAMEFRAMEWORK_API AUGFPickupItem : public AActor
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
    AUGFPickupItem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    UFUNCTION(BlueprintPure)
    FORCEINLINE USphereComponent* GetOverlapSphere() const { return OverlapSphere; }

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    virtual void OnOverlapSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
