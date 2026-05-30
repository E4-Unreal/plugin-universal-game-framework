// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "AdvancedViewModel.generated.h"

/**
 *
 */
UCLASS()
class WIDGETMANAGER_API UAdvancedViewModel : public UMVVMViewModelBase
{
    GENERATED_BODY()

private:
    TArray<TWeakObjectPtr<UObject>> Models;

public:
    /* ThisClass */

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

    template<class T UE_REQUIRES(TPointerIsConvertibleFromTo<T, UObject>::Value)>
    T* GetModelByClass() const
    {
        return Cast<T>(GetModelByClass(T::StaticClass()));
    }

    UFUNCTION(BlueprintPure, meta = (DeterminesOutputType = ObjectClass))
    UObject* GetModelByClass(TSubclassOf<UObject> ObjectClass) const
    {
        for (const auto& Model : Models)
        {
            if (Model.IsValid() && Model.Get()->IsA(ObjectClass))
            {
                return Model.Get();
            }
        }

        return nullptr;
    }

    UFUNCTION(BlueprintCallable)
    virtual void ShowWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void HideWidget(TSubclassOf<UUserWidget> WidgetClass);

    UFUNCTION(BlueprintCallable)
    virtual void ToggleWidget(TSubclassOf<UUserWidget> WidgetClass);

protected:
    UFUNCTION(BlueprintNativeEvent)
    void OnRefresh();
    virtual void OnRefresh_Implementation();

    UFUNCTION(BlueprintNativeEvent)
    void OnBindModel(UObject* NewModel);
    virtual void OnBindModel_Implementation(UObject* NewModel);

    UFUNCTION(BlueprintNativeEvent)
    void OnUnbindModel(UObject* OldModel);
    virtual void OnUnbindModel_Implementation(UObject* OldModel);
};
