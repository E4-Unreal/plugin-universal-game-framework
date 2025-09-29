// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Flexible/FlexibleDataObjectBase.h"

#include "Data/Flexible/DataObjectFragment.h"

UObject* UFlexibleDataObjectBase::GetInstanceDataByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const
{
    auto DataObject = Super::GetInstanceDataByInterface_Implementation(InterfaceClass);

    return DataObject ? DataObject : GetFragmentByInterface(InterfaceClass);
}
