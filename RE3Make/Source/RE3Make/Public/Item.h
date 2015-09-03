// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ParticleDefinitions.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum EItemType
{
	E_Consumable	UMETA(DisplayName = "Consumable"),
	E_Weapon		UMETA(DisplayName = "Weapon"),
	E_KeyItem		UMETA(DisplayName = "KeyItem")
};

USTRUCT(BlueprintType)
struct FItemStruct
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	/** Splash art for the UI */
	UTexture2D* SplashArt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		/** Name of the weapon */
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	FString Info;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		/** Name of the weapon */
	bool bIsWeapon;
};

UCLASS()
class RE3MAKE_API AItem : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent *CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Particle, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent *ItemFlash;
	
public:	
	// Sets default values for this actor's properties
	AItem(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
		/** Weapon Configuration Struct object */
	FItemStruct ItemStruct;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemType)
	TEnumAsByte<EItemType> TypeItem;

	UFUNCTION(BlueprintCallable, Category = Item)
	virtual void Pickup();

	UFUNCTION(BlueprintCallable, Category = Item)
	virtual void Use();

	virtual void Drop();

	FORCEINLINE class UBoxComponent *GetCollisionComp() const { return CollisionComp; }
	FORCEINLINE class UParticleSystemComponent *GetItemFlash() const { return ItemFlash; }
	
};
