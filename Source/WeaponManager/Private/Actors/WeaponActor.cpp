// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WeaponActor.h"

#include "Interfaces/WeaponDataInterface.h"

const FName AWeaponActor::RootSceneName(TEXT("RootScene"));
const FName AWeaponActor::StaticMeshName(TEXT("StaticMesh"));
const FName AWeaponActor::SkeletalMeshName(TEXT("SkeletalMesh"));

AWeaponActor::AWeaponActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* RootScene */

    RootScene = CreateDefaultSubobject<USceneComponent>(RootSceneName);
    SetRootComponent(RootScene);

    /* SkeletalMesh */

    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(SkeletalMeshName);
    GetSkeletalMesh()->SetupAttachment(GetRootScene());

    /* StaticMesh */

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(StaticMeshName);
    GetStaticMesh()->SetupAttachment(GetRootScene());
}

void AWeaponActor::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    ApplyWeaponData();
}

#if WITH_EDITOR
void AWeaponActor::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = PropertyChangedEvent.Property != nullptr ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, WeaponData))
    {
        ApplyWeaponData();
    }
}
#endif

void AWeaponActor::ApplyWeaponData()
{
    if (WeaponData)
    {
        TSoftObjectPtr<USkeletalMesh> SkeletalMeshAsset = IWeaponDataInterface::Execute_GetSkeletalMesh(WeaponData.GetObject());
        TSoftObjectPtr<UStaticMesh> StaticMeshAsset = IWeaponDataInterface::Execute_GetStaticMesh(WeaponData.GetObject());

        if (!SkeletalMeshAsset.IsNull())
        {
            GetSkeletalMesh()->SetSkeletalMesh(SkeletalMeshAsset.LoadSynchronous());
            GetStaticMesh()->SetStaticMesh(nullptr);
        }
        else if (!StaticMeshAsset.IsNull())
        {
            GetSkeletalMesh()->SetSkeletalMesh(nullptr);
            GetStaticMesh()->SetStaticMesh(StaticMeshAsset.LoadSynchronous());
        }
    }
}
