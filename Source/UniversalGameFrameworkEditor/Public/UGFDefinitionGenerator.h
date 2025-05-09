// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefinitionGenerator.h"
#include "UGFDefinitionGenerator.generated.h"

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORKEDITOR_API UUGFDefinitionGenerator : public UDefinitionGenerator
{
    GENERATED_BODY()

protected:
    virtual void OnUpdateDefinition(UDefinitionBase* Definition, FTableRowBase* Row) override;
};
