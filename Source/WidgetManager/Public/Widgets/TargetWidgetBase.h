// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/TargetWidgetInterface.h"
#include "TargetWidgetBase.generated.h"

/**
 * 플레이어가 아닌 다른 액터의 정보를 표시하기 위한 위젯 클래스
 */
UCLASS(Abstract)
class WIDGETMANAGER_API UTargetWidgetBase : public UUserWidget, public ITargetWidgetInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TSubclassOf<UActorComponent> TargetComponentClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Reference", Transient)
    TWeakObjectPtr<UActorComponent> TargetComponent;

public:
    /* UserWidget */

    virtual void NativeOnInitialized() override;

    /* API */

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetTargetActor(AActor* NewTargetActor);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetTargetComponent(UActorComponent* NewTargetComponent);

protected:
    /* API */

    virtual void FindComponent();

    UFUNCTION(BlueprintNativeEvent)
    void BindTargetComponentEvents(UActorComponent* InTargetComponent);

    UFUNCTION(BlueprintNativeEvent)
    void UnbindTargetComponentEvents(UActorComponent* InTargetComponent);

    UFUNCTION(BlueprintNativeEvent)
    void OnTargetComponentChanged(UActorComponent* OldTargetComponent);
};
