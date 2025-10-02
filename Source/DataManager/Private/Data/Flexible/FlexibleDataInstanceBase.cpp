// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Flexible/FlexibleDataInstanceBase.h"

#include "Data/Flexible/DataInstanceFragment.h"

UObject* UFlexibleDataInstanceBase::GetDataInstanceByInterface(TSubclassOf<UInterface> InterfaceClass) const
{
    auto DataObject = Super::GetDataInstanceByInterface(InterfaceClass);

    return DataObject ? DataObject : GetFragmentByInterface(InterfaceClass);
}
