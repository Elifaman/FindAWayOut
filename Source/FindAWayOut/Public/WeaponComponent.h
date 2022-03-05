
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseWeapon.h"
#include "WeaponComponent.generated.h"

class ABaseWeapon;
class UAnimMontage;

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		TSubclassOf<ABaseWeapon> WeaponClass;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Anim")
		UAnimMontage* ReloadAnimMontage;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FINDAWAYOUT_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// ...
	UWeaponComponent();

	void StartFire();
	void StopFire();
	void NextWeapon();
	void Reload();

	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;

protected:
	// ...
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TArray<FWeaponData> WeaponData;

	UPROPERTY(EditAnywhere, Category = "Socket")
		FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditAnywhere, Category = "Socket")
		FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Anim")
		UAnimMontage* EquipAnimMontage;

	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
private:	
	
	UPROPERTY()
		ABaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
		TArray<ABaseWeapon*> Weapons;

	UPROPERTY()
		UAnimMontage* CurrentReloadAnimMontage = nullptr;

	int32 CurrentWeaponIndex = 0;
	bool bIsEquipAnimInProgress = false;
	bool bIsReloadAnimInProgress = false;
	
	void SpawnWeapons();
	void AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void EquipWeapon(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage* Anim);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

	bool CanFire() const;
	bool CanEquip() const;
	bool CanReload() const;

	void OnEmptyClip();
	void ChangeClip();
 
	template<typename T>
	T* FindNotifyByClass(UAnimSequenceBase* Anim)
	{
		if (!Anim) return nullptr;

		const auto NotifyEvents = Anim->Notifies;
		for (auto NotifyEvent : NotifyEvents)
		{
			auto AnimNotify = Cast<T>(NotifyEvent.Notify);
			if (AnimNotify)
			{
				return AnimNotify;
			}
		}
		return nullptr;
	}

};
