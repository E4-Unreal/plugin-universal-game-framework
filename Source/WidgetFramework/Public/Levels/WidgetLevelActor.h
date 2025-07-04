// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "WidgetLevelActor.generated.h"

UCLASS()
class WIDGETFRAMEWORK_API AWidgetLevelActor : public ALevelScriptActor
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    TArray<TSubclassOf<UUserWidget>> WidgetClasses;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    bool bVisible;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
    TArray<TObjectPtr<UUserWidget>> Widgets;

protected:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable)
    void CreateWidgets();

    UFUNCTION(BlueprintCallable)
    void RemoveWidgets();

    UFUNCTION(BlueprintCallable)
    void ToggleWidgets();

    UFUNCTION(BlueprintCallable)
    void ShowWidgets();

    UFUNCTION(BlueprintCallable)
    void HideWidgets();
};
