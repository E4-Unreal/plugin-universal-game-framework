// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/DataObjectInterface.h"


// Add default functionality here for any IDataInstanceInterface functions that are not pure virtual.
bool IDataObjectInterface::SupportsInterface_Implementation(TSubclassOf<UInterface> InterfaceClass) const
{
    const UObject* Object = Cast<UObject>(this);

    return Object && InterfaceClass ? Object->GetClass()->ImplementsInterface(InterfaceClass) : false;
}
