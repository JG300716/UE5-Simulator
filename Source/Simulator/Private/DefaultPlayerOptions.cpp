/**
* Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */
#include "DefaultPlayerOptions.h"

#include "Blueprint/UserWidget.h"

EDriveMode FDefaultBasicUserOption::DefaultDriveMode = EDriveMode::AllWheels;
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

UOptionBase* UDefaultPlayerOptions::GetOption(const FName OptionName)
{
	return OptionMap.Contains(OptionName) ? OptionMap[OptionName] : nullptr;
}

TMap<FName, UOptionBase*> UDefaultPlayerOptions::GetOptionMap()
{
	return OptionMap;
}

void UDefaultPlayerOptions::LogOptionMap()
{
	for(auto & name : OptionMap)
	{
		UE_LOG(LogTemp, Warning, TEXT("Option: %s"), *name.Key.ToString());
		UE_LOG(LogTemp, Warning, TEXT("Value: %d"), (int8)name.Value->SettingsType.GetIntValue());
		UE_LOG(LogTemp, Warning, TEXT("Option Type: %d"), (int8)name.Value->BaseOptionButtonType.GetIntValue());
	}
}

void UDefaultPlayerOptions::GetOptionByName(const FName OptionName, UOptionBase* &Option, TEnumAsByte<EOptionButtonType> &OptionType)
{
	if (!OptionMap.Contains(OptionName)) return;
	Option = OptionMap[OptionName];
	OptionType = Option->BaseOptionButtonType;
}
