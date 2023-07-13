// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BackToBack/GameEnums/BTBEnums.h"
#include "GameFramework/Character.h"
#include "BTBCharacter.generated.h"


class UBTBCharacterAction;
class UInputMappingContext;
class ABTBCamera;


/**
 * Our Version of Character.
 */

UCLASS()
class BACKTOBACK_API ABTBCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABTBCharacter();
	
	bool GetbStartJump()
	{
		return bStartJump;
	}
	
	void SetbStartJump(const bool Value)
	{
		bStartJump = Value;
	}

	UFUNCTION(BlueprintCallable)
	virtual float GetUserInput_X()
	{
		return UserInput_X;
	}

	virtual void SetUserInput_X(const float Value)
	{
		UserInput_X = Value;
	}

	virtual float GetUserInput_Y()
	{
		return UserInput_Y;
	}

	virtual void SetUserInput_Y(const float Value)
	{
		UserInput_Y = Value;
	}

	// bool GetbStartShoot()
	// {
	// 	return bStartShoot;
	// }
	//
	// void SetbStartShoot(const bool Value)
	// {
	// 	bStartShoot = Value;
	// }

	// bool GetbStartThrowing()
	// {
	// 	return bStartThrowing;
	// }
	//
	// void SetbStartThrowing(const bool Value)
	// {
	// 	bStartThrowing = Value;
	// }
	//
	// bool GetbStartSummoning()
	// {
	// 	return bStartSummoning;
	// }
	//
	// void SetbStartSummoning(const bool Value)
	// {
	// 	bStartSummoning = Value;
	// }

	// UFUNCTION(BlueprintCallable)
	// bool GetbStartAttack()
	// {
	// 	return bstartAttack;
	// }
	//
	// UFUNCTION(BlueprintCallable)
	// void SetbStartAttack(const bool Value)
	// {
	// 	bstartAttack = Value;
	// }

	bool GetbStartPool()
	{
		return bStartPool;
	}

	void SetbStartPool(const bool Value)
	{
		bStartPool = Value;
	}

	bool GetbIsPaused()
	{
		return bIsPaused;
	}

	void SetbIsPaused(const bool Value)
	{
		bIsPaused = Value;
	}

	// UFUNCTION(BlueprintCallable)
	// virtual bool GetbStartSwitching()
	// {
	// 	return bStartSwitching;
	// }
	//
	// UFUNCTION(BlueprintCallable)
	// void SetbStartSwitching(const bool Value)
	// {
	// 	bStartSwitching = Value;
	// }

	// bool GetbStartDashing()
	// {
	// 	return bStartDashing;
	// }
	//
	// void SetbStartDashing(bool Value)
	// {
	// 	bStartDashing = Value;
	// }
	
protected:
	virtual void Die() PURE_VIRTUAL(ABTBCharacter::Die);
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

private:
	

	
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<TObjectPtr<UBTBCharacterAction>> CharacterActions;

	TObjectPtr<ABTBCamera> TopDownCameraPtr;
	
	UPROPERTY(EditAnywhere, Category = "Health")
	float Health { 2 };

	UPROPERTY(EditAnywhere, meta=(ClampMin = 1, ClampMax = 100), Category = "Health")
	float MaxHealth { 2 };
	
	float UserInput_X;
	float UserInput_Y;
	float TickDeltaTime;

	UPROPERTY(BlueprintReadOnly)
	ERightTriggerButtonStates RightTriggerButtonState;
	
	UPROPERTY(BlueprintReadOnly)
	ELeftTriggerButtonStates LeftTriggerButtonState;

	UPROPERTY(BlueprintReadOnly)
	ERightButtonStates RightButtonState;
	
	UPROPERTY(BlueprintReadOnly)
	ELeftButtonStates LeftButtonState;

	UPROPERTY(BlueprintReadOnly)
	EUpButtonStates UpButtonState;

	UPROPERTY(BlueprintReadOnly)
	EDownButtonStates DownButtonState;

	UPROPERTY(BlueprintReadOnly)
	EStartButtonStates StartButtonState;
	
protected:

	
private:
	bool bStartRotate = false;
	bool bStartJump = false;
	// bool bStartSwitching = false;
	// bool bStartShoot = false;
	// bool bstartAttack = false;
	bool bStartPool = false;
	bool bHasMovementInput;
	bool bIsPaused = false;
	// bool bStartThrowing = false;
	// bool bStartSummoning = false;
	// bool bStartDashing = false;
	
};