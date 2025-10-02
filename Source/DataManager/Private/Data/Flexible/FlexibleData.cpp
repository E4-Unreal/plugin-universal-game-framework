// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Flexible/FlexibleData.h"

UDataFragment* UFlexibleData::AddFragment(TSubclassOf<UDataFragment> FragmentClass)
{
    auto Fragment = GetFragmentByClass(FragmentClass);

    if (Fragment == nullptr)
    {
        Fragment = CreateFragment(FragmentClass);
        Fragments.Emplace(Fragment);
    }

    return Fragment;
}
