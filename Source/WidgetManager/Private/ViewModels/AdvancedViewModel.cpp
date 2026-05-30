// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewModels/AdvancedViewModel.h"

#include "Subsystems/WidgetManagerSubsystem.h"

void UAdvancedViewModel::SetModel(UObject* NewModel)
{
    TArray<UObject*> NewModels = { NewModel };
    SetModels(NewModels);
}

void UAdvancedViewModel::SetModels(const TArray<UObject*>& NewModels)
{
    // Unbind Old Models
    for (const auto& OldModel : Models)
    {
        if (OldModel.IsValid())
        {
            UnbindModel(OldModel.Get());
        }
    }

    // Change Models
    Models.Empty(NewModels.Num());
    Models.Append(NewModels);

    // Bind New Models
    for (const auto& NewModel : NewModels)
    {
        if (NewModel)
        {
            BindModel(NewModel);
        }
    }

    // Initialize
    Refresh();
}

void UAdvancedViewModel::Refresh()
{
    if (!Models.IsEmpty())
    {
        OnRefresh();
    }
}

void UAdvancedViewModel::BindModel(UObject* NewModel)
{
    if (NewModel)
    {
        OnBindModel(NewModel);
    }
}

void UAdvancedViewModel::UnbindModel(UObject* OldModel)
{
    if (OldModel)
    {
        OnUnbindModel(OldModel);
    }
}

void UAdvancedViewModel::ShowWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (auto Subsystem = UWidgetManagerSubsystem::Get(GetOuter()))
    {
        Subsystem->ShowWidget(WidgetClass);
    }
}

void UAdvancedViewModel::HideWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (auto Subsystem = UWidgetManagerSubsystem::Get(GetOuter()))
    {
        Subsystem->HideWidget(WidgetClass);
    }
}

void UAdvancedViewModel::ToggleWidget(TSubclassOf<UUserWidget> WidgetClass)
{
    if (auto Subsystem = UWidgetManagerSubsystem::Get(GetOuter()))
    {
        Subsystem->ToggleWidget(WidgetClass);
    }
}

void UAdvancedViewModel::OnRefresh_Implementation()
{
}

void UAdvancedViewModel::OnBindModel_Implementation(UObject* NewModel)
{
}

void UAdvancedViewModel::OnUnbindModel_Implementation(UObject* OldModel)
{
}
