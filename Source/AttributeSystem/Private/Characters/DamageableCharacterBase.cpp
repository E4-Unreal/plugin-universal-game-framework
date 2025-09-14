// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DamageableCharacterBase.h"

#include "Components/AttributeSystemComponent.h"
#include "GameplayTags/AttributeGameplayTags.h"

const FName ADamageableCharacterBase::AttributeSystemName(TEXT("AttributeSystem"));

ADamageableCharacterBase::ADamageableCharacterBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* SocketManager */

    AttributeSystem = CreateDefaultSubobject<UAttributeSystemComponent>(AttributeSystemName);
}

void ADamageableCharacterBase::PostInitializeComponents()
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

float ADamageableCharacterBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                                       class AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    GetAttributeSystem()->TakeDamage(ActualDamage, DamageEvent, EventInstigator, DamageCauser);

    return ActualDamage;
}

void ADamageableCharacterBase::OnAttributeValueChanged_Implementation(FGameplayTag AttributeType, float OldValue, float NewValue)
{

}

void ADamageableCharacterBase::OnDamaged_Implementation(float Value)
{

}

void ADamageableCharacterBase::OnHealed_Implementation(float Value)
{

}

void ADamageableCharacterBase::OnDead_Implementation()
{

}

void ADamageableCharacterBase::OnRevived_Implementation()
{

}
