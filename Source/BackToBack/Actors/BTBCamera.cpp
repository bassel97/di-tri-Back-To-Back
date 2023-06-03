// Copyright di-tri studio, Inc. All Rights Reserved.


#include "BTBCamera.h"

#include "BackToBack/Characters/BTBPlayableCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ABTBCamera::ABTBCamera()
{
	DebugSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DebugSphere"));
	SetRootComponent(DebugSphere);
	DebugSphere->SetCollisionProfileName(FName("NoCollision"));

	
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	//SetRootComponent(CameraArm);
	CameraArm->SetupAttachment(DebugSphere);

	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	

	CameraArm->TargetOffset = FVector(0, 0, MaxArmLength);
	CameraArm->SetWorldRotation(FRotator(-90, 0, 0));

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ABTBCamera::BeginPlay()
{
	Super::BeginPlay();
	GetActivePlayers();
}

void ABTBCamera::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CalculateCameraMovement();
	UpdateCameraMovement();
}
		
void ABTBCamera::GetActivePlayers()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if(!ensure(World != nullptr))
	{
		return;
	}
	UGameplayStatics::GetAllActorsOfClass(World, ABTBPlayableCharacter::StaticClass(), ActivePlayers);
}

void ABTBCamera::CalculateCameraMovement()
{
	const FVector PreviousLocation = DebugSphere->GetComponentLocation();
	const FVector PlayersAvgLocation = UGameplayStatics::GetActorArrayAverageLocation(ActivePlayers);
	const FVector LerpedLocation = UKismetMathLibrary::VLerp(PreviousLocation, PlayersAvgLocation, CameraMoveSpeed);
	DebugSphere->SetWorldLocation(LerpedLocation);
}

void ABTBCamera::UpdateCameraMovement()
{
	for (int i = 0 ; i < ActivePlayers.Num() ; i++)
	{
		TObjectPtr<AActor>& Player = ActivePlayers[i];
		for (int j = i + 1 ; j < ActivePlayers.Num() - 1 ; j++)
		{
			Distances.Add(ActivePlayers[j]->GetDistanceTo(Player));
		}
	}

	const float MaxDistance = FMath::Max(Distances);
	CameraArm->TargetArmLength = FMath::Clamp(MaxDistance, MinArmLength, MaxArmLength);
	Distances.Empty();
}
