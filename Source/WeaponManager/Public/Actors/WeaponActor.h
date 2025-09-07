// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/WeaponActorInterface.h"
#include "WeaponActor.generated.h"

class IWeaponDataInterface;

UCLASS()
class WEAPONMANAGER_API AWeaponActor : public AActor,
    public IWeaponActorInterface
{
    GENERATED_BODY()

protected:
    const static FName RootSceneName;
    const static FName SkeletalMeshName;
    const static FName StaticMeshName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USceneComponent> RootScene;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UStaticMeshComponent> StaticMesh;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (AllowedClasses = "WeaponDataInterface"))
    TSoftObjectPtr<UDataAsset> Data;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, ReplicatedUsing = OnRep_Instance)
    TObjectPtr<USlotContent> Instance;

public:
    AWeaponActor(const FObjectInitializer& ObjectInitializer);

    /* Object */

    virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

    /* Actor */

    virtual void PostInitializeComponents() override;
#if WITH_EDITOR
    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

    /* WeaponActorInterface */

    virtual USlotContent* GetInstance_Implementation() const override { return Instance; }
    virtual void SetInstance_Implementation(USlotContent* NewInstance) override;

    /* Getter */

    FORCEINLINE USceneComponent* GetRootScene() const { return RootScene; }
    FORCEINLINE USkeletalMeshComponent* GetSkeletalMesh() const { return SkeletalMesh; }
    FORCEINLINE UStaticMeshComponent* GetStaticMesh() const { return StaticMesh; }

protected:
    /* API */

    virtual void ApplyWeaponData();
    virtual void OnInstanceChanged(USlotContent* OldInstance, USlotContent* NewInstance);

    /* Replication */

    UFUNCTION()
    virtual void OnRep_Instance(USlotContent* OldInstance);
};
