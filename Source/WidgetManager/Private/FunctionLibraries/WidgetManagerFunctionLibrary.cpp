// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/WidgetManagerFunctionLibrary.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/EntryWidgetInterface.h"
#include "Interfaces/WidgetUtilityInterface.h"

APlayerController* UWidgetManagerFunctionLibrary::GetPlayerControllerFromActor(AActor* Actor)
{
    if (Actor == nullptr) return nullptr;

    APlayerController* PlayerController = nullptr;

    if (Actor->IsA<APlayerController>())
    {
        PlayerController = Cast<APlayerController>(Actor);
    }
    else if (Actor->IsA<APawn>())
    {
        PlayerController = Cast<APlayerController>(Cast<APawn>(Actor)->GetController());
    }
    else if (Actor->IsA<AGameModeBase>() || Actor->IsA<AGameStateBase>())
    {
        if (UWorld* World = Actor->GetWorld())
        {
            PlayerController = World->GetFirstPlayerController();
        }
    }
    else if (Actor->IsA<APlayerState>())
    {
        PlayerController = Cast<APlayerState>(Actor)->GetPlayerController();
    }
    else
    {
        PlayerController = Cast<APlayerController>(Actor->GetInstigatorController());
    }

    return PlayerController;
}

UUserWidget* UWidgetManagerFunctionLibrary::CreateWidgetByClass(APlayerController* OwningPlayerController,
                                                                TSubclassOf<UUserWidget> WidgetClass)
{
    UUserWidget* Widget = nullptr;

    if (OwningPlayerController && WidgetClass)
    {
        Widget = CreateWidget(OwningPlayerController, WidgetClass);
        Widget->AddToViewport();
        HideWidget(Widget);
    }

    return Widget;
}

TArray<UUserWidget*> UWidgetManagerFunctionLibrary::CreateWidgetsByClasses(APlayerController* OwningPlayerController,
    const TArray<TSubclassOf<UUserWidget>>& WidgetClasses)
{
    TArray<UUserWidget*> Widgets;
    Widgets.Reserve(WidgetClasses.Num());

    for (TSubclassOf<UUserWidget> WidgetClass : WidgetClasses)
    {
        if (UUserWidget* Widget = CreateWidgetByClass(OwningPlayerController, WidgetClass))
        {
            Widgets.Emplace(Widget);
        }
    }

    return Widgets;
}

void UWidgetManagerFunctionLibrary::DestroyWidget(UUserWidget* Widget)
{
    if (Widget && Widget->IsInViewport())
    {
        Widget->RemoveFromParent();
    }
}

void UWidgetManagerFunctionLibrary::DestroyWidgetByClass(TMap<TSubclassOf<UUserWidget>, UUserWidget*>& WidgetMap,
    TSubclassOf<UUserWidget> WidgetClass)
{
    if (WidgetClass && WidgetMap.Contains(WidgetClass))
    {
        DestroyWidget(WidgetMap[WidgetClass]);
        WidgetMap.Remove(WidgetClass);
    }
}

void UWidgetManagerFunctionLibrary::DestroyWidgetByClass(
    TMap<TSubclassOf<UUserWidget>, TObjectPtr<UUserWidget>> WidgetMap, TSubclassOf<UUserWidget> WidgetClass)
{
    if (WidgetClass && WidgetMap.Contains(WidgetClass))
    {
        DestroyWidget(WidgetMap[WidgetClass]);
        WidgetMap.Remove(WidgetClass);
    }
}

void UWidgetManagerFunctionLibrary::DestroyWidgets(TArray<UUserWidget*>& Widgets)
{
    for (UUserWidget* Widget : Widgets)
    {
        DestroyWidget(Widget);
    }

    Widgets.Empty();
}

void UWidgetManagerFunctionLibrary::DestroyWidgets(TArray<TObjectPtr<UUserWidget>>& Widgets)
{
    for (UUserWidget* Widget : Widgets)
    {
        DestroyWidget(Widget);
    }

    Widgets.Empty();
}

