// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemDefinition.h"

void UItemDefinition::Update(int32 NewID, const FText& NewDisplayText)
{
    ID = NewID;
    DisplayText = NewDisplayText;
}
