// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ResourceActor.h"

#include "Components/AttributeSystemComponent.h"
#include "Components/InteractableComponent.h"
#include "Components/ItemContainerComponent.h"
#include "Kismet/GameplayStatics.h"

const FName AResourceActor::AttributeSystemName(TEXT("AttributeSystem"));

AResourceActor::AResourceActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* SocketManager */

    AttributeSystem = CreateDefaultSubobject<UAttributeSystemComponent>(AttributeSystemName);
}

void AResourceActor::Interact_Implementation(AActor* Interactor)
{
    GetInteractableComponent()->Interact(Interactor);

    // TODO 캐릭터 애니메이션 재생 > 애님 노티파이로 ApplyDamage
    UGameplayStatics::ApplyDamage(this, 50, Interactor->GetInstigator()->GetController(), Interactor, nullptr);
}

void AResourceActor::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    if (GetAttributeSystem())
    {
        GetAttributeSystem()->OnAttributeValueChanged.AddDynamic(this, &ThisClass::OnAttributeValueChanged);
        GetAttributeSystem()->OnDamaged.AddDynamic(this, &ThisClass::OnDamaged);
        GetAttributeSystem()->OnHealed.AddDynamic(this, &ThisClass::OnHealed);
        GetAttributeSystem()->OnDead.AddDynamic(this, &ThisClass::OnDead);
        GetAttributeSystem()->OnRevived.AddDynamic(this, &ThisClass::OnRevived);
    }
}

float AResourceActor::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                                       class AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    GetAttributeSystem()->TakeDamage(ActualDamage, DamageEvent, EventInstigator, DamageCauser);

    return ActualDamage;
}

void AResourceActor::OnAttributeValueChanged_Implementation(FGameplayTag AttributeType, float OldValue, float NewValue)
{

}

void AResourceActor::OnDamaged_Implementation(float Value)
{

}

void AResourceActor::OnHealed_Implementation(float Value)
{

}

void AResourceActor::OnDead_Implementation()
{
    GetItemContainer()->SpawnItems();
}

void AResourceActor::OnRevived_Implementation()
{

}
