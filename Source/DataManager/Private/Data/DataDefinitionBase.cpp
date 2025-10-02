// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataDefinitionBase.h"

#include "Data/DataInstanceBase.h"

UDataDefinitionBase::UDataDefinitionBase()
{
    DataType = "Data";
}

FPrimaryAssetId UDataDefinitionBase::GetPrimaryAssetId() const
{
    return FPrimaryAssetId(DataType, FName(FString::FromInt(ID)));
}

UDataAsset* UDataDefinitionBase::GetDataByInterface(TSubclassOf<UInterface> InterfaceClass) const
{
    return InterfaceClass && GetClass()->ImplementsInterface(InterfaceClass) ? const_cast<ThisClass*>(this) : nullptr;
}

UDataInstanceBase* UDataDefinitionBase::CreateDataInstance() const
{
    if (DataInstanceClass)
    {
        auto NewDataInstance = NewObject<UDataInstanceBase>(GetTransientPackage(), DataInstanceClass);
        NewDataInstance->SetDefinition(const_cast<ThisClass*>(this));

        return NewDataInstance;
    }

    return nullptr;
}
