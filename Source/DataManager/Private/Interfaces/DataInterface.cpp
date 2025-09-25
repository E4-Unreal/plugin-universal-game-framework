// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/DataInterface.h"


// Add default functionality here for any IDataInterface functions that are not pure virtual.
bool IDataInterface::SupportsInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const
{
    return Cast<UObject>(this)->GetClass()->ImplementsInterface(InterfaceClass);
}
