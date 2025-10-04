// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractableComponent.h"

#include "Components/InteractionSystemComponent.h"
#include "Components/ShapeComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "GameplayTags/InteractionGameplaytags.h"
#include "Logging.h"
#include "FunctionLibraries/InteractionSystemFunctionLibrary.h"
#include "Interfaces/TargetWidgetInterface.h"
#include "Settings/InteractionSystemSettings.h"
#include "Subsystems/WidgetManagerSubsystem.h"

UInteractableComponent::UInteractableComponent()
{
    bWantsInitializeComponent = true;

    InteractionType = Interaction::Root;
    bUseCursorEvent = true;
    bUseOutlineEffect = true;
}

void UInteractableComponent::InitializeComponent()
{
    Super::InitializeComponent();

    FindDisplayMesh();
    FindWidgetComponent();
    FindOverlapShape();
}

void UInteractableComponent::BeginPlay()
{
    Super::BeginPlay();

    BindOverlapShapeEvents();
    BindActorEvents();

    InitWidgetComponent();
}

void UInteractableComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    UnbindOverlapShapeEvents();
    UnbindActorEvents();

    Super::OnComponentDestroyed(bDestroyingHierarchy);
}

float UInteractableComponent::GetInteractionDuration_Implementation() const
{
    return 0.0f;
}

AActor* UInteractableComponent::GetInteractor_Implementation() const
{
    return CurrentInteractor.Get();
}

FGameplayTag UInteractableComponent::GetInteractionType_Implementation() const
{
    return InteractionType;
}

FText UInteractableComponent::GetInteractionMessage_Implementation() const
{
    return InteractionMessage;
}

bool UInteractableComponent::CanInteract_Implementation(AActor* Interactor)
{
    if (bUseOverlapShape && !OverlappingActors.Contains(Interactor)) return false;

    return Interactor && !GetOwner()->IsHidden();
}

void UInteractableComponent::StartInteract_Implementation(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR_COMPONENT(Log, TEXT("Interactor: %s"), *Interactor->GetName())

        OnStartInteract(Interactor);
    }
}

void UInteractableComponent::Interact_Implementation(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR_COMPONENT(Log, TEXT("Interactor: %s"), *Interactor->GetName())

        OnInteract(Interactor);
    }
}

void UInteractableComponent::CancelInteract_Implementation(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR_COMPONENT(Log, TEXT("Interactor: %s"), *Interactor->GetName())

        OnCancelInteract(Interactor);
    }
}

bool UInteractableComponent::CanSelect_Implementation(AActor* Interactor)
{
    if (bUseOverlapShape && !OverlappingActors.Contains(Interactor)) return false;

    return true;
}

void UInteractableComponent::Select_Implementation(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR_COMPONENT(Log, TEXT("Interactor: %s"), *Interactor->GetName())

        OnSelect(Interactor);
    }
}

void UInteractableComponent::Deselect_Implementation(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR_COMPONENT(Log, TEXT("Interactor: %s"), *Interactor->GetName())

        OnDeselect(Interactor);
    }
}

void UInteractableComponent::SetDisplayMesh(UMeshComponent* NewDisplayMesh)
{
    DisplayMesh = NewDisplayMesh;
}

void UInteractableComponent::SetWidgetComponent(UWidgetComponent* NewWidgetComponent)
{
    WidgetComponent = NewWidgetComponent;
}

void UInteractableComponent::SetOverlapShape(UShapeComponent* NewOverlapShape)
{
    OverlapShape = NewOverlapShape;
}

void UInteractableComponent::SetInteractionType(FGameplayTag NewInteractionType)
{
    InteractionType = NewInteractionType;

    if (WidgetComponent.IsValid())
    {
        if (auto InteractionWidget = WidgetComponent->GetWidget())
        {
            UInteractionSystemFunctionLibrary::SetInteractionType(InteractionWidget, InteractionType);
        }
    }
}

void UInteractableComponent::SetInteractionMessage(const FText& NewInteractionMessage)
{
    InteractionMessage = NewInteractionMessage;

    if (WidgetComponent.IsValid())
    {
        if (auto InteractionWidget = WidgetComponent->GetWidget())
        {
            UInteractionSystemFunctionLibrary::SetInteractionMessage(InteractionWidget, GetInteractionMessage());
        }
    }
}

