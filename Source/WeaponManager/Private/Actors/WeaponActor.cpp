// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WeaponActor.h"

#include "Interfaces/WeaponDataInterface.h"
#include "Interfaces/WeaponInstanceInterface.h"
#include "Net/UnrealNetwork.h"

const FName AWeaponActor::RootSceneName(TEXT("RootScene"));
const FName AWeaponActor::StaticMeshName(TEXT("StaticMesh"));
const FName AWeaponActor::SkeletalMeshName(TEXT("SkeletalMesh"));

AWeaponActor::AWeaponActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bReplicates = true;

    /* RootScene */

    RootScene = CreateDefaultSubobject<USceneComponent>(RootSceneName);
    SetRootComponent(RootScene);

    /* SkeletalMesh */

    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(SkeletalMeshName);
    GetSkeletalMesh()->SetupAttachment(GetRootScene());
    GetSkeletalMesh()->SetCollisionProfileName("NoCollision");

    /* StaticMesh */

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(StaticMeshName);
    GetStaticMesh()->SetupAttachment(GetRootScene());
    GetStaticMesh()->SetCollisionProfileName("NoCollision");
}

void AWeaponActor::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ThisClass, Instance);
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

    if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, Data))
    {
        ApplyWeaponData();
    }
}
#endif

void AWeaponActor::SetWeaponInstance_Implementation(const TScriptInterface<IWeaponInstanceInterface>& NewWeaponInstance)
{
    TScriptInterface<IWeaponInstanceInterface> OldWeaponInstance = Instance;
    Instance = NewWeaponInstance;

    OnInstanceChanged(OldWeaponInstance, Instance);
}

void AWeaponActor::ApplyWeaponData()
{
    if (Data)
    {
        TSoftObjectPtr<USkeletalMesh> SkeletalMeshAsset = IWeaponDataInterface::Execute_GetSkeletalMesh(Data.GetObject());
        TSoftObjectPtr<UStaticMesh> StaticMeshAsset = IWeaponDataInterface::Execute_GetStaticMesh(Data.GetObject());

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

void AWeaponActor::OnInstanceChanged(const TScriptInterface<IWeaponInstanceInterface>& OldInstance,
    const TScriptInterface<IWeaponInstanceInterface>& NewInstance)
{
    if (NewInstance)
    {
        Data = IWeaponInstanceInterface::Execute_GetData(Instance.GetObject());
    }

    ApplyWeaponData();
}

void AWeaponActor::OnRep_Instance(TScriptInterface<IWeaponInstanceInterface> OldInstance)
{
    OnInstanceChanged(OldInstance, Instance);
}
