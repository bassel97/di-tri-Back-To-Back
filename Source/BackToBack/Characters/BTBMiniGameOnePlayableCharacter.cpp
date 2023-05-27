// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBMiniGameOnePlayableCharacter.h"
#include "BTBEnemyCharacter.h"
#include "BackToBack/Actors/BTBGun.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

void ABTBMiniGameOnePlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABTBMiniGameOnePlayableCharacter::OnBoxOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABTBMiniGameOnePlayableCharacter::OnBoxEndOverlap);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABTBMiniGameOnePlayableCharacter::OnEnemyHit);
}

ABTBMiniGameOnePlayableCharacter::ABTBMiniGameOnePlayableCharacter()
{
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	//CollisionBox->SetupAttachment(GetRootComponent());
	CollisionBox->SetAllMassScale(0.5);
	CollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "GunSocket");

	GunSwitchPosition = CreateDefaultSubobject<UChildActorComponent>(TEXT("GunSwitchPosition"));
	GunSwitchPosition->SetupAttachment(GetMesh());
	//GunSwitchPosition->SetRelativeLocation(playersMidPoin);
}


float ABTBMiniGameOnePlayableCharacter::GetRotationValue()
{
	if(RotationValue >= 0.925f && OtherPlayer->RotationValue >= 0.925f)		return 1;
	if(RotationValue <= -0.975f && OtherPlayer->RotationValue <= -0.975f)		return -1;
	return 0;
}

void ABTBMiniGameOnePlayableCharacter::Die()
{
	Super::Die();
}

void ABTBMiniGameOnePlayableCharacter::OnEnemyHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ABTBEnemyCharacter* Enemy = Cast<ABTBEnemyCharacter>(OtherActor))
	{
		Die();
	}
}

void ABTBMiniGameOnePlayableCharacter::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherComp != nullptr && OtherActor != this)
	{
		if (OtherComp->ComponentHasTag("Hand"))
		{
			IsOverlapping = true;
		}
	}
}

void ABTBMiniGameOnePlayableCharacter::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IsOverlapping = false;
}



void ABTBMiniGameOnePlayableCharacter::SetGun(ABTBGun* Gun)
{
	GunActor = Gun;
}

ABTBGun* ABTBMiniGameOnePlayableCharacter::GetGun()
{
	return GunActor;
}