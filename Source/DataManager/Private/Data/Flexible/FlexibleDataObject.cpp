// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Flexible/FlexibleDataObject.h"

#include "Data/Flexible/DataObjectFragment.h"
#include "Net/UnrealNetwork.h"

void UFlexibleDataObject::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Fragments)
}

UDataObjectFragment* UFlexibleDataObject::GetFragmentByInterface(const TSubclassOf<UInterface> InterfaceClass) const
{
    if (InterfaceClass)
    {
        for (const auto& Fragment : Fragments)
        {
            if (Fragment && Fragment->GetClass()->ImplementsInterface(InterfaceClass))
            {
                return Fragment;
            }
        }
    }

    return nullptr;
}
