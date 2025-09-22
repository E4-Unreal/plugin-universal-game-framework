// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/UGFNonPlayerCharacter.h"

AUGFNonPlayerCharacter::AUGFNonPlayerCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}
