// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "AsyncTaskCooldownChanged.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCooldownChanged, FGameplayTag, CooldownTag, FActiveGameplayEffectHandle, ActiveGameplayEffectHandle);

/**
 * Blueprint node to automatically register a listener for changes (Begin and End) to an array of Cooldown tags.
 * Useful to use in UI.
 */
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncTask))
class GASPROJECT_API UAsyncTaskCooldownChanged : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	// Called when a cooldown starts
	UPROPERTY(BlueprintAssignable)
	FOnCooldownChanged OnCooldownBegin;

	// Called when a cooldown ends
	UPROPERTY(BlueprintAssignable)
	FOnCooldownChanged OnCooldownEnd;

private:
	// Reference to use the component's methods
	UAbilitySystemComponent* ASC;

	// Tags of the cooldowns the task will be listening
	FGameplayTagContainer RegisteredCooldownTags;

public:
	// Blueprint node to activate the task
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "AsyncTasks")
	static UAsyncTaskCooldownChanged* ListenForCooldownChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTagContainer CooldownTags);

	// Blueprint node to kill the task if needed
	UFUNCTION(BlueprintCallable)
	void EndTask();

private:
	// Internal methods to bind the events
	void OnActiveGameplayEffectAddedCallback(UAbilitySystemComponent* Target, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);
	void OnActiveGameplayEffectRemovedCallback(const FActiveGameplayEffect& Info);
};
