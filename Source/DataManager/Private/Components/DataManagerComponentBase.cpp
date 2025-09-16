// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DataManagerComponentBase.h"

UDataManagerComponentBase::UDataManagerComponentBase()
{
    bWantsInitializeComponent = true;
}

void UDataManagerComponentBase::InitializeComponent()
{
    Super::InitializeComponent();

    Refresh();
}

void UDataManagerComponentBase::Refresh_Implementation()
{
}
