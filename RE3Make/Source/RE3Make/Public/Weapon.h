// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "Weapon.generated.h"

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
	AWeapon();

	FORCEINLINE class USkeletalMeshComponent *GetMesh() const { return Mesh; }
	
};
