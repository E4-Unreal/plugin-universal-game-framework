// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/MeshManagerFunctionLibrary.h"

#include "FunctionLibraries/DataManagerFunctionLibrary.h"
#include "Interfaces/MeshDataInterface.h"

UDataAsset* UMeshManagerFunctionLibrary::GetMeshData(UObject* DataObject)
{
    return UDataManagerFunctionLibrary::GetDataByInterface<UMeshDataInterface>(DataObject);
}

TSoftObjectPtr<UStaticMesh> UMeshManagerFunctionLibrary::GetStaticMesh(UObject* DataObject)
{
    auto MeshData = GetMeshData(DataObject);

    return MeshData ? IMeshDataInterface::Execute_GetStaticMesh(MeshData) : nullptr;
}

TSoftObjectPtr<USkeletalMesh> UMeshManagerFunctionLibrary::GetSkeletalMesh(UObject* DataObject)
{
    auto MeshData = GetMeshData(DataObject);

    return MeshData ? IMeshDataInterface::Execute_GetSkeletalMesh(MeshData) : nullptr;
}

TSoftObjectPtr<UMaterialInterface> UMeshManagerFunctionLibrary::GetMaterial(UObject* DataObject)
{
    auto MeshData = GetMeshData(DataObject);

    return MeshData ? IMeshDataInterface::Execute_GetMaterial(MeshData) : nullptr;
}

TSoftClassPtr<UAnimInstance> UMeshManagerFunctionLibrary::GetAnimationClass(UObject* DataObject)
{
    auto MeshData = GetMeshData(DataObject);

    return MeshData ? IMeshDataInterface::Execute_GetAnimationClass(MeshData) : nullptr;
}
