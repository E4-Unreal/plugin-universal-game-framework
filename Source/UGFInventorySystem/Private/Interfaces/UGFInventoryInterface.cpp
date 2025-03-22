// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/UGFInventoryInterface.h"

#include "Logging.h"


void IUGFInventoryInterface::AddItem_Implementation(const FUGFItem& Item, int32& Overflow)
{
    LOG_TODO_INTERFACE
}

void IUGFInventoryInterface::RemoveItem_Implementation(const FUGFItem& Item, int32& Underflow)
{
    LOG_TODO_INTERFACE
}

bool IUGFInventoryInterface::HasItem_Implementation(const FUGFItem& Item) const
{
    LOG_TODO_INTERFACE

    return false;
}

void IUGFInventoryInterface::SwapInventorySlot_Implementation(int32 SelectedIndex, int32 TargetIndex)
{
    LOG_TODO_INTERFACE
}
