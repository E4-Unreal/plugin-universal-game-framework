// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/SlotManagerFunctionLibrary.h"

#include "Data/DataDefinitionBase.h"
#include "FunctionLibraries/DataManagerFunctionLibrary.h"
#include "Interfaces/SlotDataInterface.h"

bool USlotManagerFunctionLibrary::HasSlotData(UDataDefinitionBase* Definition)
{
    return GetSlotData(Definition) != nullptr;
}

TSoftObjectPtr<UTexture2D> USlotManagerFunctionLibrary::GetThumbnailTexture(UDataDefinitionBase* Definition)
{
    auto SlotData = GetSlotData(Definition);

    return SlotData ? ISlotDataInterface::Execute_GetThumbnailTexture(SlotData) : nullptr;
}

UDataAsset* USlotManagerFunctionLibrary::GetSlotData(UDataDefinitionBase* Definition)
{
    return UDataManagerFunctionLibrary::GetDataByInterface<USlotDataInterface>(Definition);
}
