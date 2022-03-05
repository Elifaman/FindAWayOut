// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FindAWayOut/GameStructs.h"
#include "BaseWeapon.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnClipEmptySigtature);

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		int32 Bullets; // кол-во патронов в магазине

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
		int32 Clips; // кол-во магаизнов в текущем оружии

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		bool Infinite; // конечен ли арсенал у оружия или нет
};

UCLASS()
class FINDAWAYOUT_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

	FOnClipEmptySigtature OnClipEmpty;

	virtual void StartFire();
	virtual void StopFire();

	void ChangeClip(); // замена текущей обоймы на новую
	bool CanReload() const;

	FAmmoData GetAmmoData() { return CurrentAmmo; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		ABaseWeapon* BaseWeaponPointer;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		FAmmoData DefaultAmmo {15, 10, false}; // начальный арсенал оружия

	// ...

	// ...

	virtual void MakeShot();
	virtual bool GetTraceData(FVector& TrceStart, FVector& TraceEnd) const;

	APlayerController* GetPlayerController() const;
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;
	
	void MakeHit(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd);

	void DecreesAmmo(); // обновляет инф-ю о кол-ве патронов после каждого выстрела
	bool bIsAmmoEmpty() const; // вернет "правду", когда арсенал будет полностью пуст
	bool bIsClipEmpty() const; // вертнет "правду", когда текущая обойма станет пустой
	void LogAmmo();

private:
	// ...
	FAmmoData CurrentAmmo;

};
