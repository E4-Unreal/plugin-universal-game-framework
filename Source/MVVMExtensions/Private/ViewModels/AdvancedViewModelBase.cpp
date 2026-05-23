// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewModels/AdvancedViewModelBase.h"

void UAdvancedViewModelBase::SetModel(UObject* NewModel)
{
    TArray<UObject*> NewModels = { NewModel };
    SetModels(NewModels);
}

void UAdvancedViewModelBase::SetModels(const TArray<UObject*>& NewModels)
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

void UAdvancedViewModelBase::Refresh()
{
    if (!Models.IsEmpty())
    {
        OnRefresh();
    }
}

void UAdvancedViewModelBase::BindModel(UObject* NewModel)
{
    if (NewModel)
    {
        OnBindModel(NewModel);
    }
}

void UAdvancedViewModelBase::UnbindModel(UObject* OldModel)
{
    if (OldModel)
    {
        OnUnbindModel(OldModel);
    }
}

void UAdvancedViewModelBase::OnRefresh_Implementation()
{
}

void UAdvancedViewModelBase::OnBindModel_Implementation(UObject* NewModel)
{
}

void UAdvancedViewModelBase::OnUnbindModel_Implementation(UObject* OldModel)
{
}