TSubclassOf<UUserWidget> UInteractableComponent::GetInteractionWidgetClass() const
{
    return InteractionWidgetClass ? InteractionWidgetClass : UInteractionSystemSettings::Get()->GetDefaultInteractionWidgetClass();
}

UInteractionSystemComponent* UInteractableComponent::GetPlayerInteractionSystem() const
{
    if (APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn())
    {
        if (auto InteractionSystem = PlayerPawn->GetComponentByClass<UInteractionSystemComponent>())
        {
            return InteractionSystem;
        }
    }

    return nullptr;
}

void UInteractableComponent::OnStartInteract_Implementation(AActor* Interactor)
{
    UInteractionSystemFunctionLibrary::Interact(GetOwner(), Interactor);
}

void UInteractableComponent::OnInteract_Implementation(AActor* Interactor)
{
    CurrentInteractor = Interactor;
    ShowMenuWidget(Interactor);
}

void UInteractableComponent::OnCancelInteract_Implementation(AActor* Interactor)
{
    HideMenuWidget(Interactor);
    CurrentInteractor = nullptr;
}

void UInteractableComponent::OnSelect_Implementation(AActor* Interactor)
{
    ActivateOutlineEffect();
    ShowInteractionWidget();
}

void UInteractableComponent::OnDeselect_Implementation(AActor* Interactor)
{
    DeactivateOutlineEffect();
    HideInteractionWidget();
}

void UInteractableComponent::ActivateOutlineEffect()
{
    if (bUseOutlineEffect && DisplayMesh.IsValid())
    {
        DisplayMesh->SetRenderCustomDepth(true);
    }
}

void UInteractableComponent::DeactivateOutlineEffect()
{
    if (bUseOutlineEffect && DisplayMesh.IsValid())
    {
        DisplayMesh->SetRenderCustomDepth(false);
    }
}

void UInteractableComponent::ShowInteractionWidget()
{
    if (WidgetComponent.IsValid())
    {
        WidgetComponent->SetVisibility(true);
    }
}

void UInteractableComponent::HideInteractionWidget()
{
    if (WidgetComponent.IsValid())
    {
        WidgetComponent->SetVisibility(false);
    }
}

UUserWidget* UInteractableComponent::ShowMenuWidget(AActor* PlayerActor)
{
    if (PlayerActor && MenuWidgetClass)
    {
        UUserWidget* MenuWidget = GetWorld()->GetGameInstance()->GetSubsystem<UWidgetManagerSubsystem>()->ShowWidget(PlayerActor, MenuWidgetClass);
        if (MenuWidget && MenuWidget->Implements<UTargetWidgetInterface>())
        {
            ITargetWidgetInterface::Execute_SetTargetActor(MenuWidget, GetOwner());
        }

        return MenuWidget;
    }

    return nullptr;
}

bool UInteractableComponent::HideMenuWidget(AActor* PlayerActor)
{
    if (PlayerActor && MenuWidgetClass)
    {
        return GetWorld()->GetGameInstance()->GetSubsystem<UWidgetManagerSubsystem>()->HideWidget(PlayerActor, MenuWidgetClass);
    }

    return false;
}

void UInteractableComponent::FindDisplayMesh()
{
    if (DisplayMesh.IsValid()) return;

    if (ACharacter* OwningCharacter = Cast<ACharacter>(GetOwner()))
    {
        DisplayMesh = OwningCharacter->GetMesh();
    }
    else
    {
        DisplayMesh = GetOwner()->GetComponentByClass<UMeshComponent>();
    }
}

void UInteractableComponent::FindWidgetComponent()
{
    if (WidgetComponent.IsValid()) return;

    WidgetComponent = GetOwner()->GetComponentByClass<UWidgetComponent>();
}

void UInteractableComponent::FindOverlapShape()
{
    if (OverlapShape.IsValid()) return;

    OverlapShape = GetOwner()->GetComponentByClass<UShapeComponent>();
}