void UWidgetManagerFunctionLibrary::DestroyWidgetsByMap(TMap<TSubclassOf<UUserWidget>, UUserWidget*>& WidgetMap)
{
    for (const auto& [WidgetClass, Widget] : WidgetMap)
    {
        DestroyWidget(Widget);
    }
    WidgetMap.Empty();
}

void UWidgetManagerFunctionLibrary::DestroyWidgetsByMap(
    TMap<TSubclassOf<UUserWidget>, TObjectPtr<UUserWidget>>& WidgetMap)
{
    for (const auto& [WidgetClass, Widget] : WidgetMap)
    {
        DestroyWidget(Widget);
    }
    WidgetMap.Empty();
}

bool UWidgetManagerFunctionLibrary::ShowWidget(UUserWidget* Widget)
{
    if (Widget && Widget->IsInViewport() && !Widget->IsVisible())
    {
        UUserWidget* DefaultWidget = Widget->GetClass()->GetDefaultObject<UUserWidget>();
        ESlateVisibility DefaultVisibility = DefaultWidget->GetVisibility();
        if (DefaultVisibility != ESlateVisibility::Collapsed && DefaultVisibility != ESlateVisibility::Hidden)
        {
            Widget->SetVisibility(DefaultVisibility);

            return true;
        }
    }

    return false;
}

void UWidgetManagerFunctionLibrary::ShowWidgets(const TArray<UUserWidget*>& Widgets)
{
    for (UUserWidget* Widget : Widgets)
    {
        ShowWidget(Widget);
    }
}

bool UWidgetManagerFunctionLibrary::HideWidget(UUserWidget* Widget)
{
    if (Widget && Widget->IsInViewport() && Widget->IsVisible())
    {
        UUserWidget* DefaultWidget = Widget->GetClass()->GetDefaultObject<UUserWidget>();
        ESlateVisibility DefaultVisibility = DefaultWidget->GetVisibility();
        if (DefaultVisibility != ESlateVisibility::Collapsed && DefaultVisibility != ESlateVisibility::Hidden)
        {
            Widget->SetVisibility(ESlateVisibility::Collapsed);

            return true;
        }
    }

    return false;
}

void UWidgetManagerFunctionLibrary::HideWidgets(const TArray<UUserWidget*>& Widgets)
{
    for (UUserWidget* Widget : Widgets)
    {
        HideWidget(Widget);
    }
}

void UWidgetManagerFunctionLibrary::ToggleWidget(UUserWidget* Widget)
{
    if (!ShowWidget(Widget))
    {
        HideWidget(Widget);
    }
}

void UWidgetManagerFunctionLibrary::ToggleWidgets(const TArray<UUserWidget*>& Widgets)
{
    for (UUserWidget* Widget : Widgets)
    {
        ToggleWidget(Widget);
    }
}

void UWidgetManagerFunctionLibrary::SetPlayerUIMode(APlayerController* PlayerController)
{
    if (PlayerController)
    {
        PlayerController->SetIgnoreMoveInput(true);
        PlayerController->SetIgnoreLookInput(true);

        if (PlayerController->IsLocalController())
        {
            PlayerController->SetShowMouseCursor(true);
        }
    }
}

void UWidgetManagerFunctionLibrary::Refresh(UUserWidget* Widget)
{
    if (Widget && Widget->Implements<UWidgetUtilityInterface>())
    {
        IWidgetUtilityInterface::Execute_Refresh(Widget);
    }
}

void UWidgetManagerFunctionLibrary::Clear(UUserWidget* Widget)
{
    if (Widget && Widget->Implements<UWidgetUtilityInterface>())
    {
        IWidgetUtilityInterface::Execute_Clear(Widget);
    }
}

void UWidgetManagerFunctionLibrary::SetDataObject(UUserWidget* Widget, UObject* NewDataObject)
{
    if (Widget && Widget->Implements<UEntryWidgetInterface>())
    {
        IEntryWidgetInterface::Execute_SetDataObject(Widget, NewDataObject);
    }
}
