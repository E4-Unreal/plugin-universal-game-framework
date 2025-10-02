// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Flexible/FlexibleDataDefinitionBase.h"

#include "Data/Flexible/DataFragment.h"
#include "Data/Flexible/FlexibleDataInstance.h"

const TArray<UDataFragment*> UFlexibleDataDefinitionBase::EmptyFragments;

UFlexibleDataDefinitionBase::UFlexibleDataDefinitionBase()
{
    DataInstanceClass = UFlexibleDataInstance::StaticClass();
}

UDataAsset* UFlexibleDataDefinitionBase::GetDataByInterface(TSubclassOf<UInterface> InterfaceClass) const
{
    auto Data = Super::GetDataByInterface(InterfaceClass);

    return Data ? Data : GetFragmentByInterface(InterfaceClass);
}

UDataInstanceBase* UFlexibleDataDefinitionBase::CreateDataInstance() const
{
    auto DataInstance = Super::CreateDataInstance();

    if (auto FlexibleDataInstance = Cast<UFlexibleDataInstance>(DataInstance))
    {
        for (auto Fragment : GetFragments())
        {
            if (Fragment == nullptr) continue;

            if (auto DataInstanceFragment = Fragment->CreateDataInstanceFragment())
            {
                FlexibleDataInstance->Fragments.Emplace(DataInstanceFragment);
            }
        }
    }

    return DataInstance;
}

const TArray<UDataFragment*>& UFlexibleDataDefinitionBase::GetFragments() const
{
    return EmptyFragments;
}

UDataFragment* UFlexibleDataDefinitionBase::CreateFragment(TSubclassOf<UDataFragment> FragmentClass) const
{
    if (FragmentClass)
    {
        return NewObject<UDataFragment>(const_cast<UFlexibleDataDefinitionBase*>(this), FragmentClass, FragmentClass->GetFName(), RF_Public);
    }

    return nullptr;
}

UDataFragment* UFlexibleDataDefinitionBase::GetFragmentByClass(TSubclassOf<UDataFragment> FragmentClass) const
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

UDataFragment* UFlexibleDataDefinitionBase::GetFragmentByInterface(const TSubclassOf<UInterface> InterfaceClass) const
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
