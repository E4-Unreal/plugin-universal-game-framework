// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/UGFPickupItem.h"

#include "Components/SphereComponent.h"
#include "Components/UGFInventoryComponent.h"

AUGFPickupItem::AUGFPickupItem(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    OverlapSphere = CreateDefaultSubobject<USphereComponent>(FName("OverlapSphere"));
    SetRootComponent(OverlapSphere);
    DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("DisplayMesh"));
    DisplayMesh->SetupAttachment(RootComponent);
}

void AUGFPickupItem::BeginPlay()
{
    Super::BeginPlay();

    GetOverlapSphere()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapSphereBeginOverlap);
}

void AUGFPickupItem::OnOverlapSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (bAutoPickup)
    {
        if (auto OtherPawn = Cast<APawn>(OtherActor))
        {
            if (auto InventoryComponent = OtherPawn->GetComponentByClass<UUGFInventoryComponent>())
            {
                for (auto Item : Items)
                {
                    int32 Overflow;
                    InventoryComponent->AddItem(Item, Overflow);
                }

                Destroy();
            }
        }
    }
}
