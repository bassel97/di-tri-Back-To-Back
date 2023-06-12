// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BTBWeaponBase.h"
#include "BTBSpear.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;
class URotatingMovementComponent;
class USphereComponent;
/**
 * 
 */
UCLASS()
class BACKTOBACK_API ABTBSpear : public ABTBWeaponBase
{
	GENERATED_BODY()

public:
	ABTBSpear();
	
	void Throw(const FVector& Direction, const float Speed);
	void Summon(AActor* SummoningLocation);
	void ActivateBoxCollision();
	void DeactivateBoxCollision();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void StopSpearBounce();
	void Fall(float GravityScale);
	void Retrieve();
	void BounceAtEnemies();
	void PerformSphereTrace(const FVector& StartLocation, const FVector& EndLocation, float Radius);

	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> BoxTraceStart;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> BoxTraceEnd;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> SpearMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Components")
	TObjectPtr<UBoxComponent> CollisionBox;
	
	UPROPERTY(VisibleAnywhere, Category = "Collision Components")
	TObjectPtr<USphereComponent> EnemySphereDetection;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<URotatingMovementComponent> RotatingMovementComponent;

private:
	int32 EnemyCounter = 0;
	TArray<TPair<TObjectPtr<AActor>, bool>> EnemiesArray;
	
};
