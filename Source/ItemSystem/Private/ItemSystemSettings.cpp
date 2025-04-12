// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystemSettings.h"

UItemSystemSettings::UItemSystemSettings()
{
    CategoryName = "Plugins";
    SectionName = "ItemSystem";
}

UItemDatabase* UItemSystemSettings::GetItemDatabase() const
{
    return ItemDatabase.LoadSynchronous();
}
