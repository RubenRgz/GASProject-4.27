// Fill out your copyright notice in the Description page of Project Settings.


#include "GASProjectAttributeSet.h"

UGASProjectAttributeSet::UGASProjectAttributeSet()
{

}

void UGASProjectAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		
		//SetHealth(FMath::Clamp(GetHealth(), 0.0f, 100.0f)); // El 100 es el max health, puede ser un atributo o un flotante
	}
}
