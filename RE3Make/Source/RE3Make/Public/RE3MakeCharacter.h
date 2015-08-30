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

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	bool bCanPickup;

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

	void Action();

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

