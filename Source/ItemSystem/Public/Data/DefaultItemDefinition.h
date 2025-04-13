// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDefinition.h"
#include "DefaultItemDefinition.generated.h"

/**
 *
 */
UCLASS()
class ITEMSYSTEM_API UDefaultItemDefinition : public UItemDefinition
{
    GENERATED_BODY()

protected:
    virtual void UpdateItemConfigs(FTableRowBase* TableRow) override;

    void UpdateActorItemConfig(FTableRowBase* TableRow);
};
