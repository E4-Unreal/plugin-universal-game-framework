// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Flexible/FlexibleDataObjectBase.h"

#include "Data/Flexible/DataObjectFragment.h"

bool UFlexibleDataObjectBase::SupportsInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const
{
    auto DataObjectFragment = GetFragmentByInterface(InterfaceClass);

    return DataObjectFragment && DataObjectFragment->GetClass()->ImplementsInterface(InterfaceClass);
}
