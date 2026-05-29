// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/WidgetManagerSubsystem.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Overlay.h"
#include "FunctionLibraries/WidgetManagerFunctionLibrary.h"
#include "GameplayTags/WidgetManagerGameplayTags.h"
#include "Interfaces/AlertWidgetInterface.h"
#include "Interfaces/ConfirmWidgetInterface.h"
#include "Interfaces/PromptWidgetInterface.h"
#include "Objects/WidgetStack.h"
#include "Settings/WidgetManagerSettings.h"
#include "Widgets/AdvancedActivatableWidget.h"

UWidgetManagerSubsystem* UWidgetManagerSubsystem::Get(UObject* ContextObject)
{
    if (ContextObject == nullptr) return nullptr;

    const ULocalPlayer* LocalPlayer = nullptr;

    if (ContextObject->IsA<UUserWidget>())
    {
        LocalPlayer = Cast<UUserWidget>(ContextObject)->GetOwningLocalPlayer();
    }
    else if (ContextObject->IsA<AActor>())
    {
        if (APlayerController* PlayerController = UWidgetManagerFunctionLibrary::GetPlayerControllerFromActor(Cast<AActor>(ContextObject)))
        {
            LocalPlayer = PlayerController->GetLocalPlayer();
        }
    }
    else if (ContextObject->IsA<UActorComponent>())
    {
        AActor* Actor = Cast<UActorComponent>(ContextObject)->GetOwner();
        if (APlayerController* PlayerController = UWidgetManagerFunctionLibrary::GetPlayerControllerFromActor(Actor))
        {
            LocalPlayer = PlayerController->GetLocalPlayer();
        }
    }
    else if (ContextObject->IsA<ULocalPlayer>())
    {
        LocalPlayer = Cast<ULocalPlayer>(ContextObject);
    }

    return LocalPlayer ? LocalPlayer->GetSubsystem<ThisClass>() : nullptr;
}

bool UWidgetManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    TArray<UClass*> ChildClasses;
    GetDerivedClasses(GetClass(), ChildClasses, false);

    return ChildClasses.Num() == 0;
}

void UWidgetManagerSubsystem::PlayerControllerChanged(APlayerController* NewPlayerController)
{
    Super::PlayerControllerChanged(NewPlayerController);

    DestroyLayoutWidget();
    CreateLayoutWidget(NewPlayerController);
}

FGameplayTag UWidgetManagerSubsystem::GetLayerTag(TSubclassOf<UUserWidget> WidgetClass) const
{
    if (WidgetClass == nullptr) return FGameplayTag();

    if (WidgetClass->IsChildOf<UAdvancedActivatableWidget>())
    {
        FGameplayTag LayerTag = WidgetClass->GetDefaultObject<UAdvancedActivatableWidget>()->GetLayerTag();

        return LayerMap.Contains(LayerTag) ? LayerTag : WidgetManager::UI::Layer::Default;
    }

    return WidgetManager::UI::Layer::Default;
}

UWidgetStack* UWidgetManagerSubsystem::GetWidgetStack(FGameplayTag LayerTag) const
{
    return LayerMap.FindRef(LayerTag);
}

UUserWidget* UWidgetManagerSubsystem::ShowWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (UWidgetStack* WidgetStack = GetWidgetStack(GetLayerTag(WidgetClass)))
    {
        return WidgetStack->ShowWidget(WidgetClass);
    }

    return nullptr;
}

bool UWidgetManagerSubsystem::HideWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (UWidgetStack* WidgetStack = GetWidgetStack(GetLayerTag(WidgetClass)))
    {
        return WidgetStack->HideWidget(WidgetClass);
    }

    return false;
}

void UWidgetManagerSubsystem::ToggleWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (UWidgetStack* WidgetStack = GetWidgetStack(GetLayerTag(WidgetClass)))
    {
        return WidgetStack->ToggleWidget(WidgetClass);
    }
}

