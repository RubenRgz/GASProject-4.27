// Fill out your copyright notice in the Description page of Project Settings.


#include "GASProjectEnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GASProjectAbilitySystemComponent.h"
#include "GASProjectAttributeSet.h"
#include "GASProjectGameplayAbility.h"
#include <GameplayEffectTypes.h>

// Sets default values
AGASProjectEnemyCharacter::AGASProjectEnemyCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Create ability system object
	AbilitySystemComponent = CreateDefaultSubobject<UGASProjectAbilitySystemComponent>("AbilitySystemComponent");
}

// Called when the game starts or when spawned
void AGASProjectEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(AbilitySystemComponent))
	{
		AttributeSet = AbilitySystemComponent->GetSet<UGASProjectAttributeSet>();
	}
}

// Called to bind functionality to input
void AGASProjectEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AGASProjectEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGASProjectEnemyCharacter::GrantAbility(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level, int32 InputCode)
{
	if (GetLocalRole() == ROLE_Authority && IsValid(AbilitySystemComponent) && IsValid(AbilityClass))
	{
		UGameplayAbility* Ability = AbilityClass->GetDefaultObject<UGameplayAbility>();

		if (IsValid(Ability))
		{
			// Create the new ability spec struct
			FGameplayAbilitySpec AbilitySpec(Ability, Level, InputCode);

			// Give ability to the system
			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}
	}
}

void AGASProjectEnemyCharacter::ActivateAbility(int32 InputCode)
{
	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->AbilityLocalInputPressed(InputCode);
	}
}

void AGASProjectEnemyCharacter::CancelAbility(const FGameplayTagContainer CancelWithTags)
{
	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->CancelAbilities(&CancelWithTags);
	}
}

float AGASProjectEnemyCharacter::GetHealth() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetHealth();
	}
	return -1.0f;
}
