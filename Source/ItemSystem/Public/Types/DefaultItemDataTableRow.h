// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataTableRow.h"
#include "UObject/Object.h"
#include "DefaultItemDataTableRow.generated.h"

USTRUCT()
struct FDefaultItemDataTableRow : public FItemDataTableRow
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UStaticMesh> StaticMesh;
};
