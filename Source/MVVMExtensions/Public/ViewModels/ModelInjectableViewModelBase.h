// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Interfaces/ModelInjectableInterface.h"
#include "ModelInjectableViewModelBase.generated.h"

/**
 *
 */
UCLASS()
class MVVMEXTENSIONS_API UModelInjectableViewModelBase : public UMVVMViewModelBase, public IModelInjectableInterface
{
    GENERATED_BODY()

public:
    //~ Begin IModelInjectableInterface Interface
    virtual void SetModel_Implementation(UObject* NewModel) override { }
    //~ End IModelInjectableInterface Interface
};
