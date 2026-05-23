// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "AdvancedViewModelBase.generated.h"

/**
 *
 */
UCLASS()
class MVVMEXTENSIONS_API UAdvancedViewModelBase : public UMVVMViewModelBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    TObjectPtr<UObject> Model;

public:
    UFUNCTION(BlueprintCallable)
    void SetModel(UObject* NewModel);

    UFUNCTION(BlueprintCallable)
    void Refresh();

    UFUNCTION(BlueprintCallable)
    void BindModel(UObject* NewModel);

    UFUNCTION(BlueprintCallable)
    void UnbindModel(UObject* OldModel);

protected:
    UFUNCTION(BlueprintNativeEvent)
    void OnRefresh();

    UFUNCTION(BlueprintNativeEvent)
    void OnBindModel(UObject* NewModel);

    UFUNCTION(BlueprintNativeEvent)
    void OnUnbindModel(UObject* OldModel);
};
