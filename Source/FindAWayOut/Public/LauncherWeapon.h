// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "LauncherWeapon.generated.h"

class AMyProjectile;

UCLASS()
class FINDAWAYOUT_API ALauncherWeapon : public ABaseWeapon
{
	GENERATED_BODY()
	
public:
	// .. 

	virtual void StartFire() override;

protected:
	// ..
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<AMyProjectile> ProjectileClass;

	virtual void MakeShot() override;

private:
	// ...



};
