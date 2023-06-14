// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BackToBack/Actions/Character/BTBCharacterAction.h"
#include "BTBPlayerJumpAction.generated.h"

class ABTBCharacter;

/**
 * 
 */
UCLASS()
class BACKTOBACK_API UBTBPlayerJumpAction : public UBTBCharacterAction
{
	GENERATED_BODY()

public:
	//virtual void Act(ABTBCharacter* Character, bool bIsAI = false) override;
	virtual void Act(ABTBCharacter* Character) override;

};