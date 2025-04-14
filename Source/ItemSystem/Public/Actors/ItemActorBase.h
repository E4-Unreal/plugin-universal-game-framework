// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/ItemContainer.h"
#include "ItemActorBase.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class ITEMSYSTEM_API AItemActorBase : public AActor
{
    GENERATED_BODY()

protected:
    static FName DisplayMeshName;
    static FName OverlapSphereName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UStaticMeshComponent> DisplayMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USphereComponent> OverlapSphere;

protected:
    UPROPERTY(EditAnywhere, Category = "Config")
    TObjectPtr<UStaticMesh> DefaultStaticMesh;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    FItemContainer ItemContainer;

public:
    AItemActorBase(const FObjectInitializer& ObjectInitializer);

    virtual void PostInitializeComponents() override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable)
    virtual void Refresh();

    UFUNCTION()
    virtual void OnOverlapSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    virtual void OnOverlapSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
    FORCEINLINE UStaticMeshComponent* GetDisplayMesh() const { return DisplayMesh; }
    FORCEINLINE USphereComponent* GetOverlapSphere() const { return OverlapSphere; }
};
