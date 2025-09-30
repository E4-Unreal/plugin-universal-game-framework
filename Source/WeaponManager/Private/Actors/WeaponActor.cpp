// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/WeaponActor.h"

#include "FunctionLibraries/DataManagerFunctionLibrary.h"
#include "FunctionLibraries/MeshManagerFunctionLibrary.h"
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

void AWeaponActor::SetInstance_Implementation(UObject* NewInstance)
{
    UObject* OldWeaponInstance = Instance;
    Instance = NewInstance;

    OnInstanceChanged(OldWeaponInstance, Instance);
}

void AWeaponActor::ApplyWeaponData()
{
    if (auto MeshData = UMeshManagerFunctionLibrary::GetMeshData(Data))
    {
        auto SkeletalMeshAsset = UMeshManagerFunctionLibrary::GetSkeletalMesh(MeshData);
        auto StaticMeshAsset = UMeshManagerFunctionLibrary::GetStaticMesh(MeshData);

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

void AWeaponActor::OnInstanceChanged(UObject* OldInstance, UObject* NewInstance)
{
    Data = NewInstance ? UDataManagerFunctionLibrary::GetData(NewInstance) : nullptr;

    ApplyWeaponData();
}

void AWeaponActor::OnRep_Instance(UObject* OldInstance)
{
    OnInstanceChanged(OldInstance, Instance);
}
