// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

class USphereComponent;

UCLASS()
class FINDAWAYOUT_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Pickup")
		USphereComponent* CollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		float RespawnTime = 5.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:

	float RunningTime;

	UPROPERTY(EditAnywhere, Category = Movement)
		float ValueX;

	UPROPERTY(EditAnywhere, Category = Movement)
		float ValueY;

	UPROPERTY(EditAnywhere, Category = Movement)
		float ValueZ;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	virtual bool GivePickupTo(APawn* PlayerPawn);
	void PickupWasTaken();
	void Respawn();
};
