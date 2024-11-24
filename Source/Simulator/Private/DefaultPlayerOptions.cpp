/**
* Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */
#include "DefaultPlayerOptions.h"

EDriveMode FDefaultBasicUserOption::DefaultDriveMode = EDriveMode::AllWheelDrive;
UDefaultPlayerOptions* UDefaultPlayerOptions::PlayerOptionsInstance = nullptr;

UDefaultPlayerOptions::UDefaultPlayerOptions()
{
	UE_LOG(LogTemp, Warning, TEXT("Started"));

	PlayerOptionsInstance = this;
	
	BasicUserOptionInstance = MakeUnique<FDefaultBasicUserOption>(OptionMap);
	PhysicsUserOptionInstance = MakeUnique<FDefaultPhysicsUserOption>(OptionMap);
	AdvanceUserOptionInstance = MakeUnique<FDefaultAdvanceUserOption>(OptionMap);
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


int UDefaultPlayerOptions::UpdateOptionValue(const EOptionType OptionType, const FString& OptionName, const float& Value, const UINT8 WheelIndex)
{
	switch(OptionType)
	{
	case EOptionType::Basic:
		return UpdateBasicOptionValue(OptionName);
	case EOptionType::Physics:
		return UpdatePhysicsOptionValue(OptionName, Value);
	case EOptionType::Advance:
		return UpdateAdvanceOptionValue(OptionName, WheelIndex);
	default:
		return -1;
	}

}

int UDefaultPlayerOptions::UpdateBasicOptionValue(const FString& OptionName)
{
	TFOption<bool>* const Option = reinterpret_cast<TFOption<bool>*>(GetOption(FName(OptionName)));
	if (Option == nullptr) return -1;
	const bool NewValue = !Option->Value;
	Option->Value = NewValue;
	return NewValue;
}

int UDefaultPlayerOptions::UpdatePhysicsOptionValue(const FString& OptionName, const float& Value)
{
	TFOption<float>* const Option = reinterpret_cast<TFOption<float>*>(GetOption(FName(OptionName)));
	if (Option == nullptr) return -1;
	const float NewValue = Option->Value + Value * Option->Step;
	if (Option->MaxValue < NewValue || Option->MinValue > NewValue) return -1;
	Option->Value = NewValue;
	return NewValue;
}

int UDefaultPlayerOptions::UpdateAdvanceOptionValue(const FString& OptionName, const UINT8 WheelIndex)
{
	TFOption<BVehicleWheels*>const * const Option =  reinterpret_cast<TFOption<BVehicleWheels*>* const>(GetOption(FName(OptionName)));
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

FOptionBase* UDefaultPlayerOptions::GetOption(const FName OptionName)
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

