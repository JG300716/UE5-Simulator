/**
* Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */
#include "DefaultPlayerOptions.h"

EDriveMode FDefaultBasicUserOption::DefaultDriveMode = EDriveMode::AllWheelDrive;
UDefaultPlayerOptions* UDefaultPlayerOptions::PlayerOptionsInstance = nullptr;
TMap<FName, UOptionBase*> UDefaultPlayerOptions::OptionMap;

UDefaultPlayerOptions::UDefaultPlayerOptions()
{
	UE_LOG(LogTemp, Warning, TEXT("Started"));

	PlayerOptionsInstance = this;
	FDefaultBasicUserOption::Create(OptionMap);
	FDefaultPhysicsUserOption::Create(OptionMap);
	FDefaultAdvanceUserOption::Create(OptionMap);
	
	//TryLoadUserOption(BasicPath);

	UE_LOG(LogTemp, Warning, TEXT("Ended"));

}

UDefaultPlayerOptions* UDefaultPlayerOptions::GetPlayerOptionsInstance()
{
	PlayerOptionsInstance = PlayerOptionsInstance == nullptr ? NewObject<UDefaultPlayerOptions>() : PlayerOptionsInstance;
	return PlayerOptionsInstance;
}

void UDefaultPlayerOptions::PrintOptionMap()
{
	for(auto & name : OptionMap)
	{
		UE_LOG(LogTemp, Warning, TEXT("Option: %s"), *name.Key.ToString());
	}
}


int UDefaultPlayerOptions::UpdateOptionValue(const ESettingsType OptionType, const FString& OptionName, const float& Value, const UINT8 WheelIndex)
{
	switch(OptionType)
	{
	case ESettingsType::Basic:
		return UpdateBasicOptionValue(OptionName);
	case ESettingsType::Physics:
		return UpdatePhysicsOptionValue(OptionName, Value);
	case ESettingsType::Advance:
		return UpdateAdvanceOptionValue(OptionName, WheelIndex);
	default:
		return -1;
	}

}

int UDefaultPlayerOptions::UpdateBasicOptionValue(const FString& OptionName)
{
	TUOption<bool>* const Option = reinterpret_cast<TUOption<bool>*>(GetOption(FName(OptionName)));
	if (Option == nullptr) return -1;
	const bool NewValue = !Option->Value;
	Option->Value = NewValue;

	return NewValue;
}

int UDefaultPlayerOptions::UpdatePhysicsOptionValue(const FString& OptionName, const float& Value)
{
	TUOption<float>* const Option = reinterpret_cast<TUOption<float>*>(GetOption(FName(OptionName)));
	if (Option == nullptr) return -1;
	const float NewValue = Option->Value + Value * Option->Step;
	if (Option->MaxValue < NewValue || Option->MinValue > NewValue) return -1;
	Option->Value = NewValue;
	return NewValue;
}

int UDefaultPlayerOptions::UpdateAdvanceOptionValue(const FString& OptionName, const UINT8 WheelIndex)
{
	TUOption<BVehicleWheels*>const * const Option =  reinterpret_cast<TUOption<BVehicleWheels*>* const>(GetOption(FName(OptionName)));
	if (Option == nullptr) return -1;
	bool NewValue;
	switch (WheelIndex)
	{
	case 0: NewValue = Option->Value->FrontLeftWheel = !Option->Value->FrontLeftWheel; break;
	case 1: NewValue = Option->Value->FrontRightWheel = !Option->Value->FrontRightWheel; break;
	case 2: NewValue = Option->Value->RearLeftWheel = !Option->Value->RearLeftWheel; break;
	case 3: NewValue = Option->Value->RearRightWheel = !Option->Value->RearRightWheel; break;
	default: return -1; // Invalid WheelIndex
	}
	return NewValue;
}

UOptionBase* UDefaultPlayerOptions::GetOption(const FName OptionName)
{
	return OptionMap.Contains(OptionName) ? OptionMap[OptionName] : nullptr;
}

bool UDefaultPlayerOptions::TrySaveUserOption(const FString& Path)
{
	return true;	
}

bool UDefaultPlayerOptions::TryLoadUserOption(const FString& Path)
{
	return true;
}

TMap<FName, UOptionBase*> UDefaultPlayerOptions::GetOptionMap()
{
	return OptionMap;
}
