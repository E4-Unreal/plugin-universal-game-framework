// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/WeaponManagerFunctionLibrary.h"

#include "FunctionLibraries/DataManagerFunctionLibrary.h"
#include "Interfaces/WeaponDataInterface.h"
#include "Interfaces/WeaponInstanceInterface.h"

UDataAsset* UWeaponManagerFunctionLibrary::GetWeaponData(UObject* DataObject)
{
    return UDataManagerFunctionLibrary::GetDataByInterface<UWeaponDataInterface>(DataObject);
}

TSubclassOf<AActor> UWeaponManagerFunctionLibrary::GetActorClass(UObject* DataObject)
{
    auto WeaponData = GetWeaponData(DataObject);

    return WeaponData ? IWeaponDataInterface::Execute_GetActorClass(WeaponData) : nullptr;
}

FGameplayTag UWeaponManagerFunctionLibrary::GetSlotType(UObject* DataObject)
{
    auto WeaponData = GetWeaponData(DataObject);

    return WeaponData ? IWeaponDataInterface::Execute_GetSlotType(WeaponData) : FGameplayTag::EmptyTag;
}

FName UWeaponManagerFunctionLibrary::GetActiveSocketName(UObject* DataObject)
{
    auto WeaponData = GetWeaponData(DataObject);

    return WeaponData ? IWeaponDataInterface::Execute_GetActiveSocketName(WeaponData) : NAME_None;
}

FName UWeaponManagerFunctionLibrary::GetInActiveSocketName(UObject* DataObject)
{
    auto WeaponData = GetWeaponData(DataObject);

    return WeaponData ? IWeaponDataInterface::Execute_GetInActiveSocketName(WeaponData) : NAME_None;
}

float UWeaponManagerFunctionLibrary::GetMaxDurability(UObject* DataObject)
{
    auto WeaponData = GetWeaponData(DataObject);

    return WeaponData ? IWeaponDataInterface::Execute_GetMaxDurability(WeaponData) : 0;
}

UObject* UWeaponManagerFunctionLibrary::GetWeaponInstance(UObject* DataInstance)
{
    return UDataManagerFunctionLibrary::GetInstanceDataByInterface<UWeaponInstanceInterface>(DataInstance);
}

AActor* UWeaponManagerFunctionLibrary::GetActor(UObject* DataInstance)
{
    auto WeaponInstance = GetWeaponInstance(DataInstance);

    return WeaponInstance ? IWeaponInstanceInterface::Execute_GetActor(WeaponInstance) : nullptr;
}

void UWeaponManagerFunctionLibrary::SetActor(UObject* DataInstance, AActor* NewActor)
{
    if (auto WeaponInstance = GetWeaponInstance(DataInstance))
    {
        IWeaponInstanceInterface::Execute_SetActor(WeaponInstance, NewActor);
    }
}

float UWeaponManagerFunctionLibrary::GetDurability(UObject* DataInstance)
{
    auto WeaponInstance = GetWeaponInstance(DataInstance);

    return WeaponInstance ? IWeaponInstanceInterface::Execute_GetDurability(WeaponInstance) : 0;
}

void UWeaponManagerFunctionLibrary::SetDurability(UObject* DataInstance, float NewDurability)
{
    if (auto WeaponInstance = GetWeaponInstance(DataInstance))
    {
        IWeaponInstanceInterface::Execute_SetDurability(WeaponInstance, NewDurability);
    }
}
