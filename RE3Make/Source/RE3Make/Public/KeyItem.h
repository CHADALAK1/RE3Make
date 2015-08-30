// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "KeyItem.generated.h"

/**
 * 
 */
UCLASS()
class RE3MAKE_API AKeyItem : public AItem
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent *Mesh;

public:

	AKeyItem(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Name)
	FName KeyName;

	FORCEINLINE class UStaticMeshComponent *GetMesh() const { return Mesh; }
	
	
};
