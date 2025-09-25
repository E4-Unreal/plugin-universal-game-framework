// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Flexible/FlexibleDataBase.h"

#include "Data/Flexible/DataFragment.h"

bool UFlexibleDataBase::SupportsInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const
{
    auto DataFragment = GetFragmentByInterface(InterfaceClass);

    return DataFragment && DataFragment->GetClass()->ImplementsInterface(InterfaceClass);
}
