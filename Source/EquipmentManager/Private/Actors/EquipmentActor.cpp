// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EquipmentActor.h"
#include "Logging.h"
#include "Interfaces/EquipmentDataInterface.h"

const FName AEquipmentActor::DefaultSceneName(TEXT("DefaultScene"));
const FName AEquipmentActor::StaticMeshName(TEXT("StaticMesh"));
const FName AEquipmentActor::SkeletalMeshName(TEXT("SkeletalMesh"));

AEquipmentActor::AEquipmentActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* DefaultScene */

    DefaultScene = CreateOptionalDefaultSubobject<USceneComponent>(DefaultSceneName);
    SetRootComponent(DefaultScene);

    /* StaticMesh */

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(StaticMeshName);
    GetStaticMesh()->SetupAttachment(GetRootComponent());

    /* SkeletalMesh */

    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(SkeletalMeshName);
    GetSkeletonMesh()->SetupAttachment(GetRootComponent());
}

void AEquipmentActor::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    InitializeByData();
}

#if WITH_EDITOR
void AEquipmentActor::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = PropertyChangedEvent.Property != nullptr ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, EquipmentData))
    {
        InitializeByData();
    }
}
#endif


void AEquipmentActor::SetEquipmentData_Implementation(UDataAsset* NewEquipmentData)
{
    EquipmentData = NewEquipmentData;
    InitializeByData();
}

void AEquipmentActor::Equip_Implementation(AActor* NewOwner)
{
    LOG(Log, TEXT("%s equip %s"), *NewOwner->GetName(), *GetName())
    SetOwner(NewOwner);
}

void AEquipmentActor::UnEquip_Implementation()
{
    LOG(Log, TEXT("%s unequip %s"), *Owner->GetName(), *GetName())
    SetOwner(nullptr);
}

void AEquipmentActor::InitializeByData()
{
    USkeletalMesh* NewSkeletalMesh = nullptr;
    UStaticMesh* NewStaticMesh = nullptr;

    if (EquipmentData && EquipmentData->Implements<UEquipmentDataInterface>())
    {
        TSoftObjectPtr<USkeletalMesh> SkeletalMeshToLoad = IEquipmentDataInterface::Execute_GetSkeletalMesh(EquipmentData);
        TSoftObjectPtr<UStaticMesh> StaticMeshToLoad = IEquipmentDataInterface::Execute_GetStaticMesh(EquipmentData);

        if (!SkeletalMeshToLoad.IsNull())
        {
            NewSkeletalMesh = SkeletalMeshToLoad.LoadSynchronous();
        }
        else if (!StaticMeshToLoad.IsNull())
        {
            NewStaticMesh = StaticMeshToLoad.LoadSynchronous();
        }
    }

    GetSkeletonMesh()->SetSkeletalMesh(NewSkeletalMesh);
    GetStaticMesh()->SetStaticMesh(NewStaticMesh);
}
