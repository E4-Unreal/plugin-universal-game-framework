// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/WeaponActorInterface.h"
#include "WeaponActor.generated.h"

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
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TScriptInterface<IWeaponDataInterface> WeaponData;

public:
    AWeaponActor(const FObjectInitializer& ObjectInitializer);

    /* Actor */

    virtual void PostInitializeComponents() override;
#if WITH_EDITOR
    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

    /* WeaponActorInterface */

    virtual TScriptInterface<IWeaponDataInterface> GetWeaponData_Implementation() const override { return WeaponData; }
    virtual void SetWeaponData_Implementation(const TScriptInterface<IWeaponDataInterface>& NewWeaponData) override
    {
        WeaponData = NewWeaponData;
        ApplyWeaponData();
    }

    /* Getter */

    FORCEINLINE USceneComponent* GetRootScene() const { return RootScene; }
    FORCEINLINE USkeletalMeshComponent* GetSkeletalMesh() const { return SkeletalMesh; }
    FORCEINLINE UStaticMeshComponent* GetStaticMesh() const { return StaticMesh; }

protected:
    /* API */

    virtual void ApplyWeaponData();
};
