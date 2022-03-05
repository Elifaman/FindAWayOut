// Fill out your copyright notice in the Description page of Project Settings.


#include "HealPickup.h"

bool AHealPickup::GivePickupTo(APawn* PlayerPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Heal was taken"));
	return true;
}
