// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Flexible/FlexibleDataObjectBase.h"

#include "Data/Flexible/DataObjectFragment.h"

UObject* UFlexibleDataObjectBase::GetDataObjectByInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const
{
    auto DataObject = Super::GetDataObjectByInterface_Implementation(InterfaceClass);

    return DataObject ? DataObject : GetFragmentByInterface(InterfaceClass);
}
