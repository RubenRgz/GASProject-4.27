// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbility.h"
#include "Delegates/Delegate.h"
#include "AsyncTaskAbilityActivated.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAbilityActivated, UGameplayAbility*, ActivatedGameplayAbility, FGameplayTagContainer, AbilityTags);

/**
 * Blueprint node to automatically register a listener for abilities activated
 */
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncTask))
class GASPROJECT_API UAsyncTaskAbilityActivated : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	// Called when an ability starts
	UPROPERTY(BlueprintAssignable)
	FOnAbilityActivated OnAbilityBeginPin;

	// Called when an ability ends
	UPROPERTY(BlueprintAssignable)
	FOnAbilityActivated OnAbilityEndPin;

private:
	// Reference to use the component's methods
	UAbilitySystemComponent* ASC;

	// Tags of the abilities the task will be listening
	FGameplayTagContainer RegisteredAbilitiesTags;

public:
	// Blueprint node to activate the task
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "AsyncTasks")
	static UAsyncTaskAbilityActivated* ListenForAbilityActivated(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTagContainer AbilitiesTags);

private:
	// Internal methods to bind the events
	void OnAbilityActivated(UGameplayAbility* GameplayAbility);
	void OnAbilityEnd(const FAbilityEndedData& AbilityEbdedData);
};
