// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "View/MVVMViewModelContextResolver.h"
#include "ModelInjectingResolver.generated.h"

UCLASS(Abstract, EditInlineNew, DefaultToInstanced, CollapseCategories)
class WIDGETMANAGER_API UModelProviderBase : public UObject
{
    GENERATED_BODY()

public:
    virtual UObject* GetModel(const UUserWidget* UserWidget) { return nullptr; }
};

UCLASS(DisplayName = "GameInstance")
class WIDGETMANAGER_API UGameInstanceModelProvider : public UModelProviderBase
{
    GENERATED_BODY()

public:
    virtual UObject* GetModel(const UUserWidget* UserWidget) override;
};

UCLASS(DisplayName = "EngineSubsystem")
class WIDGETMANAGER_API UEngineSubsystemModelProvider : public UModelProviderBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, Category = "Config")
    TSubclassOf<UEngineSubsystem> SubsystemClass;

public:
    virtual UObject* GetModel(const UUserWidget* UserWidget) override;
};

UCLASS(DisplayName = "GameInstanceSubsystem")
class WIDGETMANAGER_API UGameInstanceSubsystemModelProvider : public UModelProviderBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, Category = "Config")
    TSubclassOf<UGameInstanceSubsystem> SubsystemClass;

public:
    virtual UObject* GetModel(const UUserWidget* UserWidget) override;
};

UCLASS(DisplayName = "WorldSubsystem")
class WIDGETMANAGER_API UWorldSubsystemModelProvider : public UModelProviderBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, Category = "Config")
    TSubclassOf<UWorldSubsystem> SubsystemClass;

public:
    virtual UObject* GetModel(const UUserWidget* UserWidget) override;
};

UCLASS(DisplayName = "LocalPlayerSubsystem")
class WIDGETMANAGER_API ULocalPlayerSubsystemModelProvider : public UModelProviderBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, Category = "Config")
    TSubclassOf<ULocalPlayerSubsystem> SubsystemClass;

public:
    virtual UObject* GetModel(const UUserWidget* UserWidget) override;
};

UCLASS(DisplayName = "ActorComponent")
class WIDGETMANAGER_API UActorComponentModelProvider : public UModelProviderBase
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, Category = "Config")
    bool bPlayerController;

    UPROPERTY(EditAnywhere, Category = "Config", meta = (AllowAbstract = true))
    TSubclassOf<UInterface> InterfaceClass;

    UPROPERTY(EditAnywhere, Category = "Config")
    TSubclassOf<UActorComponent> ComponentClass;

public:
    virtual UObject* GetModel(const UUserWidget* UserWidget) override;
};

/**
 *
 */
UCLASS()
class WIDGETMANAGER_API UModelInjectingResolver : public UMVVMViewModelContextResolver
{
    GENERATED_BODY()

protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config")
    TObjectPtr<UModelProviderBase> ModelProvider;

public:
    virtual UObject* CreateInstance(const UClass* ExpectedType, const UUserWidget* UserWidget, const UMVVMView* View) const override;

#if WITH_EDITOR
    virtual bool DoesSupportViewModelClass(const UClass* Class) const override;
#endif
};
