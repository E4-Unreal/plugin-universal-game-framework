// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/WidgetManagerSubsystem.h"

bool UWidgetManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    TArray<UClass*> ChildClasses;
    GetDerivedClasses(GetClass(), ChildClasses, false);

    return ChildClasses.Num() == 0;
}
