// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/UGFLevelPortal.h"

#include "Components/InteractableComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/CommonWidgetManagerSubsystem.h"
#include "Widgets/Popup/CommonPopupWidgetBase.h"
#include "GameplayTags/UGFGameplayTags.h"


AUGFLevelPortal::AUGFLevelPortal(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    GetInteractableComponent()->InteractionType = Interaction::Move;

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
        }
    }
}

void AUGFLevelPortal::RequestConfirmPopup(APlayerController* PlayerController)
{
    if (UCommonWidgetManagerSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UCommonWidgetManagerSubsystem>())
    {
        FButtonClickedDelegate Delegate;
        Delegate.BindDynamic(this, &ThisClass::MoveToLevel);

        Subsystem->ShowConfirmWidget(PlayerController, ConfirmTitle, FText::Format(ConfirmMessage, LevelName), Delegate);
    }
}

void AUGFLevelPortal::MoveToLevel()
{
    if (!Level.IsNull())
    {
        UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), Level);
    }
}
