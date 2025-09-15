// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionSystemComponent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/InteractableInterface.h"
#include "Logging.h"

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
    if (NewTarget
        && !AvailableTargets.Contains(NewTarget)
        && NewTarget->Implements<UInteractableInterface>())
    {
        AvailableTargets.Emplace(NewTarget);

        RefreshTargets();
    }
}

void UInteractionSystemComponent::RemoveTarget(AActor* OldTarget)
{
    if (OldTarget
        && AvailableTargets.Contains(OldTarget)
        && OldTarget->Implements<UInteractableInterface>())
    {
        DeselectTarget(OldTarget);

        AvailableTargets.RemoveSingleSwap(OldTarget);

        RefreshTargets();
    }
}

void UInteractionSystemComponent::SelectTarget(AActor* NewTarget)
{
    if (NewTarget
        && AvailableTargets.Contains(NewTarget)
        && NewTarget->Implements<UInteractableInterface>()
        && IInteractableInterface::Execute_CanSelect(NewTarget, GetOwner()))
    {
        // 기존에 선택된 액터들 비활성화

        DeselectTargets();

        // 새로 선택된 액터 활성화

        IInteractableInterface::Execute_Select(NewTarget, GetOwner());
        SelectedTargets.Emplace(NewTarget);
        SelectedInteractionType = IInteractableInterface::Execute_GetInteractionType(NewTarget);
    }
}

void UInteractionSystemComponent::SelectTargets(const TArray<AActor*>& NewTargets)
{
    // 유효성 검사

    if (NewTargets.IsEmpty())
    {
        LOG_ACTOR_COMPONENT(Warning, TEXT("No Targets To Select."))
        return;
    }

    AActor* FirstSelectedTarget = NewTargets[0];
    if (!FirstSelectedTarget->Implements<UInteractableInterface>())
    {
        LOG_ACTOR_COMPONENT(Warning, TEXT("%s doesn't implement the InteractableInterface."), *FirstSelectedTarget->GetName())
        return;
    }

    SelectedInteractionType = IInteractableInterface::Execute_GetInteractionType(FirstSelectedTarget);
    if (!SelectedInteractionType.IsValid())
    {
        LOG_ACTOR_COMPONENT(Warning, TEXT("%s's interaction type is not valid."), *FirstSelectedTarget->GetName())
        return;
    }

    // 기존에 선택된 액터들 비활성화

    DeselectTargets();

    // 새로 선택된 액터들 활성화

    SelectedTargets.Reserve(NewTargets.Num());
    for (AActor* NewTarget : NewTargets)
    {
        if (NewTarget
            && AvailableTargets.Contains(NewTarget)
            && NewTarget->Implements<UInteractableInterface>()
            && IInteractableInterface::Execute_CanSelect(NewTarget, GetOwner())
            && SelectedInteractionType == IInteractableInterface::Execute_GetInteractionType(NewTarget))
        {
            IInteractableInterface::Execute_Select(NewTarget, GetOwner());
            SelectedTargets.Emplace(NewTarget);
        }
    }
}

void UInteractionSystemComponent::DeselectTarget(AActor* OldTarget)
{
    if (OldTarget && SelectedTargets.Contains(OldTarget) && OldTarget->Implements<UInteractableInterface>())
    {
        IInteractableInterface::Execute_Deselect(OldTarget, GetOwner());

        SelectedTargets.RemoveSingleSwap(OldTarget);
        if (SelectedTargets.IsEmpty()) SelectedInteractionType = FGameplayTag::EmptyTag;
    }
}

void UInteractionSystemComponent::DeselectTargets()
{
    for (const auto& SelectedTarget : SelectedTargets)
    {
        if (SelectedTarget.IsValid() && SelectedTarget->Implements<UInteractableInterface>())
        {
            IInteractableInterface::Execute_Deselect(SelectedTarget.Get(), GetOwner());
        }
    }

    SelectedTargets.Empty();
    SelectedInteractionType = FGameplayTag::EmptyTag;
}

void UInteractionSystemComponent::RefreshTargets()
{
    LOG_ACTOR_COMPONENT(Log, TEXT(""))

    // 유효성 검사

    if (AvailableTargets.IsEmpty()) return;

    // 기존에 선택된 액터들 비활성화

    DeselectTargets();

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

    for (const auto& SelectedTarget : GetSelectedTargets())
    {
        if (SelectedTarget && IInteractableInterface::Execute_CanInteract(SelectedTarget, GetOwner()))
        {
            IInteractableInterface::Execute_Interact(SelectedTarget, GetOwner());
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
    RefreshTargets();
}

void UInteractionSystemComponent::OnOverlapCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    RefreshTargets();
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
