// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UGFCharacter.generated.h"

class UMontageManagerComponent;

UCLASS()
class UNIVERSALGAMEFRAMEWORK_API AUGFCharacter : public ACharacter
{
    GENERATED_BODY()

protected:
    const static FName MontageManagerName;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UMontageManagerComponent> MontageManager;

public:
    AUGFCharacter(const FObjectInitializer& ObjectInitializer);

public:
    FORCEINLINE UMontageManagerComponent* GetMontageManager() const { return MontageManager; }
};
