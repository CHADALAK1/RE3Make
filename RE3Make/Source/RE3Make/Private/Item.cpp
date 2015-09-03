// Fill out your copyright notice in the Description page of Project Settings.

#include "RE3Make.h"
#include "RE3MakeCharacter.h"
#include "Item.h"


// Sets default values
AItem::AItem(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("CollisionComp"));
	RootComponent = CollisionComp;

	ItemFlash = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("ItemFlash"));
	ItemFlash->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AItem::Pickup()
{
	SetActorHiddenInGame(true);
	GetCollisionComp()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetItemFlash()->Deactivate();
}

void AItem::SetOwningPawn(ARE3MakeCharacter *NewOwner)
{
	//if MyPawn does not equal argument parameter
	if (MyPawn != NewOwner)
	{
		//make the player the new owner
		Instigator = NewOwner;
		MyPawn = NewOwner;
	}
}

void AItem::Use()
{

}

void AItem::Drop()
{
	SetActorHiddenInGame(false);
}

