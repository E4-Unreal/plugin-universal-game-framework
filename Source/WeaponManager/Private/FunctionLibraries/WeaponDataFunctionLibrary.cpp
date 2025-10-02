// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/WeaponDataFunctionLibrary.h"

#include "Data/DataDefinitionBase.h"
#include "Data/DataInstanceBase.h"
#include "FunctionLibraries/DataManagerFunctionLibrary.h"
#include "Interfaces/WeaponDataInterface.h"
#include "Interfaces/WeaponInstanceInterface.h"

bool UWeaponDataFunctionLibrary::HasWeaponData(UDataDefinitionBase* Definition)
{
    return GetWeaponData(Definition) != nullptr;
}

TSubclassOf<AActor> UWeaponDataFunctionLibrary::GetActorClass(UDataDefinitionBase* Definition)
{
    auto WeaponData = GetWeaponData(Definition);

    return WeaponData ? IWeaponDataInterface::Execute_GetActorClass(WeaponData) : nullptr;
}

FGameplayTag UWeaponDataFunctionLibrary::GetSlotType(UDataDefinitionBase* Definition)
{
    auto WeaponData = GetWeaponData(Definition);

    return WeaponData ? IWeaponDataInterface::Execute_GetSlotType(WeaponData) : FGameplayTag::EmptyTag;
}

FName UWeaponDataFunctionLibrary::GetActiveSocketName(UDataDefinitionBase* Definition)
{
    auto WeaponData = GetWeaponData(Definition);

    return WeaponData ? IWeaponDataInterface::Execute_GetActiveSocketName(WeaponData) : NAME_None;
}

FName UWeaponDataFunctionLibrary::GetInActiveSocketName(UDataDefinitionBase* Definition)
{
    auto WeaponData = GetWeaponData(Definition);

    return WeaponData ? IWeaponDataInterface::Execute_GetInActiveSocketName(WeaponData) : NAME_None;
}

float UWeaponDataFunctionLibrary::GetMaxDurability(UDataDefinitionBase* Definition)
{
    auto WeaponData = GetWeaponData(Definition);

    return WeaponData ? IWeaponDataInterface::Execute_GetMaxDurability(WeaponData) : 0;
}

UDataInstanceBase* UWeaponDataFunctionLibrary::CreateItemInstance(UDataDefinitionBase* Definition)
{
    if (Definition)
    {
        auto DataInstance = UDataManagerFunctionLibrary::CreateDataInstance(Definition);
        auto WeaponInstance = GetWeaponInstance(DataInstance);

        return WeaponInstance ? DataInstance : nullptr;
    }

    return nullptr;
}

bool UWeaponDataFunctionLibrary::HasWeaponInstance(UDataInstanceBase* Instance)
{
    return GetWeaponInstance(Instance) != nullptr;
}

AActor* UWeaponDataFunctionLibrary::GetActor(UDataInstanceBase* Instance)
{
    auto WeaponInstance = GetWeaponInstance(Instance);

    return WeaponInstance ? IWeaponInstanceInterface::Execute_GetActor(WeaponInstance) : nullptr;
}

void UWeaponDataFunctionLibrary::SetActor(UDataInstanceBase* Instance, AActor* NewActor)
{
    if (auto WeaponInstance = GetWeaponInstance(Instance))
    {
        IWeaponInstanceInterface::Execute_SetActor(WeaponInstance, NewActor);
    }
}

float UWeaponDataFunctionLibrary::GetDurability(UDataInstanceBase* Instance)
{
    auto WeaponInstance = GetWeaponInstance(Instance);

    return WeaponInstance ? IWeaponInstanceInterface::Execute_GetDurability(WeaponInstance) : 0;
}

void UWeaponDataFunctionLibrary::SetDurability(UDataInstanceBase* Instance, float NewDurability)
{
    if (auto WeaponInstance = GetWeaponInstance(Instance))
    {
        IWeaponInstanceInterface::Execute_SetDurability(WeaponInstance, NewDurability);
    }
}

UDataAsset* UWeaponDataFunctionLibrary::GetWeaponData(UDataDefinitionBase* Definition)
{
    return UDataManagerFunctionLibrary::GetDataByInterface<UWeaponDataInterface>(Definition);
}

UObject* UWeaponDataFunctionLibrary::GetWeaponInstance(UDataInstanceBase* Instance)
{
    return UDataManagerFunctionLibrary::GetInstanceDataByInterface<UWeaponInstanceInterface>(Instance);
}
