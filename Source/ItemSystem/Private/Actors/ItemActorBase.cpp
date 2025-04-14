// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ItemActorBase.h"

#include "Components/SphereComponent.h"
#include "Data/ItemDefinition.h"
#include "Types/ActorItemData.h"
#include "Logging.h"

FName AItemActorBase::DisplayMeshName(TEXT("DisplayMesh"));
FName AItemActorBase::OverlapSphereName(TEXT("OverlapSphere"));

AItemActorBase::AItemActorBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    /* OverlapSphere */
    OverlapSphere = CreateDefaultSubobject<USphereComponent>(OverlapSphereName);
    SetRootComponent(OverlapSphere);

    /* DisplayMesh */
    DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(DisplayMeshName);
    DisplayMesh->SetupAttachment(OverlapSphere);
    DisplayMesh->SetSimulatePhysics(true);

    ItemContainer.Quantity = 1;
}

void AItemActorBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    Refresh();
}

void AItemActorBase::BeginPlay()
{
    Super::BeginPlay();

    if (ItemContainer.IsNotValid())
    {
        Destroy();
        return;
    }

    // Bind OverlapSphere Events
    OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapSphereBeginOverlap);
    OverlapSphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapSphereEndOverlap);
}

#if WITH_EDITOR
void AItemActorBase::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    // 변경된 프로퍼티의 이름을 가져온다.
    FName PropertyName = PropertyChangedEvent.Property != nullptr ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(FItemContainer, ID) || PropertyName == GET_MEMBER_NAME_CHECKED(FItemContainer, ItemDefinition))
    {
        Refresh();
    }
}
#endif

void AItemActorBase::Refresh()
{
    if (UItemDefinition* ItemDefinition = ItemContainer.GetItemDefinition())
    {
        if (ItemDefinition->HasData<FActorItemData>())
        {
            const auto& ActorItemData = ItemDefinition->GetData<FActorItemData>();
            UStaticMesh* StaticMesh = ActorItemData.StaticMesh.LoadSynchronous();
            if (StaticMesh == nullptr) StaticMesh = DefaultStaticMesh;
            DisplayMesh->SetStaticMesh(StaticMesh);

            return;
        }
    }

    DisplayMesh->SetStaticMesh(DefaultStaticMesh);
}

void AItemActorBase::OnOverlapSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    LOG(Log, TEXT(""))
}

void AItemActorBase::OnOverlapSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    LOG(Log, TEXT(""))
}
