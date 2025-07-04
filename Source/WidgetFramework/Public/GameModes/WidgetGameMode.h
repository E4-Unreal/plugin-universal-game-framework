// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "WidgetGameMode.generated.h"

/**
 * 게임 시작 시 특정 위젯들을 화면에 표시하는 기본 게임 모드 클래스
 */
UCLASS()
class WIDGETFRAMEWORK_API AWidgetGameMode : public AGameMode
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
