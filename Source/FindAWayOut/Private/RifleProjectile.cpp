// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Sets default values
ARifleProjectile::ARifleProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


}

void ARifleProjectile::BeginPlay()
{
	Super::BeginPlay();

}




