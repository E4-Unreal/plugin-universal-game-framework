// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Flexible/FlexibleData.h"

UDataFragment* UFlexibleData::AddFragment(TSubclassOf<UDataFragment> FragmentClass)
{
    auto DataFragment = CreateFragment(FragmentClass);
    Fragments.Emplace(DataFragment);

    return DataFragment;
}
