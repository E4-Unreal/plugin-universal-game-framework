// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WidgetManagerFunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class WIDGETMANAGER_API UWidgetManagerFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    static UUserWidget* CreateWidgetByClass(APlayerController* OwningPlayerController, TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    static TArray<UUserWidget*> CreateWidgetsByClasses(APlayerController* OwningPlayerController, const TArray<TSubclassOf<UUserWidget>>& WidgetClasses);

    UFUNCTION(BlueprintCallable)
    static void DestroyWidget(UUserWidget* Widget);

    UFUNCTION(BlueprintCallable)
    static void DestroyWidgetByClass(TMap<TSubclassOf<UUserWidget>, UUserWidget*>& WidgetMap, TSubclassOf<UUserWidget> WidgetClass);

    static void DestroyWidgetByClass(TMap<TSubclassOf<UUserWidget>, TObjectPtr<UUserWidget>> WidgetMap, TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    static void DestroyWidgets(TArray<UUserWidget*>& Widgets);

    static void DestroyWidgets(TArray<TObjectPtr<UUserWidget>>& Widgets);

    UFUNCTION(BlueprintCallable)
    static void DestroyWidgetsByMap(TMap<TSubclassOf<UUserWidget>, UUserWidget*>& WidgetMap);

    static void DestroyWidgetsByMap(TMap<TSubclassOf<UUserWidget>, TObjectPtr<UUserWidget>>& WidgetMap);

    UFUNCTION(BlueprintCallable)
    static bool ShowWidget(UUserWidget* Widget);

    UFUNCTION(BlueprintCallable)
    static void ShowWidgets(const TArray<UUserWidget*>& Widgets);

    UFUNCTION(BlueprintCallable)
    static bool HideWidget(UUserWidget* Widget);

    UFUNCTION(BlueprintCallable)
    static void HideWidgets(const TArray<UUserWidget*>& Widgets);

    UFUNCTION(BlueprintCallable)
    static void ToggleWidget(UUserWidget* Widget);

    UFUNCTION(BlueprintCallable)
    static void ToggleWidgets(const TArray<UUserWidget*>& Widgets);

    UFUNCTION(BlueprintCallable)
    static void SetPlayerUIMode(APlayerController* PlayerController);

    /* WidgetUtilityInterface */

    UFUNCTION(BlueprintCallable, Category = "WidgetUtilityInterface")
    static void Refresh(UUserWidget* Widget);

    UFUNCTION(BlueprintCallable, Category = "WidgetUtilityInterface")
    static void Clear(UUserWidget* Widget);

    /* EntryWidgetInterface */

    UFUNCTION(BlueprintCallable, Category = "EntryWidgetInterface")
    static void SetDataObject(UUserWidget* Widget, UObject* NewDataObject);
};
