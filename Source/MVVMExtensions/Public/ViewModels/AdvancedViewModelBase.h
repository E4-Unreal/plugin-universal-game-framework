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

private:
    TArray<TWeakObjectPtr<UObject>> Models;

public:
    UFUNCTION(BlueprintCallable)
    void SetModel(UObject* NewModel);

    UFUNCTION(BlueprintCallable)
    void SetModels(const TArray<UObject*>& NewModels);

    UFUNCTION(BlueprintCallable)
    void Refresh();

    UFUNCTION(BlueprintCallable)
    void BindModel(UObject* NewModel);

    UFUNCTION(BlueprintCallable)
    void UnbindModel(UObject* OldModel);

    /* Query */

    template<class T UE_REQUIRES(TPointerIsConvertibleFromTo<T, UInterface>::Value)>
    UObject* GetModelByInterface() const
    {
        return GetModelByInterface(T::StaticClass());
    }

    UFUNCTION(BlueprintPure)
    UObject* GetModelByInterface(TSubclassOf<UInterface> InterfaceClass) const
    {
        for (const auto& Model : Models)
        {
            if (Model.IsValid() && Model.Get()->GetClass()->ImplementsInterface(InterfaceClass))
            {
                return Model.Get();
            }
        }

        return nullptr;
    }

protected:
    UFUNCTION(BlueprintNativeEvent)
    void OnRefresh();

    UFUNCTION(BlueprintNativeEvent)
    void OnBindModel(UObject* NewModel);

    UFUNCTION(BlueprintNativeEvent)
    void OnUnbindModel(UObject* OldModel);
};
