// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "GunPowder.generated.h"

/**
 * 
 */
UCLASS()
class RE3MAKE_API AGunPowder : public AItem
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent *Mesh;
	
public:
	AGunPowder(const FObjectInitializer &ObjectInitializer);
	

	FORCEINLINE class UStaticMeshComponent *GetMesh() const { return Mesh; }
	
};
