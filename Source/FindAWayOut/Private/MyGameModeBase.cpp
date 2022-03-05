// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "XBotCharacter.h"
#include "MyGameHUD.h"

AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = AXBotCharacter::StaticClass();
	HUDClass = AMyGameHUD::StaticClass();
}