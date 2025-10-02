// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/MeshDataFunctionLibrary.h"

#include "Data/DataDefinitionBase.h"
#include "Interfaces/MeshDataInterface.h"

bool UMeshDataFunctionLibrary::HasMeshData(UDataDefinitionBase* Definition)
{
    return GetMeshData(Definition) != nullptr;
}

TSoftObjectPtr<UStaticMesh> UMeshDataFunctionLibrary::GetStaticMesh(UDataDefinitionBase* Definition)
{
    auto MeshData = GetMeshData(Definition);

    return MeshData ? IMeshDataInterface::Execute_GetStaticMesh(MeshData) : nullptr;
}

TSoftObjectPtr<USkeletalMesh> UMeshDataFunctionLibrary::GetSkeletalMesh(UDataDefinitionBase* Definition)
{
    auto MeshData = GetMeshData(Definition);

    return MeshData ? IMeshDataInterface::Execute_GetSkeletalMesh(MeshData) : nullptr;
}

TSoftObjectPtr<UMaterialInterface> UMeshDataFunctionLibrary::GetMaterial(UDataDefinitionBase* Definition)
{
    auto MeshData = GetMeshData(Definition);

    return MeshData ? IMeshDataInterface::Execute_GetMaterial(MeshData) : nullptr;
}

TSoftClassPtr<UAnimInstance> UMeshDataFunctionLibrary::GetAnimationClass(UDataDefinitionBase* Definition)
{
    auto MeshData = GetMeshData(Definition);

    return MeshData ? IMeshDataInterface::Execute_GetAnimationClass(MeshData) : nullptr;
}

UDataAsset* UMeshDataFunctionLibrary::GetMeshData(UDataDefinitionBase* Definition)
{
    return Definition ? Definition->GetDataByInterface<UMeshDataInterface>() : nullptr;
}
