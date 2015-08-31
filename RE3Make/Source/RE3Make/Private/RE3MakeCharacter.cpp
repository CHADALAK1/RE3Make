// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "RE3Make.h"
#include "RE3MakeCharacter.h"

//////////////////////////////////////////////////////////////////////////
// ARE3MakeCharacter

ARE3MakeCharacter::ARE3MakeCharacter(const FObjectInitializer& ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	InventoryArray.SetNum(8);

	CollisionComp = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("CollisionComp"));
	CollisionComp->AttachTo(RootComponent);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ARE3MakeCharacter::OnCollisionEnter);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &ARE3MakeCharacter::OnCollisionExit);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ARE3MakeCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAction("Action", IE_Pressed, this, &ARE3MakeCharacter::Action);
	InputComponent->BindAction("Aim", IE_Pressed, this, &ARE3MakeCharacter::Aim);
	InputComponent->BindAction("Aim", IE_Released, this, &ARE3MakeCharacter::Aim);

	InputComponent->BindAxis("MoveForward", this, &ARE3MakeCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARE3MakeCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ARE3MakeCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ARE3MakeCharacter::LookUpAtRate);
}

void ARE3MakeCharacter::Action()
{
	if (bCanPickup)
	{
		for (int32 i = 0; i < InventoryArray.Num(); i++)
		{
			if (InventoryArray[i] == NULL)
			{
				InventoryArray[i] = CollidedItem;
				CollidedItem->Pickup();
				break;
			}
		}
	}
}

void ARE3MakeCharacter::Aim()
{
	if (!bIsAiming)
	{
		bIsAiming = true;
	}
	else
	{
		bIsAiming = false;
	}
}

void ARE3MakeCharacter::OnCollisionEnter(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweep, const FHitResult &SweepResult)
{
	AItem *Item = Cast<AItem>(OtherActor);
	if (Item)
	{
		if (CollidedItem == NULL)
		{
			bCanPickup = true;
			CollidedItem = Item;
		}
	}
}

void ARE3MakeCharacter::OnCollisionExit(AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	AItem *Item = Cast<AItem>(OtherActor);
	if (Item)
	{
		if (CollidedItem != NULL)
		{
			bCanPickup = false;
			CollidedItem = NULL;
		}
	}
}

void ARE3MakeCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	
}

void ARE3MakeCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ARE3MakeCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f) && (!bIsAiming))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ARE3MakeCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
