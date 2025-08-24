// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/EquipmentActorInterface.h"
#include "EquipmentActor.generated.h"

class IEquipmentDataInterface;

UCLASS()
class EQUIPMENTMANAGER_API AEquipmentActor : public AActor, public IEquipmentActorInterface
{
    GENERATED_BODY()

protected:
    const static FName DefaultSceneName;
    const static FName StaticMeshName;
    const static FName SkeletalMeshName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USceneComponent> DefaultScene;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UStaticMeshComponent> StaticMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TScriptInterface<IEquipmentDataInterface> EquipmentData;

public:
    AEquipmentActor(const FObjectInitializer& ObjectInitializer);

    virtual void PostInitializeComponents() override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

    /* EquipmentInterface */

    virtual TScriptInterface<IEquipmentDataInterface> GetEquipmentData_Implementation() const override { return EquipmentData; }
    virtual void SetEquipmentData_Implementation(const TScriptInterface<IEquipmentDataInterface>& NewEquipmentData) override;
    virtual void Equip_Implementation(AActor* NewOwner) override;
    virtual void UnEquip_Implementation() override;

protected:
    virtual void InitializeByData();

public:
    FORCEINLINE USceneComponent* GetDefaultScene() const { return DefaultScene; }
    FORCEINLINE UStaticMeshComponent* GetStaticMesh() const { return StaticMesh; }
    FORCEINLINE USkeletalMeshComponent* GetSkeletonMesh() const { return SkeletalMesh; }
};
