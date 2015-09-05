// Fill out your copyright notice in the Description page of Project Settings.

#include "RE3Make.h"
#include "RE3MakeCharacter.h"
#include "Weapon.h"

AWeapon::AWeapon(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	Mesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("Mesh"));
	Mesh->AttachTo(RootComponent);
}

void AWeapon::Use()
{
	Super::Use();
	if (ItemStruct.bIsWeapon)
	{
		if (!WeapConfig.bIsEquipped)
		{
			OnEquip();
			WeapConfig.bIsEquipped = true;
		}
		else
		{
			OnUnEquip();
			WeapConfig.bIsEquipped = false;
		}
	}
}

void AWeapon::Action()
{
	Super::Action();
	Fire();
}

void AWeapon::Fire()
{
	//TIMER HANDLER FOR TIME BETWEEN SHOTS
	FTimerHandle MyHandle;
	switch (ProjType)
	{
	case EProjectile::E_Bullet:
		Instant_Fire();
		break;
	case EProjectile::E_Spread:
		SpreadFire();
		PlayControllerRumbleEffect(Rumble);
		break;
	case EProjectile::E_Projectile:
		ProjectileFire();
		break;
	case EProjectile::E_Melee:
		MeleeFire();
	default:
		break;
	}
	SpawnMuzzleFlash(MuzzleFlash);
}

void AWeapon::StopFire()
{

}

void AWeapon::ReloadAmmo()
{

}

void AWeapon::OnEquip()
{
	AttachtoPlayer();
}

void AWeapon::OnUnEquip()
{
	DetachFromPlayer();
}

void AWeapon::AttachtoPlayer()
{
	if (MyPawn)
	{
		DetachFromPlayer();
		SetActorHiddenInGame(false);
		USkeletalMeshComponent *Character = MyPawn->GetMesh();
		Mesh->SetHiddenInGame(false);
		Mesh->AttachTo(Character, "WeaponSocket");
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "ATTACHED");
	}
}

void AWeapon::DetachFromPlayer()
{
	if (MyPawn)
	{
		SetActorHiddenInGame(true);
		Mesh->DetachFromParent();
		Mesh->SetHiddenInGame(true);
	}
}

void AWeapon::OnBackpack()
{
	//unattach weapon from socket
	GetMesh()->DetachFromParent();
	//hide the weapon
	GetMesh()->SetHiddenInGame(true);
}


void AWeapon::Instant_Fire()
{
	if (MyPawn)
	{
		if (CurrentClip > 0)
		{
			// Get the camera transform
			FVector CameraLoc;
			FRotator CameraRot;
			GetActorEyesViewPoint(CameraLoc, CameraRot);
			const int32 RandomSeed = FMath::Rand();
			FRandomStream WeaponRandomStream(RandomSeed);
			const float CurrentSpread = WeapConfig.WeaponSpread;
			const float SpreadCone = FMath::DegreesToRadians(WeapConfig.WeaponSpread * 0.5);
			const FVector AimDir = GetMesh()->GetSocketRotation("Muzzle").Vector();
			const FVector StartTrace = Mesh->GetSocketLocation("Muzzle");
			const FVector ShootDir = WeaponRandomStream.VRandCone(AimDir, SpreadCone, SpreadCone);
			const FVector EndTrace = StartTrace + ShootDir * WeapConfig.WeaponRange;
			const FHitResult Impact = WeaponTrace(StartTrace, EndTrace);

			ProcessInstantHit(Impact, StartTrace, ShootDir, RandomSeed, CurrentSpread);
			CurrentClip -= WeapConfig.ShotCost;
			PlayWeaponSound(FireSound);

			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "FIRE");
			//GetWorldTimerManager().SetTimer(this, &AWeapon::Instant_Fire, WeapConfig.TimeBetweenShots, false);
		}
		else
		{
			ReloadAmmo();
		}
	}
}

void AWeapon::SpreadFire()
{
	if (WeapConfig.SpreadAmount > 0)
	{
		for (int32 i = 0; i <= WeapConfig.SpreadAmount; i++)
		{
			Instant_Fire();
		}
	}
}

FHitResult AWeapon::WeaponTrace(const FVector &TraceFrom, const FVector &TraceTo) const
{
	static FName WeaponFireTag = FName(TEXT("WeaponTrace"));

	FCollisionQueryParams TraceParams(WeaponFireTag, true, Instigator);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;
	TraceParams.AddIgnoredActor(this);

	FHitResult Hit(ForceInit);

	GetWorld()->LineTraceSingleByChannel(Hit, TraceFrom, TraceTo, TRACE_WEAPON, TraceParams);

	return Hit;
}

void AWeapon::ProcessInstantHit(const FHitResult &Impact, const FVector &Origin, const FVector &ShootDir, int32 RandomSeed, float ReticleSpread)
{
	if (MyPawn)
	{
		const FVector EndTrace = Origin + ShootDir * WeapConfig.WeaponRange;
		const FVector EndPoint = Impact.GetActor() ? Impact.ImpactPoint : EndTrace;
		DrawDebugLine(GetWorld(), Origin, EndTrace, FColor::Black, true, 10.f);
	}
}


void AWeapon::ProjectileFire()
{

}

void AWeapon::MeleeFire()
{

}

UAudioComponent* AWeapon::PlayWeaponSound(USoundCue *Sound)
{
	UAudioComponent* AC = NULL;
	if (Sound && MyPawn)
	{
		AC = UGameplayStatics::SpawnSoundAttached(Sound, MyPawn->GetRootComponent(), FName("NAME_None"), FVector(), EAttachLocation::SnapToTarget, false, 1.0f, this->GetActorTimeDilation(), 0.0f, NULL);
	}
	return AC;
}

void AWeapon::SpawnTrailEffect(const FVector& EndPoint)
{
	if (TrailFX)
	{
		const FVector Origin = Mesh->GetSocketLocation("Muzzle");

		UParticleSystemComponent *TrailPSC = UGameplayStatics::SpawnEmitterAtLocation(this, TrailFX, Origin);
		if (TrailPSC)
		{
			TrailPSC->SetVectorParameter(FName("ShockBeamEnd"), EndPoint);
		}
	}
}

void AWeapon::PlayControllerRumbleEffect(UForceFeedbackEffect *RumbleAmount)
{
	if (Rumble)
	{
		APlayerController *Controller = GEngine->GetFirstLocalPlayerController(GetWorld());
		Controller->ClientPlayForceFeedback(RumbleAmount, false, "Rumble");
	}
}

void AWeapon::SpawnMuzzleFlash(UParticleSystem *MF)
{
	if (MF)
	{
		const FVector MFSocketLoc = GetMesh()->GetSocketLocation("Muzzle");
		const FRotator MFSocketRot = GetMesh()->GetSocketRotation("Muzzle");
		UParticleSystemComponent *Flash = UGameplayStatics::SpawnEmitterAtLocation(this, MF, MFSocketLoc, MFSocketRot);
	}
}


