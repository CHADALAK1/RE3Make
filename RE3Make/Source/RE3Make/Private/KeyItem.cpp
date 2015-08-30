// Fill out your copyright notice in the Description page of Project Settings.

#include "RE3Make.h"
#include "KeyItem.h"


AKeyItem::AKeyItem(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);
}

