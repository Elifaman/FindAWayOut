// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseWeapon.h"
#include "MyPlayerHUDWidget.generated.h"

class UWeaponComponent;

UCLASS()
class FINDAWAYOUT_API UMyPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
		bool GetWeaponAmmoData(FAmmoData& AmmoData) const;

private:

	UWeaponComponent* GetWeaponComponent() const;
};
