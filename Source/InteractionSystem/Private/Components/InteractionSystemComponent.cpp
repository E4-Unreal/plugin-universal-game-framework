// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionSystemComponent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractableInterface.h"

UInteractionSystemComponent::UInteractionSystemComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bWantsInitializeComponent = true;

    Range = 128.0f;
}

void UInteractionSystemComponent::InitializeComponent()
{
    Super::InitializeComponent();

    FindOverlapSphere();
    FindOverlapCapsule();
}

void UInteractionSystemComponent::BeginPlay()
{
    Super::BeginPlay();

    BindOverlapSphereEvents();
    BindOverlapCapsuleEvents();
}

void UInteractionSystemComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    Super::OnComponentDestroyed(bDestroyingHierarchy);

    UnBindOverlapSphereEvents();
    UnBindOverlapCapsuleEvents();
}

TArray<AActor*> UInteractionSystemComponent::GetSelectedTargets()
{
    ShrinkTargets(SelectedTargets);

    TArray<AActor*> OutSelectedTargets;
    OutSelectedTargets.Reserve(SelectedTargets.Num());
    for (const auto& SelectedTarget : SelectedTargets)
    {
        OutSelectedTargets.Emplace(SelectedTarget.Get());
    }

    return OutSelectedTargets;
}

void UInteractionSystemComponent::SetOverlapSphere(USphereComponent* NewOverlapSphere)
{
    OverlapSphere = NewOverlapSphere;

    if (OverlapSphere.IsValid())
    {
        OverlapSphere->SetSphereRadius(Range);
    }
}

void UInteractionSystemComponent::SetOverlapCapsule(UCapsuleComponent* NewOverlapCapsule)
{
    OverlapCapsule = NewOverlapCapsule;
}

void UInteractionSystemComponent::FindOverlapSphere()
{
    if (OverlapSphere.IsValid()) return;

    SetOverlapSphere(GetOwner()->GetComponentByClass<USphereComponent>());
}

void UInteractionSystemComponent::FindOverlapCapsule()
{
    if (OverlapCapsule.IsValid()) return;

    if (ACharacter* OwningCharacter = Cast<ACharacter>(GetOwner()))
    {
        SetOverlapCapsule(OwningCharacter->GetCapsuleComponent());
    }
    else
    {
        SetOverlapCapsule(GetOwner()->GetComponentByClass<UCapsuleComponent>());
    }
}

void UInteractionSystemComponent::BindOverlapSphereEvents()
{
    if (OverlapSphere.IsValid())
    {
        OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapSphereBeginOverlap);
        OverlapSphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapSphereEndOverlap);
    }
}

void UInteractionSystemComponent::UnBindOverlapSphereEvents()
{
    if (OverlapSphere.IsValid())
    {
        OverlapSphere->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnOverlapSphereBeginOverlap);
        OverlapSphere->OnComponentEndOverlap.RemoveDynamic(this, &ThisClass::OnOverlapSphereEndOverlap);
    }
}

void UInteractionSystemComponent::BindOverlapCapsuleEvents()
{
    if (OverlapCapsule.IsValid())
    {
        OverlapCapsule->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapCapsuleBeginOverlap);
        OverlapCapsule->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapCapsuleEndOverlap);
    }
}

void UInteractionSystemComponent::UnBindOverlapCapsuleEvents()
{
    if (OverlapCapsule.IsValid())
    {
        OverlapCapsule->OnComponentBeginOverlap.RemoveDynamic(this, &ThisClass::OnOverlapCapsuleBeginOverlap);
        OverlapCapsule->OnComponentEndOverlap.RemoveDynamic(this, &ThisClass::OnOverlapCapsuleEndOverlap);
    }
}

void UInteractionSystemComponent::AddTarget(AActor* NewTarget)
{
    if (NewTarget && NewTarget->Implements<UInteractableInterface>() && IInteractableInterface::Execute_CanSelect(NewTarget, GetOwner()))
    {
        ShrinkTargets(AvailableTargets);

        if (!AvailableTargets.Contains(NewTarget))
        {
            AvailableTargets.Emplace(NewTarget);

            RefreshTargets();
        }
    }
}

void UInteractionSystemComponent::RemoveTarget(AActor* OldTarget)
{
    if (OldTarget && AvailableTargets.Contains(OldTarget))
    {
        ShrinkTargets(AvailableTargets);

        if (AvailableTargets.Contains(OldTarget))
        {
            AvailableTargets.RemoveSingleSwap(OldTarget);

            RefreshTargets();
        }
    }
}

