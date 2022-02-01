// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTaskAbilityActivated.h"

UAsyncTaskAbilityActivated* UAsyncTaskAbilityActivated::ListenForAbilityActivated(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTagContainer AbilitiesTags)
{
	if (!IsValid(AbilitySystemComponent) || AbilitiesTags.Num() < 1)
	{
		return nullptr;
	}

	// Create task object
	UAsyncTaskAbilityActivated* ListenForAbilityActivated = NewObject<UAsyncTaskAbilityActivated>();
	ListenForAbilityActivated->ASC = AbilitySystemComponent;
	ListenForAbilityActivated->RegisteredAbilitiesTags = AbilitiesTags;

	// Add callbacks to the begin and end of the ability
	AbilitySystemComponent->AbilityActivatedCallbacks.AddUObject(ListenForAbilityActivated, &UAsyncTaskAbilityActivated::OnAbilityActivated);
	AbilitySystemComponent->OnAbilityEnded.AddUObject(ListenForAbilityActivated, &UAsyncTaskAbilityActivated::OnAbilityEnd);

	return ListenForAbilityActivated;
}

void UAsyncTaskAbilityActivated::OnAbilityActivated(UGameplayAbility* GameplayAbility)
{
	for (FGameplayTag ListenTag : RegisteredAbilitiesTags)
	{
		for (FGameplayTag AbilityTag : GameplayAbility->AbilityTags)
		{
			// If one of the abilities tags is in the list of listenings
			if (ListenTag == AbilityTag)
			{
				if (IsValid(GameplayAbility))
				{
					OnAbilityBeginPin.Broadcast(GameplayAbility, GameplayAbility->AbilityTags);
					return;
				}
			}
		}
	}
}

void UAsyncTaskAbilityActivated::OnAbilityEnd(const FAbilityEndedData& AbilityEndedData)
{
	for (FGameplayTag ListenTag : RegisteredAbilitiesTags)
	{
		for (FGameplayTag AbilityTag : AbilityEndedData.AbilityThatEnded->AbilityTags)
		{
			// If one of the abilities tags is in the list of listenings
			if (ListenTag == AbilityTag)
			{
				OnAbilityEndPin.Broadcast(AbilityEndedData.AbilityThatEnded, AbilityEndedData.AbilityThatEnded->AbilityTags);
				return;
			}
		}
	}
}
