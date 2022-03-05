// Fill out your copyright notice in the Description page of Project Settings.


#include "XBotCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "WeaponComponent.h"
#include "BaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(XBotCharacterLog, All, All);

// Sets default values
AXBotCharacter::AXBotCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 350.0f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));

	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	bDead = false;

	Energy = 100.0f;
	Health = 100.0f;

	IsOverlappingItem = false;

	HaveArmor = true;
	Armor = 1.0f;

	//BaseWeaponPointer = nullptr;
}



// Called when the game starts or when spawned
void AXBotCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AXBotCharacter::OnBeginOverlap);

	if (XBotEnergyClass != nullptr)
	{
		XBotEnergyWidget = CreateWidget(GetWorld(), XBotEnergyClass);
		XBotEnergyWidget->AddToViewport();
	}

}

// Called every frame
void AXBotCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Energy -= DeltaTime * EnergyThreshold;

	if (Energy <= 0.0f) {

		if (!bDead)
		{
			bDead = true;

			GetMesh()->SetSimulatePhysics(true);

			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &AXBotCharacter::RestartGame, 3.0f, false);
		}
	}


	if (bZoomingIn)
	{
		ZoomFactor += DeltaTime / 0.5f;        
	}
	else
	{
		ZoomFactor -= DeltaTime / 0.25f;
	}
	ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);

	
	FollowCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
	SpringArm->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);
	
}

// Called to bind functionality to input
void AXBotCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AXBotCharacter::StartSprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AXBotCharacter::StopSprinting);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AXBotCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AXBotCharacter::StopJumping);

	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &AXBotCharacter::ZoomIn);
	PlayerInputComponent->BindAction("ZoomIn", IE_Released, this, &AXBotCharacter::StopZoom);

	PlayerInputComponent->BindAction("Heal", IE_Pressed, this, &AXBotCharacter::StartHealing);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UWeaponComponent::StopFire);

	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UWeaponComponent::NextWeapon);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UWeaponComponent::Reload);

	PlayerInputComponent->BindAxis("MoveForward", this, &AXBotCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AXBotCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AXBotCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &AXBotCharacter::AddControllerYawInput);
	
}

void AXBotCharacter::MoveForward(float Amount)
{
	if (!bDead)
	{
		AddMovementInput(GetActorForwardVector(), Amount);
	}
	
}

void AXBotCharacter::MoveRight(float Amount)
{
	if (!bDead)
	{
		AddMovementInput(GetActorRightVector(), Amount);
	}
	
}

void AXBotCharacter::StartSprinting()
{
	if (!bDead)
	{
	WantsToSprint = true;

	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeed;
	}

}

void AXBotCharacter::StopSprinting()
{
	if (!bDead) 
	{
	WantsToSprint = false;

	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeed;
	}
	
}

void AXBotCharacter::ZoomIn()
{
	bZoomingIn = true;
}

void AXBotCharacter::StopZoom()
{
	bZoomingIn = false;
}

bool AXBotCharacter::IsSprinting() const
{
	return WantsToSprint && ISMovingForward && !GetVelocity().IsZero();
}

float AXBotCharacter::GetMovementDirection() const
{
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z);
}

void AXBotCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(TEXT("Recharge")))
	{
		
		Energy += 10.0f;

		if (Energy > 100.0f)
		{
			Energy = 100.0f;
		}

		OtherActor->Destroy();
	}
}

void AXBotCharacter::RestartGame()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AXBotCharacter::DealDamage(float DamageAmount)
{
	Health -= DamageAmount;

	if (Health <= 0.0f)
	{
		GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		RestartGame();
	}
}

void AXBotCharacter::StartDamage()
{
	TakeDamage(0.2f);
}

void AXBotCharacter::TakeDamage(float DamageAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("we received %f units of damage"), DamageAmount);

	if (Armor)
	{
		Armor -= DamageAmount;

		if (Armor < 0.0f)
		{
			HaveArmor = false;
			Health += Armor; // переход урона от щита к hp. 
			Armor = 0.0f;
		}
	}
	else 
	{
		Health -= DamageAmount;

		if (Health < 0.0f)
		{
			Health = 0.0f;
			RestartGame();
		}
	}

	
}

void AXBotCharacter::Heal(float HealAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("we're healing for %f points"), HealAmount);
	Health += HealAmount;

	if (Health >= 100.0f)
	{
		Health = 100.0f;
	}
}

void AXBotCharacter::StartHealing()
{
	Heal(0.02f);
}

void AXBotCharacter::HealArmor(float HealAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("we're healing (armor) for %f points"), HealAmount);
	Armor += HealAmount;
	HaveArmor = true;

	if (Armor > 1.0f)
	{
		Armor = 1.0f;
	}
}

void AXBotCharacter::EquipItem()
{
	if (IsOverlappingItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("We picked up an item"));
	}
}





