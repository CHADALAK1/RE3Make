// Fill out your copyright notice in the Description page of Project Settings.

#include "RE3Make.h"
#include "Weapon.h"

AWeapon::AWeapon(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	Mesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);
}


