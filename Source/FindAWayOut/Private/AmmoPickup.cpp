// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickup.h"
#include "WeaponComponent.h"

bool AAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{	
	UE_LOG(LogTemp, Warning, TEXT("Ammo was taken"));
	return true;
}