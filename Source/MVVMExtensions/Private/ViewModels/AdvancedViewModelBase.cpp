// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewModels/AdvancedViewModelBase.h"

void UAdvancedViewModelBase::SetModel(UObject* NewModel)
{
    if (Model == NewModel) return;

    UObject* OldModel = Model;
    Model = NewModel;

    UnbindModel(OldModel);
    BindModel(NewModel);

    Refresh();
}

void UAdvancedViewModelBase::Refresh()
{
    if (Model) OnRefresh();
}

void UAdvancedViewModelBase::BindModel(UObject* NewModel)
{
    if (NewModel) OnBindModel(NewModel);
}

void UAdvancedViewModelBase::UnbindModel(UObject* OldModel)
{
    if (OldModel) OnUnbindModel(OldModel);
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
