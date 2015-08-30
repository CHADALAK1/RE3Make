// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum EItemType
{
	E_Consumable	UMETA(DisplayName = "Consumable"),
	E_Weapon		UMETA(DisplayName = "Weapon"),
	E_KeyItem		UMETA(DisplayName = "KeyItem")
};

UCLASS()
class RE3MAKE_API AItem : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent *CollisionComp;
	
public:	
	// Sets default values for this actor's properties
	AItem(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemType)
	TEnumAsByte<EItemType> TypeItem;

	virtual void Pickup();
	virtual void Drop();

	FORCEINLINE class UBoxComponent *GetCollisionComp() const { return CollisionComp; }
	
};
