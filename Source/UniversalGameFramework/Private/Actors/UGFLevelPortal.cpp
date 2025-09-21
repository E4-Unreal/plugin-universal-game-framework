// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/UGFLevelPortal.h"

#include "Components/InteractableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/WidgetManagerSubsystem.h"
#include "Widgets/Popup/CommonPopupWidgetBase.h"
#include "GameplayTags/UGFGameplayTags.h"
#include "Interfaces/ConfirmWidgetInterface.h"


AUGFLevelPortal::AUGFLevelPortal(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    GetInteractableComponent()->InteractionType = Interaction::Move;
    GetInteractableComponent()->bUseOutlineEffect = false;

    LevelName = NSLOCTEXT("UGF", "LevelName", "Destination");
    ConfirmTitle = NSLOCTEXT("UGF", "MoveConfirmTitle", "Notice");
    ConfirmMessage = NSLOCTEXT("UGF", "MoveConfirmMessage", "Do you want to move to {0}");
}

FText AUGFLevelPortal::GetInteractionMessage_Implementation() const
{
    return LevelName;
}

void AUGFLevelPortal::Interact_Implementation(AActor* Interactor)
{
    Super::Interact_Implementation(Interactor);

    if (APawn* Pawn = Cast<APawn>(Interactor))
    {
        if (APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController()))
        {
            RequestConfirmPopup(PlayerController);
            GetInteractableComponent()->HideInteractionWidget();
        }
    }
}

bool AUGFLevelPortal::CanSelect_Implementation(AActor* Interactor)
{
    if (ConfirmPopupWidget.IsValid() && ConfirmPopupWidget->IsVisible()) return false;

    return Super::CanSelect_Implementation(Interactor);
}

void AUGFLevelPortal::RequestConfirmPopup(APlayerController* PlayerController)
{
    if (auto* Subsystem = GetGameInstance()->GetSubsystem<UWidgetManagerSubsystem>())
    {
        FOnWidgetHidden WidgetHiddenDelegate;
        FOnButtonClicked ConfirmButtonClickedDelegate;
        ConfirmButtonClickedDelegate.BindDynamic(this, &ThisClass::MoveToLevel);

        ConfirmPopupWidget = Subsystem->ShowConfirmWidget(PlayerController, ConfirmTitle, FText::Format(ConfirmMessage, LevelName), WidgetHiddenDelegate, ConfirmButtonClickedDelegate);
    }
}

void AUGFLevelPortal::MoveToLevel()
{
    if (!Level.IsNull())
    {
        UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), Level);
    }
}
