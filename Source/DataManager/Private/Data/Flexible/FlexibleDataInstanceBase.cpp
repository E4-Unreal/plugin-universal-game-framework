// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Flexible/FlexibleDataInstanceBase.h"

#include "Data/Flexible/DataInstanceFragment.h"

UObject* UFlexibleDataInstanceBase::GetInstanceDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const
{
    auto DataObject = Super::GetInstanceDataByInterface_Implementation(InterfaceClass);

    return DataObject ? DataObject : GetFragmentByInterface(InterfaceClass);
}
