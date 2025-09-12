// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractableComponent.h"

#include "Components/InteractionSystemComponent.h"
#include "Components/ShapeComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "GameplayTags/InteractionGameplaytags.h"
#include "Interfaces/InteractableInterface.h"
#include "Interfaces/InteractionWidgetInterface.h"
#include "Logging.h"

UInteractableComponent::UInteractableComponent()
{
    bWantsInitializeComponent = true;

    InteractionType = Interaction::Root;
    bPlayerOnly = true;
    bUseCursorEvent = true;
    bUseRenderCustomDepth = true;
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

bool UInteractableComponent::CanInteract(AActor* Interactor) const
{
    if (bUseOverlapShape && !OverlappingActors.Contains(Interactor)) return false;

    return Interactor && !GetOwner()->IsHidden();
}

void UInteractableComponent::Interact(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR_COMPONENT(Log, TEXT("Interactor: %s"), *Interactor->GetName())
    }
}

void UInteractableComponent::CancelInteract(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR_COMPONENT(Log, TEXT("Interactor: %s"), *Interactor->GetName())
    }
}

bool UInteractableComponent::CanSelect(AActor* Interactor) const
{
    if (bUseOverlapShape && !OverlappingActors.Contains(Interactor)) return false;

    return true;
}

void UInteractableComponent::Select(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR_COMPONENT(Log, TEXT("Interactor: %s"), *Interactor->GetName())

        if (bUseRenderCustomDepth && DisplayMesh.IsValid()) DisplayMesh->SetRenderCustomDepth(true);
        if (WidgetComponent.IsValid()) WidgetComponent->SetVisibility(true);
    }
}

void UInteractableComponent::Deselect(AActor* Interactor)
{
    if (Interactor)
    {
        LOG_ACTOR_COMPONENT(Log, TEXT("Interactor: %s"), *Interactor->GetName())

        if (bUseRenderCustomDepth && DisplayMesh.IsValid()) DisplayMesh->SetRenderCustomDepth(false);
        if (WidgetComponent.IsValid()) WidgetComponent->SetVisibility(false);
    }
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
    if (GetOwner())
    {
        GetOwner()->OnBeginCursorOver.AddDynamic(this, &ThisClass::OnBeginCursorOver);
        GetOwner()->OnEndCursorOver.AddDynamic(this, &ThisClass::OnEndCursorOver);
        GetOwner()->OnClicked.AddDynamic(this, &ThisClass::OnClicked);
    }
}

void UInteractableComponent::UnbindActorEvents()
{
    if (GetOwner())
    {
        GetOwner()->OnBeginCursorOver.RemoveDynamic(this, &ThisClass::OnBeginCursorOver);
        GetOwner()->OnEndCursorOver.RemoveDynamic(this, &ThisClass::OnEndCursorOver);
        GetOwner()->OnClicked.RemoveDynamic(this, &ThisClass::OnClicked);
    }
}

void UInteractableComponent::InitWidgetComponent() const
{
    if (!WidgetComponent.IsValid()) return;

    WidgetComponent->SetWidgetClass(InteractionWidgetClass);
    WidgetComponent->InitWidget();

    if (auto InteractionWidget = WidgetComponent->GetWidget())
    {
        if (InteractionWidget->Implements<UInteractionWidgetInterface>())
        {
            if (GetOwner()->Implements<UInteractableInterface>())
            {
                IInteractionWidgetInterface::Execute_SetInteractionType(InteractionWidget, IInteractableInterface::Execute_GetInteractionType(GetOwner()));
                IInteractionWidgetInterface::Execute_SetInteractionMessage(InteractionWidget, IInteractableInterface::Execute_GetInteractionMessage(GetOwner()));
            }
        }
    }
}

void UInteractableComponent::Shrink()
{
    for (int32 Index = OverlappingActors.Num() - 1; Index >= 0; --Index)
    {
        if (!OverlappingActors[Index].IsValid())
        {
            OverlappingActors.RemoveAt(Index, EAllowShrinking::No);
        }
    }

    OverlappingActors.Shrink();
}

void UInteractableComponent::AddOverlappingActor(AActor* NewActor)
{
    if (NewActor)
    {
        Shrink();

        if (!OverlappingActors.Contains(NewActor)) OverlappingActors.Emplace(NewActor);
    }
}

void UInteractableComponent::RemoveOverlappingActor(AActor* OldActor)
{
    if (OldActor)
    {
        Shrink();

        if (OverlappingActors.Contains(OldActor)) OverlappingActors.RemoveSingleSwap(OldActor);
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
    if (bUseCursorEvent)
    {
        if (auto PlayerInteractionSystem = GetPlayerInteractionSystem())
        {
            PlayerInteractionSystem->SelectTarget(GetOwner(), true);
        }
    }
}

void UInteractableComponent::OnEndCursorOver(AActor* TouchedActor)
{
    if (bUseCursorEvent)
    {
        if (auto PlayerInteractionSystem = GetPlayerInteractionSystem())
        {
            PlayerInteractionSystem->DeselectTarget(GetOwner(), true);
        }
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
