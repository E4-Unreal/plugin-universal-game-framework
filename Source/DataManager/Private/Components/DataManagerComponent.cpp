// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DataManagerComponent.h"

#include "Interfaces/InstanceDataInterface.h"
#include "Net/UnrealNetwork.h"


UDataManagerComponent::UDataManagerComponent()
{

}

void UDataManagerComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Data);
    DOREPLIFETIME(ThisClass, DataInstance);
}

#if WITH_EDITOR
void UDataManagerComponent::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    FName PropertyName = PropertyChangedEvent.Property != nullptr ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, Data))
    {
        SetData(Data);
    }
    else if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, DataInstance))
    {
        SetDataInstance(DataInstance);
    }

    Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

void UDataManagerComponent::Refresh_Implementation()
{
    // Data 혹은 DataInstance를 활용하여 액터 혹은 액터 컴포넌트 설정
}

UDataAsset* UDataManagerComponent::GetData() const
{
    if (DataInstance && DataInstance->Implements<UInstanceDataInterface>())
    {
        return IInstanceDataInterface::Execute_GetData(DataInstance);
    }

    return Data;
}

void UDataManagerComponent::SetData(UDataAsset* NewData)
{
    Data = NewData;

    if (DataInstance) RemoveReplicatedObject(Cast<UReplicatedObject>(DataInstance));
    DataInstance = nullptr;

    Refresh();
}

void UDataManagerComponent::SetDataInstance(UObject* NewDataInstance)
{
    if (DataInstance) RemoveReplicatedObject(Cast<UReplicatedObject>(DataInstance));
    DataInstance = NewDataInstance;
    if (DataInstance) AddReplicatedObject(Cast<UReplicatedObject>(DataInstance));

    Data = nullptr;

    Refresh();
}

void UDataManagerComponent::OnRep_Data(UDataAsset* OldData)
{
    if (Data)
    {
        Refresh();
    }
}

void UDataManagerComponent::OnRep_DataInstance(UObject* OldDataInstance)
{
    if (DataInstance)
    {
        Refresh();
    }
}
