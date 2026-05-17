// Fill out your copyright notice in the Description page of Project Settings.


#include "Resolvers/ModelInjectingResolver.h"

#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/ModelInjectableInterface.h"

UObject* UGameInstanceModelProvider::GetModel(const UUserWidget* UserWidget)
{
    if (UserWidget)
    {
        if (UWorld* World = UserWidget->GetWorld())
        {
            return World->GetGameInstance();
        }
    }

    return nullptr;
}

UObject* UEngineSubsystemModelProvider::GetModel(const UUserWidget* UserWidget)
{
    if (SubsystemClass && GEngine)
    {
        return GEngine->GetEngineSubsystemBase(SubsystemClass);
    }
    return nullptr;
}

UObject* UGameInstanceSubsystemModelProvider::GetModel(const UUserWidget* UserWidget)
{
    if (UserWidget && SubsystemClass)
    {
        if (UWorld* World = UserWidget->GetWorld())
        {
            if (const UGameInstance* GameInstance = World->GetGameInstance())
            {
                return GameInstance->GetSubsystemBase(SubsystemClass);
            }
        }
    }

    return nullptr;
}

UObject* UWorldSubsystemModelProvider::GetModel(const UUserWidget* UserWidget)
{
    if (UserWidget && SubsystemClass)
    {
        if (UWorld* World = UserWidget->GetWorld())
        {
            return World->GetSubsystemBase(SubsystemClass);
        }
    }
    return nullptr;
}

UObject* ULocalPlayerSubsystemModelProvider::GetModel(const UUserWidget* UserWidget)
{
    if (UserWidget && SubsystemClass)
    {
        if (const ULocalPlayer* LocalPlayer = UserWidget->GetOwningLocalPlayer())
        {
            return LocalPlayer->GetSubsystemBase(SubsystemClass);
        }
    }

    return nullptr;
}

UObject* UModelInjectingResolver::CreateInstance(const UClass* ExpectedType, const UUserWidget* UserWidget, const UMVVMView* View) const
{
    // 블루프린트에서 구현된 함수 우선 호출
    UObject* OverrideInstance = K2_CreateInstance(ExpectedType, UserWidget).GetObject();
    if (OverrideInstance != nullptr) return OverrideInstance;

    // ViewModel 생성 후 Model 주입
    if (ExpectedType && ExpectedType->ImplementsInterface(UModelInjectableInterface::StaticClass()) && ModelProvider)
    {
        if (UObject* ModelToInject = ModelProvider->GetModel(UserWidget))
        {
            if (UObject* NewViewModel = NewObject<UObject>(GetTransientPackage(), ExpectedType))
            {
                IModelInjectableInterface::Execute_SetModel(NewViewModel, ModelToInject);

                return NewViewModel;
            }
        }
    }

    return nullptr;
}

#if WITH_EDITOR
bool UModelInjectingResolver::DoesSupportViewModelClass(const UClass* Class) const
{
    if (Super::DoesSupportViewModelClass(Class))
    {
        return Class->ImplementsInterface(UModelInjectableInterface::StaticClass());
    }

    return false;
}
#endif
