// Fill out your copyright notice in the Description page of Project Settings.

#include "RE3Make.h"
#include "Weapon.h"

AWeapon::AWeapon(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	Mesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);
}

void AWeapon::Use()
{
	Super::Use();
	if (ItemStruct.bIsWeapon)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, "Used Item From Weapon");
	}
}


