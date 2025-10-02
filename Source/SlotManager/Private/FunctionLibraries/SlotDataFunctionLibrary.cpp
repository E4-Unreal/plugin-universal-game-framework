// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/SlotDataFunctionLibrary.h"

#include "Data/DataDefinitionBase.h"
#include "FunctionLibraries/DataManagerFunctionLibrary.h"
#include "Interfaces/SlotDataInterface.h"

bool USlotDataFunctionLibrary::HasSlotData(UDataDefinitionBase* Definition)
{
    return GetSlotData(Definition) != nullptr;
}

TSoftObjectPtr<UTexture2D> USlotDataFunctionLibrary::GetThumbnailTexture(UDataDefinitionBase* Definition)
{
    auto SlotData = GetSlotData(Definition);

    return SlotData ? ISlotDataInterface::Execute_GetThumbnailTexture(SlotData) : nullptr;
}

UDataAsset* USlotDataFunctionLibrary::GetSlotData(UDataDefinitionBase* Definition)
{
    return UDataManagerFunctionLibrary::GetDataByInterface<USlotDataInterface>(Definition);
}
