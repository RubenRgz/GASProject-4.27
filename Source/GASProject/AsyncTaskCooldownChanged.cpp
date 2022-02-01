// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTaskCooldownChanged.h"
#include "GASProjectAbilitySystemComponent.h"

UAsyncTaskCooldownChanged* UAsyncTaskCooldownChanged::ListenForCooldownChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTagContainer InCooldownTags)
{
	if (!IsValid(AbilitySystemComponent) || InCooldownTags.Num() < 1)
	{
		return nullptr;
	}

	// Create task object
	UAsyncTaskCooldownChanged* ListenForCooldownChange = NewObject<UAsyncTaskCooldownChanged>();
	ListenForCooldownChange->ASC = AbilitySystemComponent;
	ListenForCooldownChange->RegisteredCooldownTags = InCooldownTags;

	// Add callbacks to the active gameplay effects	
	AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(ListenForCooldownChange, &UAsyncTaskCooldownChanged::OnActiveGameplayEffectAddedCallback);
	static_cast<UGASProjectAbilitySystemComponent*>(AbilitySystemComponent)->GetActiveGameplayEffectsContainer()->OnActiveGameplayEffectRemovedDelegate.AddUObject(ListenForCooldownChange, &UAsyncTaskCooldownChanged::OnActiveGameplayEffectRemovedCallback);

	return ListenForCooldownChange;
}

void UAsyncTaskCooldownChanged::EndTask()
{
	if (IsValid(ASC))
	{
		ASC->OnActiveGameplayEffectAddedDelegateToSelf.RemoveAll(this);
		static_cast<UGASProjectAbilitySystemComponent*>(ASC)->GetActiveGameplayEffectsContainer()->OnActiveGameplayEffectRemovedDelegate.RemoveAll(this);
	}

	SetReadyToDestroy();
	MarkPendingKill();
}

void UAsyncTaskCooldownChanged::OnActiveGameplayEffectAddedCallback(UAbilitySystemComponent* Target, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle)
{
	FGameplayTagContainer AssetTags;
	SpecApplied.GetAllAssetTags(AssetTags);

	FGameplayTagContainer GrantedTags;
	SpecApplied.GetAllGrantedTags(GrantedTags);

	TArray<FGameplayTag> CooldownTagArray;
	RegisteredCooldownTags.GetGameplayTagArray(CooldownTagArray);

	for (FGameplayTag CooldownTag : CooldownTagArray)
	{
		if (AssetTags.HasTagExact(CooldownTag) || GrantedTags.HasTagExact(CooldownTag))
		{
			// Player is Server
			OnCooldownBegin.Broadcast(CooldownTag, ActiveHandle);
		}
	}
}

void UAsyncTaskCooldownChanged::OnActiveGameplayEffectRemovedCallback(const FActiveGameplayEffect& Info)
{
	FGameplayTagContainer AssetTags;
	Info.Spec.GetAllAssetTags(AssetTags);

	FGameplayTagContainer GrantedTags;
	Info.Spec.GetAllGrantedTags(GrantedTags);

	TArray<FGameplayTag> CooldownTagArray;
	RegisteredCooldownTags.GetGameplayTagArray(CooldownTagArray);

	for (FGameplayTag CooldownTag : CooldownTagArray)
	{
		if (AssetTags.HasTagExact(CooldownTag) || GrantedTags.HasTagExact(CooldownTag))
		{
			// Player is Server
			OnCooldownEnd.Broadcast(CooldownTag, Info.Handle);
		}
	}
}