void UInteractableComponent::BindOverlapShapeEvents()
{
    if (bUseOverlapShape && OverlapShape.IsValid())
    {
        OverlapShape->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapShapeBeginOverlap);
        OverlapShape->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapShapeEndOverlap);
    }
}

void UInteractableComponent::UnbindOverlapShapeEvents()
{
    if (bUseOverlapShape && OverlapShape.IsValid())
    {
        OverlapShape->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnOverlapShapeBeginOverlap);
        OverlapShape->OnComponentEndOverlap.RemoveDynamic(this, &ThisClass::OnOverlapShapeEndOverlap);
    }
}

void UInteractableComponent::BindActorEvents()
{
    if (bUseCursorEvent && GetOwner())
    {
        GetOwner()->OnBeginCursorOver.AddDynamic(this, &ThisClass::OnBeginCursorOver);
        GetOwner()->OnEndCursorOver.AddDynamic(this, &ThisClass::OnEndCursorOver);
        GetOwner()->OnClicked.AddDynamic(this, &ThisClass::OnClicked);
    }
}

void UInteractableComponent::UnbindActorEvents()
{
    if (bUseCursorEvent && GetOwner())
    {
        GetOwner()->OnBeginCursorOver.RemoveDynamic(this, &ThisClass::OnBeginCursorOver);
        GetOwner()->OnEndCursorOver.RemoveDynamic(this, &ThisClass::OnEndCursorOver);
        GetOwner()->OnClicked.RemoveDynamic(this, &ThisClass::OnClicked);
    }
}

void UInteractableComponent::InitWidgetComponent() const
{
    if (!WidgetComponent.IsValid()) return;

    WidgetComponent->SetWidgetClass(GetInteractionWidgetClass());
    WidgetComponent->InitWidget();

    if (auto InteractionWidget = WidgetComponent->GetWidget())
    {
        UInteractionSystemFunctionLibrary::SetInteractionType(InteractionWidget, UInteractionSystemFunctionLibrary::GetInteractionType(GetOwner()));
        UInteractionSystemFunctionLibrary::SetInteractionMessage(InteractionWidget, UInteractionSystemFunctionLibrary::GetInteractionMessage(GetOwner()));
    }
}

void UInteractableComponent::AddOverlappingActor(AActor* NewActor)
{
    if (NewActor && !OverlappingActors.Contains(NewActor))
    {
        OverlappingActors.Emplace(NewActor);
    }
}

void UInteractableComponent::RemoveOverlappingActor(AActor* OldActor)
{
    if (OldActor && OverlappingActors.Contains(OldActor))
    {
        OverlappingActors.RemoveSingleSwap(OldActor);
    }
}

void UInteractableComponent::OnOverlapShapeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AddOverlappingActor(OtherActor);

    if (auto InteractionSystem = OtherActor->GetComponentByClass<UInteractionSystemComponent>())
    {
        InteractionSystem->AddTarget(GetOwner());
    }
}

void UInteractableComponent::OnOverlapShapeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    RemoveOverlappingActor(OtherActor);

    if (auto InteractionSystem = OtherActor->GetComponentByClass<UInteractionSystemComponent>())
    {
        InteractionSystem->RemoveTarget(GetOwner());
    }
}

void UInteractableComponent::OnBeginCursorOver(AActor* TouchedActor)
{
    if (auto PlayerInteractionSystem = GetPlayerInteractionSystem())
    {
        PlayerInteractionSystem->SelectTarget(GetOwner());
    }
}

void UInteractableComponent::OnEndCursorOver(AActor* TouchedActor)
{
    if (auto PlayerInteractionSystem = GetPlayerInteractionSystem())
    {
        PlayerInteractionSystem->DeselectTarget(GetOwner());
        PlayerInteractionSystem->RefreshTargets();
    }
}

void UInteractableComponent::OnClicked(AActor* TouchedActor, FKey ButtonPressed)
{
    if (bUseCursorEvent)
    {
        if (auto PlayerInteractionSystem = GetPlayerInteractionSystem())
        {
            PlayerInteractionSystem->TryInteract();
        }
    }
}
