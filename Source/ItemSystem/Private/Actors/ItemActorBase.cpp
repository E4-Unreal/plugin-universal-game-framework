// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ItemActorBase.h"

FName AItemActorBase::DisplayMeshName(TEXT("DisplayMesh"));

AItemActorBase::AItemActorBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* DisplayMesh */
    DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(DisplayMeshName);
}
