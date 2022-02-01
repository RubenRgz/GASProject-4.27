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
	UFUNCTION(BlueprintCallable, Category = "GeneralLogic")
	float GetGECooldown(FActiveGameplayEffectHandle ActiveGEHandle);

	UFUNCTION(BlueprintCallable, Category = "GeneralLogic")
	void AddCooldownDataToList(FGameplayTag Tag, FActiveGameplayEffectHandle Handle);

	UFUNCTION(BlueprintCallable, Category = "GeneralLogic")
	void RemoveCooldownDataFromList(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "GeneralLogic")
	TArray<FActiveGameplayEffectHandle> GetActiveGEHandlesArray();

	UFUNCTION(BlueprintCallable, Category = "GeneralLogic")
	TArray<FGameplayTag> GetActiveGETagsArray();

	FActiveGameplayEffectsContainer* GetActiveGameplayEffectsContainer();

private:
	const FActiveGameplayEffect* GetActiveGameplayEffectByHandle(FActiveGameplayEffectHandle ActiveGEHandle);
};
