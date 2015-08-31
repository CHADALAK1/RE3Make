// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Item.h"
#include "Weapon.h"
#include "RE3MakeCharacter.generated.h"

UCLASS(config=Game)
class ARE3MakeCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent *CollisionComp;

public:
	ARE3MakeCharacter(const FObjectInitializer& ObjectInitializer);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	TArray<AItem*> InventoryArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	AItem *CollidedItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	AWeapon *CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	bool bIsPickingUp;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** Checks to see if the player can pickup an item*/
	bool bCanPickup;

	/** Checks to see if the player is aiming*/
	bool bIsAiming;

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Does all of the necessary things to pickup, climb, fire, and interact */
	void Action();

	/** Aims the weapon*/
	void Aim();

	UFUNCTION()
	void OnCollisionEnter(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnCollisionExit(AActor* OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:

	FORCEINLINE class UBoxComponent *GetCollisionComp() const { return CollisionComp; }
};

