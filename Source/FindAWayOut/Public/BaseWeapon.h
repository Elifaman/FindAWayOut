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
		int32 Bullets; // ���-�� �������� � ��������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
		int32 Clips; // ���-�� ��������� � ������� ������

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		bool Infinite; // ������� �� ������� � ������ ��� ���
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

	void ChangeClip(); // ������ ������� ������ �� �����
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
		FAmmoData DefaultAmmo {15, 10, false}; // ��������� ������� ������

	// ...

	// ...

	virtual void MakeShot();
	virtual bool GetTraceData(FVector& TrceStart, FVector& TraceEnd) const;

	APlayerController* GetPlayerController() const;
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;
	
	void MakeHit(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd);

	void DecreesAmmo(); // ��������� ���-� � ���-�� �������� ����� ������� ��������
	bool bIsAmmoEmpty() const; // ������ "������", ����� ������� ����� ��������� ����
	bool bIsClipEmpty() const; // ������� "������", ����� ������� ������ ������ ������
	void LogAmmo();

private:
	// ...
	FAmmoData CurrentAmmo;

};
