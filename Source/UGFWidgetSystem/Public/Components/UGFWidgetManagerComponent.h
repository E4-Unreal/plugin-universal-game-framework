// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UGFWidgetManagerComponent.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class UGFWIDGETSYSTEM_API UUGFWidgetManagerComponent : public UActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient, Category = "State")
    TMap<TSubclassOf<UUserWidget>, TObjectPtr<UUserWidget>> WidgetMap;

public:
    UFUNCTION(BlueprintPure)
    FORCEINLINE UUserWidget* GetOrCreateWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void ShowWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void HideWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void ToggleWidget(TSubclassOf<UUserWidget> WidgetClass);

protected:
    UFUNCTION(BlueprintPure)
    APlayerController* GetPlayerController() const;

    UFUNCTION(BlueprintCallable)
    virtual UUserWidget* RegisterWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void UnRegisterWidget(TSubclassOf<UUserWidget> WidgetClass);
};
