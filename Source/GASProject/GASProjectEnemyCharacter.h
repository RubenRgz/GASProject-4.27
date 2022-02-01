// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include <GameplayEffectTypes.h>
#include "GASProjectEnemyCharacter.generated.h"

UCLASS()
class GASPROJECT_API AGASProjectEnemyCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

#pragma region GameplayAbilitySystem
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UGASProjectAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	const class UGASProjectAttributeSet* AttributeSet;
#pragma endregion

public:
	// Sets default values for this character's properties
	AGASProjectEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region GameplayAbilitySystem
	/** Returns current ability system component. */
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/** Register ability to the character. */
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void GrantAbility(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level, int32 InputCode);

	/** Activates a specific ability. */
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void ActivateAbility(int32 InputCode);

	/** Cancels a specific ability. */
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void CancelAbility(const FGameplayTagContainer CancelWithTags);

	/** Get current health attribute. */
	UFUNCTION(BlueprintPure, Category = "Abilities|Attributes")
	float GetHealth() const;
#pragma endregion
};
