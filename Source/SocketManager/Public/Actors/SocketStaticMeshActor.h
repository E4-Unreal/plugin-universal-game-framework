// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SocketMeshActor.h"
#include "SocketStaticMeshActor.generated.h"

UCLASS()
class SOCKETMANAGER_API ASocketStaticMeshActor : public ASocketMeshActor
{
    GENERATED_BODY()

public:
    ASocketStaticMeshActor(const FObjectInitializer& ObjectInitializer);

    virtual void SetMesh(UStreamableRenderAsset* NewMesh) override;

    UFUNCTION(BlueprintCallable)
    void SetStaticMesh(UStaticMesh* NewMesh);
};
