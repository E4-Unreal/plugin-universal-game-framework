// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/DataObjectInterface.h"


// Add default functionality here for any IDataInstanceInterface functions that are not pure virtual.
bool IDataObjectInterface::SupportsInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const
{
    return Cast<UObject>(this)->GetClass()->ImplementsInterface(InterfaceClass);
}
