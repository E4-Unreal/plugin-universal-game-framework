// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/DataManagerSubsystem.h"
#include "UGFDataManagerSubsystem.generated.h"

/**
 *
 */
UCLASS()
class UNIVERSALGAMEFRAMEWORK_API UUGFDataManagerSubsystem : public UDataManagerSubsystem
{
    GENERATED_BODY()

public:
    UUGFDataManagerSubsystem();

protected:
    virtual void OnSaveData_Implementation() override;
    virtual void OnLoadData_Implementation() override;
};
