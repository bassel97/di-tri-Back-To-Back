// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBScarabCollectable.h"

#include "BackToBack/Characters/BTBMiniGameTwoPlayableCharacter.h"
#include "Components/BoxComponent.h"

ABTBScarabCollectable::ABTBScarabCollectable()
{
	ScarabMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Scarab Mesh"));
	ScarabMesh->SetupAttachment(SceneComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(SceneComponent);
}

void ABTBScarabCollectable::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABTBScarabCollectable::OnBoxOverlap);
}

void ABTBScarabCollectable::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ABTBMiniGameTwoPlayableCharacter* MG2Player = Cast<ABTBMiniGameTwoPlayableCharacter>(OtherActor))
	{
		if (MG2Player->DashMeter < 1.f && MG2Player->DashMeter >= 0.0f)
		{
			MG2Player->DashMeter += 0.2f;
			Cast<ABTBMiniGameTwoPlayableCharacter>(MG2Player->OtherPlayer)->DashMeter = MG2Player->DashMeter;
		}
		MG2Player->PlayerDash.Broadcast(MG2Player->DashMeter);
		this->Destroy();
	}
}




