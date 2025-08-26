// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TargetWidgetBase.generated.h"

/**
 * 플레이어가 아닌 다른 액터의 정보를 표시하기 위한 위젯 클래스
 */
UCLASS(Abstract)
class WIDGETMANAGER_API UTargetWidgetBase : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UActorComponent> TargetComponentClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", Transient)
    TWeakObjectPtr<AActor> TargetActor;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", Transient)
    TWeakObjectPtr<UActorComponent> TargetComponent;

public:
    UFUNCTION(BlueprintPure)
    AActor* GetTargetActor() const { return TargetActor.Get(); }

    UFUNCTION(BlueprintCallable)
    virtual void SetTargetActor(AActor* NewTargetActor);

    UFUNCTION(BlueprintPure)
    UActorComponent* GetTargetComponent() const { return TargetComponent.Get(); }

    UFUNCTION(BlueprintCallable)
    virtual void SetTargetComponent(UActorComponent* NewTargetComponent);
};
