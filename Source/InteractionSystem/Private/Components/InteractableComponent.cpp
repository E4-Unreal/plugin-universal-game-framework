// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractableComponent.h"

#include "Components/InteractionSystemComponent.h"
#include "Components/ShapeComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "GameplayTags/InteractionGameplaytags.h"

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

void UInteractableComponent::ActivateFocusEffects(AActor* Interactor)
{
    if (Interactor)
    {
        if (bUseRenderCustomDepth && DisplayMesh.IsValid()) DisplayMesh->SetRenderCustomDepth(true);
        if (WidgetComponent.IsValid()) WidgetComponent->SetVisibility(true);
    }
}

void UInteractableComponent::DeactivateFocusEffects(AActor* Interactor)
{
    if (Interactor)
    {
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
    if (OverlapShape.IsValid())
    {
        OverlapShape->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapShapeBeginOverlap);
        OverlapShape->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapShapeEndOverlap);
    }
}

void UInteractableComponent::UnbindOverlapShapeEvents()
{
    if (OverlapShape.IsValid())
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
}

void UInteractableComponent::OnOverlapShapeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    RemoveOverlappingActor(OtherActor);
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
