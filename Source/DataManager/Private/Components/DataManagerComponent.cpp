// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DataManagerComponent.h"

#include "Net/UnrealNetwork.h"


UDataManagerComponent::UDataManagerComponent()
{

}

void UDataManagerComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Definition);
    DOREPLIFETIME(ThisClass, Instance);
}

#if WITH_EDITOR
void UDataManagerComponent::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    FName PropertyName = PropertyChangedEvent.Property != nullptr ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, Definition))
    {
        SetDefinition(Definition);
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, Instance))
    {
        SetDataInstance(Instance);
    }

    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void UDataManagerComponent::Refresh_Implementation()
{
    // Data 혹은 DataInstance를 활용하여 액터 혹은 액터 컴포넌트 설정
}

void UDataManagerComponent::SetDefinition(UDataDefinitionBase* NewDefinition)
{
    Definition = NewDefinition;

    if (Instance) RemoveReplicatedObject(Cast<UReplicatedObject>(Instance));
    Instance = nullptr;

    Refresh();
}

void UDataManagerComponent::SetDataInstance(UDataInstanceBase* NewInstance)
{
    if (Instance) RemoveReplicatedObject(Cast<UReplicatedObject>(Instance));
    Instance = NewInstance;
    if (Instance) AddReplicatedObject(Cast<UReplicatedObject>(Instance));

    Definition = nullptr;

    Refresh();
}

void UDataManagerComponent::OnRep_Definition(UDataDefinitionBase* OldDefinition)
{
    if (Definition)
    {
        Refresh();
    }
}

void UDataManagerComponent::OnRep_Instance(UDataInstanceBase* OldInstance)
{
    if (Instance)
    {
        Refresh();
    }
}
