// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Flexible/FlexibleData.h"

#include "Data/Flexible/DataFragment.h"

UDataFragment* UFlexibleData::GetFragmentByClass(TSubclassOf<UDataFragment> FragmentClass) const
{
    if (FragmentClass)
    {
        for (const auto& Fragment : Fragments)
        {
            if (Fragment && Fragment->IsA(FragmentClass))
            {
                return Fragment;
            }
        }
    }

    return nullptr;
}

UDataFragment* UFlexibleData::GetFragmentByInterface(const TSubclassOf<UInterface> InterfaceClass) const
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
