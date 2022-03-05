
#include "LauncherWeapon.h"
#include "MyProjectile.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

void ALauncherWeapon::StartFire()
{
	MakeShot();
	UE_LOG(LogTemp, Warning, TEXT("FIRE!!"));
}

void ALauncherWeapon::MakeShot()
{
	if (!GetWorld() || bIsAmmoEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd))
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	AMyProjectile* Projectile = GetWorld()->SpawnActorDeferred<AMyProjectile>(ProjectileClass, SpawnTransform);

	if (Projectile)
	{
		Projectile->SetShotDirection(Direction);
		Projectile->SetOwner(GetOwner());
		Projectile->FinishSpawning(SpawnTransform);
	}

	DecreesAmmo();
}




