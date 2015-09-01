// Fill out your copyright notice in the Description page of Project Settings.

#include "RE3Make.h"
#include "GunPowder.h"


AGunPowder::AGunPowder(const FObjectInitializer &ObjectInitializer)
: Super(ObjectInitializer)
{
	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, "Mesh");
	Mesh->AttachTo(RootComponent);
}



