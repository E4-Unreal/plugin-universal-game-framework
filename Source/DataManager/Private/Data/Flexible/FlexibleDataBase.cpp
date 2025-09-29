// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Flexible/FlexibleDataBase.h"

#include "Data/Flexible/DataFragment.h"

const TArray<UDataFragment*> UFlexibleDataBase::EmptyFragments;

UDataAsset* UFlexibleDataBase::GetDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const
{
    auto Data = Super::GetDataByInterface_Implementation(InterfaceClass);

    return Data ? Data : GetFragmentByInterface(InterfaceClass);
}

const TArray<UDataFragment*>& UFlexibleDataBase::GetFragments() const
{
    return EmptyFragments;
}

UDataFragment* UFlexibleDataBase::CreateFragment(TSubclassOf<UDataFragment> FragmentClass) const
{
    if (FragmentClass)
    {
        return NewObject<UDataFragment>(const_cast<UFlexibleDataBase*>(this), FragmentClass, FragmentClass->GetFName(), RF_Public);
    }

    return nullptr;
}

UDataFragment* UFlexibleDataBase::GetFragmentByClass(TSubclassOf<UDataFragment> FragmentClass) const
{
    if (FragmentClass)
    {
        for (const auto& Fragment : GetFragments())
        {
            if (Fragment && Fragment->IsA(FragmentClass))
            {
                return Fragment;
            }
        }
    }

    return nullptr;
}

UDataFragment* UFlexibleDataBase::GetFragmentByInterface(const TSubclassOf<UInterface> InterfaceClass) const
{
    if (InterfaceClass)
    {
        for (const auto& Fragment : GetFragments())
        {
            if (Fragment && Fragment->GetClass()->ImplementsInterface(InterfaceClass))
            {
                return Fragment;
            }
        }
    }

    return nullptr;
}
