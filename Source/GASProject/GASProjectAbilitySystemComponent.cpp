// Fill out your copyright notice in the Description page of Project Settings.


#include "GASProjectAbilitySystemComponent.h"

float UGASProjectAbilitySystemComponent::GetGECooldown(FActiveGameplayEffectHandle ActiveGEHandle)
{
	const FActiveGameplayEffect* GameplayEffect = GetActiveGameplayEffectByHandle(ActiveGEHandle);
	float WorldTime = ActiveGameplayEffects.GetWorldTime();
	return GameplayEffect->GetTimeRemaining(WorldTime);
}


void UGASProjectAbilitySystemComponent::AddCooldownDataToList(FGameplayTag Tag, FActiveGameplayEffectHandle Handle)
{
	ActivatedCooldownList.Add(Tag, Handle);
}

void UGASProjectAbilitySystemComponent::RemoveCooldownDataFromList(FGameplayTag Tag)
{
	ActivatedCooldownList.Remove(Tag);
}

TArray<FActiveGameplayEffectHandle> UGASProjectAbilitySystemComponent::GetActiveGEHandlesArray()
{
	TArray<FActiveGameplayEffectHandle> OutArray;
	ActivatedCooldownList.GenerateValueArray(OutArray);
	return OutArray;
}

TArray<FGameplayTag> UGASProjectAbilitySystemComponent::GetActiveGETagsArray()
{
	TArray<FGameplayTag> OutArray;
	ActivatedCooldownList.GenerateKeyArray(OutArray);
	return OutArray;
}

FActiveGameplayEffectsContainer* UGASProjectAbilitySystemComponent::GetActiveGameplayEffectsContainer()
{
	return &ActiveGameplayEffects;
}

const FActiveGameplayEffect* UGASProjectAbilitySystemComponent::GetActiveGameplayEffectByHandle(FActiveGameplayEffectHandle ActiveGEHandle)
{
	return GetActiveGameplayEffect(ActiveGEHandle);
}
