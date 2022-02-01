// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GASProjectAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class GASPROJECT_API UGASProjectAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

private:
	TMap<FGameplayTag, FActiveGameplayEffectHandle> ActivatedCooldownList;

public:
	// Retrieves gameplay effect remaining cooldown time
	UFUNCTION(BlueprintCallable, Category = "GeneralLogic")
	float GetGECooldown(FActiveGameplayEffectHandle ActiveGEHandle);

	// Add gameplay effect handle to a map that will be iterated to get all cooldown times
	UFUNCTION(BlueprintCallable, Category = "GeneralLogic")
	void AddCooldownDataToList(FGameplayTag Tag, FActiveGameplayEffectHandle Handle);

	// Remove gameplay effect handle from the map
	UFUNCTION(BlueprintCallable, Category = "GeneralLogic")
	void RemoveCooldownDataFromList(FGameplayTag Tag);

	// Retrieves all the handles(values) in the map
	UFUNCTION(BlueprintCallable, Category = "GeneralLogic")
	TArray<FActiveGameplayEffectHandle> GetActiveGEHandlesArray();

	// Retrieves all the tags(keys) in the map
	UFUNCTION(BlueprintCallable, Category = "GeneralLogic")
	TArray<FGameplayTag> GetActiveGETagsArray();

	// Internal function to get the container of the active gameplay effect
	FActiveGameplayEffectsContainer* GetActiveGameplayEffectsContainer();

private:
	const FActiveGameplayEffect* GetActiveGameplayEffectByHandle(FActiveGameplayEffectHandle ActiveGEHandle);
};