void UInteractionSystemComponent::SelectTarget(AActor* NewTarget, bool bForce)
{
    if (NewTarget && IInteractableInterface::Execute_CanSelect(NewTarget, GetOwner()))
    {
        // ex) BeginCursorOver

        if (bForce)
        {
            for (const auto& SelectedTarget : SelectedTargets)
            {
                DeselectTarget(SelectedTarget.Get());
            }
        }

        // Select

        ShrinkTargets(AvailableTargets);
        ShrinkTargets(SelectedTargets);

        if (AvailableTargets.Contains(NewTarget) && !SelectedTargets.Contains(NewTarget))
        {
            SelectedTargets.Emplace(NewTarget);

            IInteractableInterface::Execute_Select(NewTarget, GetOwner());
        }
    }
}

void UInteractionSystemComponent::DeselectTarget(AActor* OldTarget, bool bForce)
{
    if (OldTarget)
    {
        // Deselect

        ShrinkTargets(SelectedTargets);

        if (SelectedTargets.Contains(OldTarget))
        {
            SelectedTargets.RemoveSingleSwap(OldTarget);

            IInteractableInterface::Execute_Deselect(OldTarget, GetOwner());
        }

        // es) EndCursorOver

        if (bForce)
        {
            RefreshTargets();
        }
    }
}

void UInteractionSystemComponent::RefreshTargets()
{
    // 초기화
    for (const auto& SelectedTarget : SelectedTargets)
    {
        DeselectTarget(SelectedTarget.Get());
    }
    SelectedTargets.Reset();

    // 유효성 검사
    if (AvailableTargets.IsEmpty()) return;

    // 가장 가까운 액터 선택
    float MinDistance = MAX_flt;
    int32 MinIndex = 0;

    for (int32 Index = 0; Index < AvailableTargets.Num(); ++Index)
    {
        const auto& AvailableTarget = AvailableTargets[Index];
        if (!AvailableTarget.IsValid()) continue;

        float Distance = GetDistanceToTarget(AvailableTarget.Get());
        if (Distance < MinDistance)
        {
            MinDistance = Distance;
            MinIndex = Index;
        }
    }

    SelectTarget(AvailableTargets[MinIndex].Get());
}

void UInteractionSystemComponent::SetRange(float NewRange)
{
    Range = NewRange;

    if (OverlapSphere.IsValid())
    {
        OverlapSphere->SetSphereRadius(Range);
    }
}

bool UInteractionSystemComponent::TryInteract()
{
    if (SelectedTargets.IsEmpty()) return false;

    bool bResult = true;

    for (const auto& SelectedTarget : SelectedTargets)
    {
        if (SelectedTarget.IsValid() && IInteractableInterface::Execute_CanInteract(SelectedTarget.Get(), GetOwner()))
        {
            IInteractableInterface::Execute_Interact(SelectedTarget.Get(), GetOwner());
        }
        else
        {
            bResult = false;
        }
    }

    return bResult;
}

void UInteractionSystemComponent::CancelInteract()
{
    if (SelectedTargets.IsEmpty()) return;

    for (const auto& SelectedTarget : SelectedTargets)
    {
        if (SelectedTarget.IsValid())
        {
            IInteractableInterface::Execute_CancelInteract(SelectedTarget.Get(), GetOwner());
        }
    }
}

void UInteractionSystemComponent::ShrinkTargets(TArray<TWeakObjectPtr<AActor>>& InTargets)
{
    for (int32 Index = InTargets.Num() - 1; Index >= 0; --Index)
    {
        if (!InTargets[Index].IsValid())
        {
            InTargets.RemoveAt(Index, EAllowShrinking::No);
        }
    }

    InTargets.Shrink();
}

void UInteractionSystemComponent::ShrinkAllTargets()
{
    ShrinkTargets(AvailableTargets);
    ShrinkTargets(SelectedTargets);
}

void UInteractionSystemComponent::OnOverlapSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                                              AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                              const FHitResult& SweepResult)
{
    AddTarget(OtherActor);
}

void UInteractionSystemComponent::OnOverlapSphereEndOverlap(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    RemoveTarget(OtherActor);
}

void UInteractionSystemComponent::OnOverlapCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OtherActor)
    {
        RefreshTargets();
    }
}

void UInteractionSystemComponent::OnOverlapCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor)
    {
        RefreshTargets();
    }
}

float UInteractionSystemComponent::GetDistanceToTarget(AActor* Target) const
{
    if (Target)
    {
        FVector OwnerLocation = GetOwner()->GetActorLocation();
        FVector TargetLocation = Target->GetActorLocation();

        return FVector::Dist(OwnerLocation, TargetLocation);
    }

    return MAX_flt;
}
