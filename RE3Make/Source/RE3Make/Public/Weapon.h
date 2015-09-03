// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "Weapon.generated.h"

/** CUSTOM TRACE CHANNEL FOR THE INSTANT HIT PORTION */
#define TRACE_WEAPON ECC_GameTraceChannel1

UENUM(BlueprintType)
/** ENUM OF PROJECTILE TYPES.
* Can be selected in blueprint for Gameplay adjustments
*/
namespace EProjectile
{
	enum Type
	{
		E_Bullet			UMETA(DisplayName = "Bullet"),
		E_Projectile		UMETA(DisplayName = "Projectile"),
		E_Melee				UMETA(DisplayName = "Melee"),
	};
}

USTRUCT(BlueprintType)
/** STRUCT THAT HOLDS BASE VARIABLES FOR THE WEAPON */
struct FWeaponConfig
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		/** Max Clip of weapon */
	int32 MaxClip;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		/** Range of the weapon's projectile */
	float WeaponRange;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		/** Time between firing the weapon(even if trigger held down) */
	float TimeBetweenShots;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ammo)
		/** How much does each shot cost */
	int32 ShotCost;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		/** Spread of the weapon for each shot */
	float WeaponSpread;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		/** Checks to see if weapon is equipped */
	bool bIsEquipped;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		/** Use of Priority Makes the picking up of weapon and equiping them
		* automatically sort them in RE3MakeCharacter (SORTING WIP)
		*/
	int32 Priority;
};

/**
 * 
 */
UCLASS()
class RE3MAKE_API AWeapon : public AItem
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent *Mesh;
	
public:
	AWeapon(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		/** Weapon Configuration Struct object */
	FWeaponConfig WeapConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		/** Current Ammo in clip */
	int32 CurrentClip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		/** Projectile Type Enum Object */
	TEnumAsByte<EProjectile::Type> ProjType;

	UPROPERTY(EditDefaultsOnly, Category = Config)
		/** Fire Sound for weapon */
	class USoundCue* FireSound;

	UPROPERTY(EditDefaultsOnly, Category = Config)
		/** Reload Start Sound for weapon */
	class USoundCue* ReloadStartSound;

	UPROPERTY(EditDefaultsOnly, Category = Config)
		/** Reload Finish Sound for weapon */
	class USoundCue* ReloadFinishSound;

	UPROPERTY(EditDefaultsOnly, Category = Config)
		/** Reload Finish Sound for weapon */
	class USoundCue* EmptySound;

	UFUNCTION(BlueprintCallable, Category = Firing)
		/** Fires Weapon and checks ProjType Enum to decide Projectile type */
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Firing)
		/** Stops firing weapon and empties the Timer Handles */
	void StopFire();

	/** Reloads the Weapon */
	void ReloadAmmo();

	/** virtual Instant_Fire functions.
	* Reason for virtual is in case if the firing function behaves different with different weapons
	* Fires Line Trace From Weapon
	*/
	virtual void Instant_Fire();

	/** virtual ProjectileFire functions.
	* Reason for virtual is in case if the firing function behaves different with different weapons
	* Fires Projectile From Weapon
	*/
	virtual void ProjectileFire();

	/** virtual MeleeFire functions.
	* Reason for virtual is in case if the firing function behaves different with different weapons
	* Turns on Collision Damage from Weapon (WIP)
	*/
	virtual void MeleeFire();

	/** Attaches weapon to player */
	void AttachtoPlayer();

	/** Detaches weapon from player */
	void DetachFromPlayer();

	UFUNCTION(BlueprintCallable, Category = Equip)
		/** Does statements to Equip Weapon */
	void OnEquip();

	UFUNCTION(BlueprintCallable, Category = Equip)
		/** Does statements to UnEquip Weapon */
	void OnUnEquip();

	UFUNCTION(BlueprintCallable, Category = Equip)
		/** Puts the Weapon back in the alternate inventory(WeaponBackpack) */
	void OnBackpack();

	/** retrieves the trace line points between the socket and the hit object */
	FHitResult WeaponTrace(const FVector &TraceFrom, const FVector &TraceTo) const;

	/** processes the instant hit trace */
	void ProcessInstantHit(const FHitResult &Impact, const FVector &Origin, const FVector &ShootDir, int32 RandomSeed, float ReticleSpread);

	/** Returns a weapon sound to play(Firing, Reloading, etc)
	* @param Sound  SoundCue sound for the weapon to play
	* @return  Returns the Weapon Sound to be played
	*/
	UAudioComponent* PlayWeaponSound(USoundCue *Sound);

	virtual void Use() override;

	virtual void Action() override;


	FORCEINLINE class USkeletalMeshComponent *GetMesh() const { return Mesh; }
	
};
