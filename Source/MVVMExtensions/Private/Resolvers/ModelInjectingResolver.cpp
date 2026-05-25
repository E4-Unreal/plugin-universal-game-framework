// Fill out your copyright notice in the Description page of Project Settings.


#include "Resolvers/ModelInjectingResolver.h"

#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "ViewModels/AdvancedViewModelBase.h"

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

UObject* UActorComponentModelProvider::GetModel(const UUserWidget* UserWidget)
{
    if (UserWidget)
    {
        if (InterfaceClass)
        {
            if (bPlayerController)
            {
                if (APlayerController* PlayerController = UserWidget->GetOwningPlayer())
                {
                    TArray<UActorComponent*> Components = PlayerController->GetComponentsByInterface(InterfaceClass.Get());
                    return Components.Num() > 0 ? Components[0] : nullptr;
                }
            }
            else
            {
                if (APawn* Pawn = UserWidget->GetOwningPlayerPawn())
                {
                    TArray<UActorComponent*> Components = Pawn->GetComponentsByInterface(InterfaceClass.Get());
                    return Components.Num() > 0 ? Components[0] : nullptr;
                }
            }
        }
        else if (ComponentClass)
        {
            if (bPlayerController)
            {
                if (APlayerController* PlayerController = UserWidget->GetOwningPlayer())
                {
                    return PlayerController->GetComponentByClass(ComponentClass);
                }
            }
            else
            {
                if (APawn* Pawn = UserWidget->GetOwningPlayerPawn())
                {
                    return Pawn->GetComponentByClass(ComponentClass);
                }
            }
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
    if (ExpectedType)
    {
        if (auto ViewModel = NewObject<UAdvancedViewModelBase>(GetTransientPackage(), ExpectedType))
        {
            if (ModelProvider)
            {
                if (UObject* ModelToInject = ModelProvider->GetModel(UserWidget))
                {
                    ViewModel->SetModel(ModelToInject);
                }
            }

            return ViewModel;
        }
    }

    return nullptr;
}

#if WITH_EDITOR
bool UModelInjectingResolver::DoesSupportViewModelClass(const UClass* Class) const
{
    if (Super::DoesSupportViewModelClass(Class))
    {
        return Class->IsChildOf(UAdvancedViewModelBase::StaticClass());
    }

    return false;
}
#endif
