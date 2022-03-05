// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "XBotCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UXBotHealthComponent;
class UTextRenderComponent;
class USkeletalMeshComponent;
class UWeaponComponent;
class ABaseWeapon;

UCLASS()
class FINDAWAYOUT_API AXBotCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AXBotCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Armor = 1.0f;

	void DealDamage(float DamageAmount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UWeaponComponent* WeaponComponent;

	UFUNCTION(BlueprintCallable, Category = "Movement|Run")
		float GetMovementDirection() const;

	UFUNCTION(BlueprintCallable, Category = "Movement|Sprint")
		bool IsSprinting() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Sprint", meta = (ClampMin = "1.2",
		ClampMax = "5.0"))
		float SprintSpeed = 2.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Energy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float EnergyThreshold = 1.5f;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* HitComp, 
			AActor* OtherActor, 
			UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex, 
			bool bFromSweep, 
			const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserWidget> XBotEnergyClass;
		UUserWidget* XBotEnergyWidget;

		void RestartGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ZoomIn")
		float ZoomFactor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ZoomIn")
		bool bZoomingIn;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
		bool IsOverlappingItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ISMovingForward = false;

	bool HaveArmor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
		ABaseWeapon* BaseWeaponPointer = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	bool WantsToSprint = false;
	
	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void StartSprinting();
	void StopSprinting();

	void ZoomIn();
	void StopZoom();

	void EquipItem();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void TakeDamage(float DamageAmount);
	void StartDamage();
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(float HealAmount);
	void StartHealing();

	UFUNCTION(BlueprintCallable, Category = "Armor")
		void HealArmor(float HealAmount);


	bool bDead;

};
