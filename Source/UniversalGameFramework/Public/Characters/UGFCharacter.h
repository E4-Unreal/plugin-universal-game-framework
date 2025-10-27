// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UGFCharacter.generated.h"

class USocketManagerComponent;
class UMontageManagerComponent;
class UFootstepManagerComponent;

UCLASS()
class UNIVERSALGAMEFRAMEWORK_API AUGFCharacter : public ACharacter
{
    GENERATED_BODY()

protected:
    const static FName SocketManagerName;
    const static FName MontageManagerName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USocketManagerComponent> SocketManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UMontageManagerComponent> MontageManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UFootstepManagerComponent> FootstepManager;

public:
    AUGFCharacter(const FObjectInitializer& ObjectInitializer);

public:
    FORCEINLINE USocketManagerComponent* GetSocketManager() const { return SocketManager; }
    FORCEINLINE UMontageManagerComponent* GetMontageManager() const { return MontageManager; }
    FORCEINLINE UFootstepManagerComponent* GetFootstepManager() const { return FootstepManager; }
};
