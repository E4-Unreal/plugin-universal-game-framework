// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/Builder/UGFCharacterSocketDefinitionBuilder.h"

#include "Data/UGFCharacterSocketDefinition.h"
#include "Types/UGFCharacterSocketDefinitionTableRow.h"

UUGFCharacterSocketDefinitionBuilder::UUGFCharacterSocketDefinitionBuilder()
{
    DefinitionClass = UUGFCharacterSocketDefinition::StaticClass();
    DataName = "UGFCharacterSocket";
}

bool UUGFCharacterSocketDefinitionBuilder::OnUpdateData(UDataDefinitionBase* Definition,
                                                        FDataDefinitionTableRowBase* DataDefinitionTableRow)
{
    bool bDirty = false;

    auto CastedDataDefinition = Cast<UUGFCharacterSocketDefinition>(Definition);
    auto CastedTableRow = static_cast<FUGFCharacterSocketDefinitionTableRow*>(DataDefinitionTableRow);
    if (CastedDataDefinition && CastedTableRow)
    {
        SET_DATA(CastedDataDefinition->SocketType, CastedTableRow->SocketType);
        SET_DATA(CastedDataDefinition->SocketName, CastedTableRow->SocketName);
        SET_DATA(CastedDataDefinition->SocketTypesToHide, CastedTableRow->SocketTypesToHide);
        SET_DATA(CastedDataDefinition->StaticMesh, CastedTableRow->StaticMesh);
        SET_DATA(CastedDataDefinition->SkeletalMesh, CastedTableRow->SkeletalMesh);
        SET_DATA(CastedDataDefinition->ActorClass, CastedTableRow->ActorClass);
    }

    return bDirty;
}