UUserWidget* UWidgetManagerSubsystem::ShowAlertWidget(AActor* PlayerActor, const FText& TitleText,
    const FText& MessageText, const FOnWidgetHidden& WidgetHiddenDelegate, TSubclassOf<UUserWidget> WidgetClass)
{
    WidgetClass = WidgetClass && WidgetClass->ImplementsInterface(UAlertWidgetInterface::StaticClass()) ? WidgetClass : UWidgetManagerSettings::Get()->GetDefaultAlertWidgetClass();

    if (WidgetClass)
    {
        if (UUserWidget* Widget = ShowWidget(WidgetClass))
        {
            IPopupWidgetInterface::Execute_SetTitleText(Widget, TitleText);
            IPopupWidgetInterface::Execute_SetMessageText(Widget, MessageText);
            IPopupWidgetInterface::Execute_BindOnWidgetHidden(Widget, WidgetHiddenDelegate);

            return Widget;
        }
    }

    return nullptr;
}

UUserWidget* UWidgetManagerSubsystem::ShowConfirmWidget(AActor* PlayerActor, const FText& TitleText,
    const FText& MessageText, const FOnWidgetHidden& WidgetHiddenDelegate,
    const FOnButtonClicked& ConfirmButtonClickedDelegate, TSubclassOf<UUserWidget> WidgetClass)
{
    WidgetClass = WidgetClass && WidgetClass->ImplementsInterface(UConfirmWidgetInterface::StaticClass()) ? WidgetClass : UWidgetManagerSettings::Get()->GetDefaultConfirmWidgetClass();

    if (WidgetClass)
    {
        if (UUserWidget* Widget = ShowWidget(WidgetClass))
        {
            IPopupWidgetInterface::Execute_SetTitleText(Widget, TitleText);
            IPopupWidgetInterface::Execute_SetMessageText(Widget, MessageText);
            IPopupWidgetInterface::Execute_BindOnWidgetHidden(Widget, WidgetHiddenDelegate);

            IConfirmWidgetInterface::Execute_BindOnConfirmButtonClicked(Widget, ConfirmButtonClickedDelegate);

            return Widget;
        }
    }

    return nullptr;
}

UUserWidget* UWidgetManagerSubsystem::ShowPromptWidget(AActor* PlayerActor, const FText& TitleText,
    const FText& MessageText, const FOnWidgetHidden& WidgetHiddenDelegate,
    const FOnPromptSubmitted& PromptSubmittedDelegate, bool bNumeric, float MinValue, float MaxValue,
    TSubclassOf<UUserWidget> WidgetClass)
{
    WidgetClass = WidgetClass && WidgetClass->ImplementsInterface(UPromptWidgetInterface::StaticClass()) ? WidgetClass : UWidgetManagerSettings::Get()->GetDefaultPromptWidgetClass();

    if (WidgetClass)
    {
        if (UUserWidget* Widget = ShowWidget(WidgetClass))
        {
            IPopupWidgetInterface::Execute_SetTitleText(Widget, TitleText);
            IPopupWidgetInterface::Execute_SetMessageText(Widget, MessageText);
            IPopupWidgetInterface::Execute_BindOnWidgetHidden(Widget, WidgetHiddenDelegate);

            IPromptWidgetInterface::Execute_BindOnPromptSubmitted(Widget, PromptSubmittedDelegate);
            IPromptWidgetInterface::Execute_SetNumeric(Widget, bNumeric);
            IPromptWidgetInterface::Execute_SetMinValue(Widget, MinValue);
            IPromptWidgetInterface::Execute_SetMaxValue(Widget, MaxValue);

            return Widget;
        }
    }

    return nullptr;
}

void UWidgetManagerSubsystem::CreateLayoutWidget(APlayerController* PlayerController)
{
    if (auto Settings = UWidgetManagerSettings::Get())
    {
        LayoutWidget = CreateWidget<UCommonUserWidget>(PlayerController);

        UOverlay* RootOverlay = LayoutWidget->WidgetTree->ConstructWidget<UOverlay>();
        LayoutWidget->WidgetTree->RootWidget = RootOverlay;

        TArray<FGameplayTag> LayerTags = { WidgetManager::UI::Layer::Default };
        LayerTags.Append(Settings->GetLayerTags());
        LayerMap.Reserve(LayerTags.Num());
        for (const auto& LayerTag : LayerTags)
        {
            UWidgetStack* WidgetStack = NewObject<UWidgetStack>(LayoutWidget);
            LayerMap.Emplace(LayerTag, WidgetStack);
        }

        LayoutWidget->AddToViewport();
    }
}

void UWidgetManagerSubsystem::DestroyLayoutWidget()
{
    if (LayoutWidget)
    {
        LayoutWidget->RemoveFromParent();
        LayerMap.Reset();
        LayoutWidget = nullptr;
    }
}
