// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PawnWidgetManagerComponent.h"

#include "InputAction.h"
#include "Subsystems/WidgetManagerSubsystem.h"


UPawnWidgetManagerComponent::UPawnWidgetManagerComponent()
{
}

void UPawnWidgetManagerComponent::BeginPlay()
{
    Super::BeginPlay();

    ShowHUDWidget(GetOwner());
    BindControllerChangedEvent();
}

void UPawnWidgetManagerComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    UnBindControllerChangedEvent();

    Super::OnComponentDestroyed(bDestroyingHierarchy);
}

TArray<FInputActionConfigData> UPawnWidgetManagerComponent::GetInputActionConfigs()
{
    TArray<FInputActionConfigData> InputActionConfigs;
    InputActionConfigs.Reserve(ToggleableWidgetMap.Num());
    for (const auto& [InputAction, ToggleableWidgetClass] : ToggleableWidgetMap)
    {
        InputActionConfigs.Emplace(InputAction, TSet({ ETriggerEvent::Triggered }));
    }

    return InputActionConfigs;
}

void UPawnWidgetManagerComponent::OnInputActionTriggered_Implementation(const FInputActionInstance& InputActionInstance)
{
    Super::OnInputActionTriggered_Implementation(InputActionInstance);

    const UInputAction* InputAction = InputActionInstance.GetSourceAction();
    if (ToggleableWidgetMap.Contains(InputAction))
    {
        ToggleWidget(ToggleableWidgetMap[InputAction]);
    }
}

UUserWidget* UPawnWidgetManagerComponent::ShowHUDWidget(AActor* PlayerActor)
{
    if (auto Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UWidgetManagerSubsystem>())
    {
        return Subsystem->ShowWidget(PlayerActor, HUDWidgetClass);
    }

    return nullptr;
}

bool UPawnWidgetManagerComponent::HideHUDWidget(AActor* PlayerActor)
{
    if (auto Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UWidgetManagerSubsystem>())
    {
        return Subsystem->HideWidget(PlayerActor, HUDWidgetClass);
    }

    return false;
}

void UPawnWidgetManagerComponent::ToggleWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (auto Subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UWidgetManagerSubsystem>())
    {
        return Subsystem->ToggleWidget(GetOwner(), WidgetClass);
    }
}

void UPawnWidgetManagerComponent::BindControllerChangedEvent()
{
    APawn* OwningPawn = CastChecked<APawn>(GetOwner());

    OwningPawn->ReceiveControllerChangedDelegate.AddDynamic(this, &ThisClass::OnControllerChanged);
}

void UPawnWidgetManagerComponent::UnBindControllerChangedEvent()
{
    APawn* OwningPawn = CastChecked<APawn>(GetOwner());

    OwningPawn->ReceiveControllerChangedDelegate.RemoveDynamic(this, &ThisClass::OnControllerChanged);
}

void UPawnWidgetManagerComponent::OnControllerChanged(APawn* Pawn, AController* OldController,
    AController* NewController)
{
    if (OldController)
    {
        HideHUDWidget(OldController);
    }

    if (NewController)
    {
        ShowHUDWidget(NewController);
    }
}
