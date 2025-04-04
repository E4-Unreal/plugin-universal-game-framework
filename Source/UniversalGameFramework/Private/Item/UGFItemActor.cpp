// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/UGFItemActor.h"

#include "Components/SphereComponent.h"
#include "Components/UGFInventoryComponent.h"

AUGFItemActor::AUGFItemActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    OverlapSphere = CreateDefaultSubobject<USphereComponent>(FName("OverlapSphere"));
    SetRootComponent(OverlapSphere);
    DisplayMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("DisplayMesh"));
    DisplayMesh->SetupAttachment(RootComponent);
}

void AUGFItemActor::SetItem_Implementation(const FUGFItem& InItem)
{
    Items.Reset();
    Items.Emplace(InItem);
}

void AUGFItemActor::SetItems_Implementation(const TArray<FUGFItem>& InItems)
{
    Items = InItems;
}

void AUGFItemActor::BeginPlay()
{
    Super::BeginPlay();

    GetOverlapSphere()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapSphereBeginOverlap);
}

void AUGFItemActor::OnOverlapSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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
