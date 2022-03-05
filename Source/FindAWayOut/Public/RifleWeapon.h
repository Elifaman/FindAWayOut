// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "RifleWeapon.generated.h"

class ARifleProjectile;

UCLASS()
class FINDAWAYOUT_API ARifleWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	// ...
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	// ...
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float TimeBetweenShots = 0.2f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float BulletSpread = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float DamageAmount = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<ARifleProjectile> RifleProjectileClass;


	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TrceStart, FVector& TraceEnd) const override;

private:
	// ...
	FTimerHandle ShotTimerHandle;

	void MakeDamage(const FHitResult& HitResult);
};
