// Copyright di-tri studio, Inc. All Rights Reserved.

#pragma once

//#include "BackToBack/Characters/BTBCharacter.h"
#include "CoreMinimal.h"
#include "BackToBack/Actions/Character/BTBCharacterAction.h"
#include "BTBPlayer4DMoveAction.generated.h"

class ABTBCharacter;
class ABTBAICharacter;

/**
 * Our 4D Move for mini game two (top down)
 */
UCLASS()
class BACKTOBACK_API UBTBPlayer4DMoveAction : public UBTBCharacterAction
{
	GENERATED_BODY()

public:
	virtual void Act(ABTBCharacter* Character) override;

};
