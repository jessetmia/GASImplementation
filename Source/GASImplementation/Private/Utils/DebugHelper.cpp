#include "Utils/DebugHelper.h"

void DebugHelper::Print(const FString& ClassName, const FString& Message, const FColor& Color, const uint64 FKey,
	const bool bPrintToScreen)
{
	UE_LOG(LogTemp, Warning, TEXT("%s: %s"),*ClassName, *Message);

	if (bPrintToScreen)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(FKey, 5.f, Color, Message);
	}
}
