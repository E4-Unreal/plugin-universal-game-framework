// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Flexible/FlexibleDataBase.h"

#include "Data/Flexible/DataFragment.h"
#include "Data/Flexible/FlexibleDataInstance.h"

const TArray<UDataFragment*> UFlexibleDataBase::EmptyFragments;

UFlexibleDataBase::UFlexibleDataBase()
{
    DataInstanceClass = UFlexibleDataInstance::StaticClass();
}

UDataAsset* UFlexibleDataBase::GetDataByInterface(TSubclassOf<UInterface> InterfaceClass) const
{
    auto Data = Super::GetDataByInterface(InterfaceClass);

    return Data ? Data : GetFragmentByInterface(InterfaceClass);
}

UDataInstanceBase* UFlexibleDataBase::CreateDataInstance() const
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
