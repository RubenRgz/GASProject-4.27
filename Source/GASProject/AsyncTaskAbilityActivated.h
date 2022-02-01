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
	UPROPERTY(BlueprintAssignable)
	FOnAbilityActivated OnAbilityBeginPin;

	UPROPERTY(BlueprintAssignable)
	FOnAbilityActivated OnAbilityEndPin;

private:
	UAbilitySystemComponent* ASC;
	FGameplayTagContainer RegisteredAbilitiesTags;

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "AsyncTasks")
	static UAsyncTaskAbilityActivated* ListenForAbilityActivated(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTagContainer AbilitiesTags);

private:
	void OnAbilityActivated(UGameplayAbility* GameplayAbility);
	void OnAbilityEnd(const FAbilityEndedData& AbilityEbdedData);
};
