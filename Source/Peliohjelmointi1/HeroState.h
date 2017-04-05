#pragma once

UENUM(BlueprintType)
enum class EHeroState : uint8 {
	HS_Idle UMETA(DisplayName = "Idle"),
	HS_Climb UMETA(DisplayName = "Climb"),
	HS_Attack UMETA(DisplayName = "Attack"),
	HS_Block UMETA(DisplayName = "Block"),
	HS_Counter UMETA(DisplayName = "Counter"),
	HS_Inhale UMETA(DisplayName = "Inhale"),
	HS_Exhale UMETA(DisplayName = "Exhale"),
	HS_Pickup UMETA(DisplayName = "Pickup")
};

