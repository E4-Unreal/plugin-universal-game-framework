// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/SlotManagerFunctionLibrary.h"

#include "FunctionLibraries/DataManagerFunctionLibrary.h"
#include "Interfaces/SlotDataInterface.h"

UDataAsset* USlotManagerFunctionLibrary::GetSlotData(UObject* DataObject)
{
    return UDataManagerFunctionLibrary::GetDataByInterface<USlotDataInterface>(DataObject);
}

TSoftObjectPtr<UTexture2D> USlotManagerFunctionLibrary::GetThumbnailTexture(UObject* DataObject)
{
    auto SlotData = GetSlotData(DataObject);

    return SlotData ? ISlotDataInterface::Execute_GetThumbnailTexture(SlotData) : nullptr;
}
