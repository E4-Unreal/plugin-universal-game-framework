// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Interfaces/ModelInjectableInterface.h"
#include "AdvancedViewModelBase.generated.h"

/**
 *
 */
UCLASS()
class MVVMEXTENSIONS_API UAdvancedViewModelBase : public UMVVMViewModelBase, public IModelInjectableInterface
{
    GENERATED_BODY()

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    TObjectPtr<UObject> Model;

public:
    //~ Begin IModelInjectableInterface Interface
    virtual void SetModel_Implementation(UObject* NewModel) override { Model = NewModel; }
    //~ End IModelInjectableInterface Interface
};
