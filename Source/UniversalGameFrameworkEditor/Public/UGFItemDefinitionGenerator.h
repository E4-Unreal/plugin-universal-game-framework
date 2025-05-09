// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefinitionGenerator.h"
#include "UGFItemDefinitionGenerator.generated.h"

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORKEDITOR_API UUGFItemDefinitionGenerator : public UDefinitionGenerator
{
    GENERATED_BODY()

public:
    UUGFItemDefinitionGenerator();

protected:
    virtual void OnUpdateDefinition(UDefinitionBase* Definition, FDefinitionDataTableRow* Row) override;
};
