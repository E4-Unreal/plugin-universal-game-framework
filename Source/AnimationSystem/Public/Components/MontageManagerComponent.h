// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "MontageManagerComponent.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class ANIMATIONSYSTEM_API UMontageManagerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TMap<FGameplayTag, TObjectPtr<UAnimMontage>> MontageMap;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TWeakObjectPtr<USkeletalMeshComponent> Mesh;

public:
    UMontageManagerComponent(const FObjectInitializer& ObjectInitializer);

    virtual void InitializeComponent() override;

    /* API */

    UFUNCTION(BlueprintCallable)
    virtual void SetMesh(USkeletalMeshComponent* NewMesh);

    UFUNCTION(BlueprintCallable)
    virtual void PlayMontage(UAnimMontage* Montage);

    UFUNCTION(BlueprintPure)
    virtual UAnimMontage* GetMontageByTag(const FGameplayTag& Tag) const;

    UFUNCTION(BlueprintCallable)
    virtual void PlayMontageByTag(const FGameplayTag& Tag);
};
