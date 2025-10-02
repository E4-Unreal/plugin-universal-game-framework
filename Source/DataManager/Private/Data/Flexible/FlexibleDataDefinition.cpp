// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Flexible/FlexibleDataDefinition.h"

UDataFragment* UFlexibleDataDefinition::AddFragment(TSubclassOf<UDataFragment> FragmentClass)
{
    auto Fragment = GetFragmentByClass(FragmentClass);

    if (Fragment == nullptr)
    {
        Fragment = CreateFragment(FragmentClass);
        Fragments.Emplace(Fragment);

        MarkPackageDirty();
    }

    return Fragment;
}
