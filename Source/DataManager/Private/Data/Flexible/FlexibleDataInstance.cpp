// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Flexible/FlexibleDataInstance.h"

#include "Data/Flexible/DataInstanceFragment.h"
#include "Net/UnrealNetwork.h"

void UFlexibleDataInstance::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Fragments)
}

UDataInstanceFragment* UFlexibleDataInstance::GetFragmentByInterface(const TSubclassOf<UInterface> InterfaceClass) const
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
