// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickableItem.generated.h"

class USphereComponent;

UCLASS()
class FINDAWAYOUT_API APickableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableItem();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float RunningTime;

	UPROPERTY(EditAnywhere, Category = Movement)
		float ValueX;

	UPROPERTY(EditAnywhere, Category = Movement)
		float ValueY;

	UPROPERTY(EditAnywhere, Category = Movement)
		float ValueZ;
};
