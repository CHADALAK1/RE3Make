// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "Weapon.generated.h"

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
		* automatically sort them in BornImmortalCharacter (SORTING WIP)
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


	virtual void Use() override;


	FORCEINLINE class USkeletalMeshComponent *GetMesh() const { return Mesh; }
	
};
