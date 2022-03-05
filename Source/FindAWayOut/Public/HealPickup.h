// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "HealPickup.generated.h"

/**
 * 
 */
UCLASS()
class FINDAWAYOUT_API AHealPickup : public ABasePickup
{
	GENERATED_BODY()
	

private:
	//...
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
