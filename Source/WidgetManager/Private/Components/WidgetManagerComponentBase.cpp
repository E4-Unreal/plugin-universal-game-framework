// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WidgetManagerComponentBase.h"

#include "Blueprint/UserWidget.h"
#include "FunctionLibraries/WidgetManagerFunctionLibrary.h"

UWidgetManagerComponentBase::UWidgetManagerComponentBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UWidgetManagerComponentBase::BeginPlay()
{
    Super::BeginPlay();

    CreateWidgets();
    ShowStartupWidgets();
}

void UWidgetManagerComponentBase::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    DestroyWidgets();

    Super::OnComponentDestroyed(bDestroyingHierarchy);
}

UUserWidget* UWidgetManagerComponentBase::GetWidgetByClass(TSubclassOf<UUserWidget> WidgetClass) const
{
    return WidgetMap.FindRef(WidgetClass).Get();
}

UUserWidget* UWidgetManagerComponentBase::GetOrCreateWidgetByClass(TSubclassOf<UUserWidget> WidgetClass)
{
    UUserWidget* Widget = GetWidgetByClass(WidgetClass);

    return Widget ? Widget : CreateWidgetByClass(WidgetClass);
}

APlayerController* UWidgetManagerComponentBase::GetOwningPlayerController() const
{
    UClass* OwnerClass = GetOwner()->GetClass();
    APlayerController* OwningPlayerController = nullptr;
    if (OwnerClass->IsChildOf<APlayerController>())
    {
        OwningPlayerController = Cast<APlayerController>(GetOwner());
    }
    else if (OwnerClass->IsChildOf<APawn>())
    {
        APawn* OwningPawn = Cast<APawn>(GetOwner());
        OwningPlayerController = Cast<APlayerController>(OwningPawn->GetController());
    }
    else if (OwnerClass->IsChildOf<AGameModeBase>())
    {
        OwningPlayerController = GetWorld()->GetFirstPlayerController();
    }

    if (!OwningPlayerController->IsLocalController()) OwningPlayerController = nullptr;

    return OwningPlayerController;
}

UUserWidget* UWidgetManagerComponentBase::CreateWidgetByClass(TSubclassOf<UUserWidget> WidgetClass)
{
    if (UUserWidget* Widget = UWidgetManagerFunctionLibrary::CreateWidgetByClass(GetOwningPlayerController(), WidgetClass))
    {
        WidgetMap.Emplace(WidgetClass, Widget);

        return Widget;
    }

    return nullptr;
}

bool UWidgetManagerComponentBase::ShowWidgetByClass(TSubclassOf<UUserWidget> WidgetClass)
{
    UUserWidget* Widget = GetOrCreateWidgetByClass(WidgetClass);

    return UWidgetManagerFunctionLibrary::ShowWidget(Widget);
}

bool UWidgetManagerComponentBase::HideWidgetByClass(TSubclassOf<UUserWidget> WidgetClass)
{
    UUserWidget* Widget = GetWidgetByClass(WidgetClass);

    return UWidgetManagerFunctionLibrary::HideWidget(Widget);
}

void UWidgetManagerComponentBase::ToggleWidgetByClass(TSubclassOf<UUserWidget> WidgetClass)
{
    UUserWidget* Widget = GetOrCreateWidgetByClass(WidgetClass);

    UWidgetManagerFunctionLibrary::ToggleWidget(Widget);
}

void UWidgetManagerComponentBase::DestroyWidgetByClass(TSubclassOf<UUserWidget> WidgetClass)
{
    UWidgetManagerFunctionLibrary::DestroyWidgetByClass(WidgetMap, WidgetClass);
}

void UWidgetManagerComponentBase::CreateWidgets()
{
    CreateStartupWidgets();
}

void UWidgetManagerComponentBase::DestroyWidgets()
{
    DestroyStartupWidgets();
}

void UWidgetManagerComponentBase::CreateStartupWidgets()
{
    if (!StartupWidgets.IsEmpty()) return;

    StartupWidgets = UWidgetManagerFunctionLibrary::CreateWidgetsByClasses(GetOwningPlayerController(), StartupWidgetClasses.Array());
}

void UWidgetManagerComponentBase::DestroyStartupWidgets()
{
    UWidgetManagerFunctionLibrary::DestroyWidgets(StartupWidgets);
}

void UWidgetManagerComponentBase::ShowStartupWidgets()
{
    UWidgetManagerFunctionLibrary::ShowWidgets(StartupWidgets);
}

void UWidgetManagerComponentBase::HideStartupWidgets()
{
    UWidgetManagerFunctionLibrary::HideWidgets(StartupWidgets);
}

void UWidgetManagerComponentBase::ToggleStartupWidgets()
{
    UWidgetManagerFunctionLibrary::ToggleWidgets(StartupWidgets);
}
