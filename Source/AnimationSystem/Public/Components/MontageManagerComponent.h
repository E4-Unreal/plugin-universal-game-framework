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
    // TMap<MontageType, Montage>
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TMap<FGameplayTag, TObjectPtr<UAnimMontage>> MontageMap;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Reference", Transient)
    TWeakObjectPtr<USkeletalMeshComponent> SkeletalMesh;

public:
    UMontageManagerComponent(const FObjectInitializer& ObjectInitializer);

    /* Actor Component */

    virtual void InitializeComponent() override;

    /* API */

    UFUNCTION(BlueprintCallable, Category = "Reference")
    virtual void SetSkeletalMesh(USkeletalMeshComponent* NewSkeletalMesh);

    UFUNCTION(BlueprintPure)
    FORCEINLINE bool HasMontageByTag(const FGameplayTag& Tag) const { return MontageMap.Contains(Tag); }

    UFUNCTION(BlueprintPure)
    FORCEINLINE UAnimMontage* GetMontageByTag(const FGameplayTag& Tag) const { return MontageMap.FindRef(Tag); }

    UFUNCTION(BlueprintCallable)
    virtual bool PlayMontage(UAnimMontage* Montage);

    UFUNCTION(BlueprintCallable)
    virtual bool PlayMontageByTag(const FGameplayTag& Tag);

protected:
    /* API */

    virtual void FindSkeletalMesh();

    UFUNCTION()
    virtual void BindAnimInstanceEvents();

    UFUNCTION()
    virtual void OnPlayMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

    UFUNCTION()
    virtual void OnPlayMontageNotifyEnd(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
};
