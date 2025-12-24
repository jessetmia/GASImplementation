#pragma once

class DebugHelper
{
public:
	static void Print(const FString& ClassName, const FString& Message, const FColor& Color = FColor::MakeRandomColor(), const uint64 FKey = -1, const bool bPrintToScreen = true);
};
