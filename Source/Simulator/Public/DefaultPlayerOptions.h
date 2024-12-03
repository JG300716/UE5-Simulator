/**
* Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */

#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DefaultPlayerOptions.generated.h"


#define DEFINE_VEHICLE_WHEEL_PARTS_STRUCT(StructName, Type) \
USTRUCT(NotBlueprintType)                                     \
struct StructName                                          \
{                                                          \
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleBodyParts") \
Type FrontLeftWheel;                                   \
\
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleBodyParts") \
Type RearLeftWheel;                                    \
\
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleBodyParts") \
Type FrontRightWheel;                                  \
\
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleBodyParts") \
Type RearRightWheel;                                   \
};

#define DEFINE_VEHICLE_BODY_PARTS_STRUCT(StructName, WheelStructName, Type) \
USTRUCT(NotBlueprintType)                                                     \
struct StructName                                                          \
{                                                                          \
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleBodyParts") \
Type Chassis;                                                          \
\
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleBodyParts") \
WheelStructName Wheels;                                                \
};

DEFINE_VEHICLE_WHEEL_PARTS_STRUCT(FVehicleWheels, float)
DEFINE_VEHICLE_BODY_PARTS_STRUCT(FVehicle, FVehicleWheels, float)
DEFINE_VEHICLE_WHEEL_PARTS_STRUCT(BVehicleWheels, bool)


UENUM(NotBlueprintType)
enum EDriveMode : uint8
{
	Custom = 0,
	AllWheelDrive = 1,
	FrontWheelDrive = 2,
	RearWheelDrive = 3
};

UENUM(BlueprintType)
enum EOptionType : uint8
{
	Basic = 0,
	Physics = 1,
	Advance = 2
};

UCLASS(BlueprintType)
class SIMULATOR_API UOptionBase : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerOptions")
	TEnumAsByte<EOptionType> OptionType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerOptions")
	FString OptionName;
};
template <typename T>
USTRUCT(NotBlueprintType)
struct TUOption
{
public:
	TEnumAsByte<EOptionType> OptionType;
	FString OptionName;
	T Value;
	T DefaultValue;
	T MinValue;
	T MaxValue;
	float Step = 0;
	FString Unit;
	FString Tooltip;
	bool IsAffectingOtherOptions = false;

	TUOption(
		const EOptionType &Type,
		const FString &Name,
		T Value,
		T DefaultValue,
		T MinValue,
		T MaxValue,
		float Step,
		const FString &Unit,
		const FString &Tooltip,
		bool IsAffectingOtherOptions
		):
	OptionType(Type),
	OptionName(Name),
	Value(Value),
	DefaultValue(DefaultValue),
	MinValue(MinValue),
	MaxValue(MaxValue),
	Step(Step),
	Unit(Unit),
	Tooltip(Tooltip),
	IsAffectingOtherOptions(IsAffectingOtherOptions)
	{}

};

UCLASS(BlueprintType)
class SIMULATOR_API UOptionFloat : public UOptionBase
{
	GENERATED_BODY()
public:
	float Value;
	float DefaultValue;
	float MinValue;
	float MaxValue;
	float Step;
	FString Unit;
	FString Tooltip;
	bool IsAffectingOtherOptions;
	void Initialize(TUOption<float> &Option)
	{
		this->OptionName = Option.OptionName;
		this->OptionType = Option.OptionType;
		this->Value = Option.Value;
		this->DefaultValue = Option.DefaultValue;
		this->MinValue = Option.MinValue;
		this->MaxValue = Option.MaxValue;
		this->Step = Option.Step;
		this->Unit = Option.Unit;
		this->Tooltip = Option.Tooltip;
		this->IsAffectingOtherOptions = Option.IsAffectingOtherOptions;
	}
};
UCLASS(BlueprintType)
class SIMULATOR_API UOptionInt : public UOptionBase
{
	GENERATED_BODY()

public:
	int32 Value;
	int32 DefaultValue;
	int32 MinValue;
	int32 MaxValue;
	float Step;
	FString Unit;
	FString Tooltip;
	bool IsAffectingOtherOptions;
	void Initialize(TUOption<int32> &Option)
	{
		this->OptionName = Option.OptionName;
		this->OptionType = Option.OptionType;
		this->Value = Option.Value;
		this->DefaultValue = Option.DefaultValue;
		this->MinValue = Option.MinValue;
		this->MaxValue = Option.MaxValue;
		this->Step = Option.Step;
		this->Unit = Option.Unit;
		this->Tooltip = Option.Tooltip;
		this->IsAffectingOtherOptions = Option.IsAffectingOtherOptions;
	}
};
UCLASS(BlueprintType)
class UOptionBool : public UOptionBase
{
	GENERATED_BODY()

public:
	bool Value;
	bool DefaultValue;
	FString Tooltip;
	bool IsAffectingOtherOptions;
	void Initialize(TUOption<bool> &Option)
	{
		this->OptionName = Option.OptionName;
		this->OptionType = Option.OptionType;
		this->Value = Option.Value;
		this->DefaultValue = Option.DefaultValue;
		this->Tooltip = Option.Tooltip;
		this->IsAffectingOtherOptions = Option.IsAffectingOtherOptions;
	}
	
};

UCLASS(BlueprintType)
class UOptionDriveMode : public UOptionBase
{
	GENERATED_BODY()

public:
	TEnumAsByte<EDriveMode> Value;
	TEnumAsByte<EDriveMode> DefaultValue;
	TEnumAsByte<EDriveMode> MinValue;
	TEnumAsByte<EDriveMode> MaxValue;
	float Step;
	FString Tooltip;
	bool IsAffectingOtherOptions;
	void Initialize(TUOption<EDriveMode> &Option)
	{
		this->OptionName = Option.OptionName;
		this->OptionType = Option.OptionType;
		this->Value = Option.Value;
		this->DefaultValue = Option.DefaultValue;
		this->MinValue = Option.MinValue;
		this->MaxValue = Option.MaxValue;
		this->Step = Option.Step;
		this->Tooltip = Option.Tooltip;
		this->IsAffectingOtherOptions = Option.IsAffectingOtherOptions;
	}
};

UCLASS(BlueprintType)
class UOptionVehicle : public UOptionBase
{
	GENERATED_BODY()
public:

	FVehicle Value;
	FVehicle DefaultValue;
	FVehicle MinValue;
	FVehicle MaxValue;
	float Step;
	FString Tooltip;
	bool IsAffectingOtherOptions;

	void Initialize(TUOption<FVehicle> &Option)
	{
		this->OptionName = Option.OptionName;
		this->OptionType = Option.OptionType;
		this->Value = Option.Value;
		this->DefaultValue = Option.DefaultValue;
		this->MinValue = Option.MinValue;
		this->MaxValue = Option.MaxValue;
		this->Step = Option.Step;
		this->Tooltip = Option.Tooltip;
		this->IsAffectingOtherOptions = Option.IsAffectingOtherOptions;
	}
	
};

UCLASS(BlueprintType)
class UOptionWheels : public UOptionBase
{
	GENERATED_BODY()
public:
	FVehicleWheels Value;
	FVehicleWheels DefaultValue;
	FVehicleWheels MinValue;
	FVehicleWheels MaxValue;
	float Step;
	FString Tooltip;
	bool IsAffectingOtherOptions;

	void Initialize(TUOption<FVehicleWheels> &Option)
	{
		this->OptionName = Option.OptionName;
		this->OptionType = Option.OptionType;
		this->Value = Option.Value;
		this->DefaultValue = Option.DefaultValue;
		this->MinValue = Option.MinValue;
		this->MaxValue = Option.MaxValue;
		this->Step = Option.Step;
		this->Tooltip = Option.Tooltip;
		this->IsAffectingOtherOptions = Option.IsAffectingOtherOptions;
	}

	void Initialize(TUOption<BVehicleWheels> &Option)
	{
		this->OptionName = Option.OptionName;
		this->OptionType = Option.OptionType;
		this->Value = ConvertToVehicleWheels(Option.Value);
		this->DefaultValue = ConvertToVehicleWheels(Option.DefaultValue);
		this->MinValue = ConvertToVehicleWheels(Option.MinValue);
		this->MaxValue = ConvertToVehicleWheels(Option.MaxValue);
		this->Step = Option.Step;
		this->Tooltip = Option.Tooltip;
		this->IsAffectingOtherOptions = Option.IsAffectingOtherOptions;
	}

	FVehicleWheels& operator=(const BVehicleWheels &Other)
	{
		this->Value = ConvertToVehicleWheels(Other);
		return this->Value;
	}

private:
	FVehicleWheels ConvertToVehicleWheels(const BVehicleWheels& Source)
	{
		FVehicleWheels Result;
		Result.FrontLeftWheel = Source.FrontLeftWheel;
		Result.FrontRightWheel = Source.FrontRightWheel;
		Result.RearLeftWheel = Source.RearLeftWheel;
		Result.RearRightWheel = Source.RearRightWheel;
		return Result;
	}
};

USTRUCT(NotBlueprintType)
struct FDefaultBasicUserOption
{
	GENERATED_BODY()

	static void Create(TMap<FName, UOptionBase*>& OptionMap)
{
    TUOption<bool> ManualGearboxValues = {Basic, "Manual Gearbox", bDefaultManualGearbox, bDefaultManualGearbox, false, true, 1, "", "Use manual gearbox", true};
    TUOption<bool> AutomaticGearboxValues = {Basic, "Automatic Gearbox", bDefaultAutomaticGearbox, bDefaultAutomaticGearbox, false, true, 1, "", "Use automatic gearbox", true};
    TUOption<bool> AutomaticReverseValues = {Basic, "Automatic Reverse", bDefaultAutomaticReverse, bDefaultAutomaticReverse, false, true, 1, "", "Use automatic reverse", true};
    TUOption<EDriveMode> DriveModeValues = {Basic, "Drive Mode", DefaultDriveMode, DefaultDriveMode, EDriveMode::AllWheelDrive, EDriveMode::RearWheelDrive, 1, "", "Select drive mode", true};
    TUOption<bool> SuspensionEnabledValues = {Basic, "Suspension Enabled", bDefaultSuspensionEnabled, bDefaultSuspensionEnabled, false, true, 1, "", "Enable suspension", true};
    TUOption<bool> WheelFrictionEnabledValues = {Basic, "Wheel Friction Enabled", bDefaultWheelFrictionEnabled, bDefaultWheelFrictionEnabled, false, true, 1, "", "Enable wheel friction", true};
    TUOption<bool> TractionControlEnabledValues = {Basic, "Traction Control Enabled", bDefaultTractionControlEnabled, bDefaultTractionControlEnabled, false, true, 1, "", "Enable traction control", true};
    TUOption<bool> AbsEnabledValues = {Basic, "ABS Enabled", bDefaultAbsEnabled, bDefaultAbsEnabled, false, true, 1, "", "Enable ABS", true};

    UOptionBool* ManualGearbox = NewObject<UOptionBool>(GetTransientPackage(), UOptionBool::StaticClass());
    UOptionBool* AutomaticGearbox = NewObject<UOptionBool>(GetTransientPackage(), UOptionBool::StaticClass());
    UOptionBool* AutomaticReverse = NewObject<UOptionBool>(GetTransientPackage(), UOptionBool::StaticClass());
    UOptionDriveMode* DriveMode = NewObject<UOptionDriveMode>(GetTransientPackage(), UOptionDriveMode::StaticClass());
    UOptionBool* SuspensionEnabled = NewObject<UOptionBool>(GetTransientPackage(), UOptionBool::StaticClass());
    UOptionBool* WheelFrictionEnabled = NewObject<UOptionBool>(GetTransientPackage(), UOptionBool::StaticClass());
    UOptionBool* TractionControlEnabled = NewObject<UOptionBool>(GetTransientPackage(), UOptionBool::StaticClass());
    UOptionBool* AbsEnabled = NewObject<UOptionBool>(GetTransientPackage(), UOptionBool::StaticClass());

    ManualGearbox->Initialize(ManualGearboxValues);
    AutomaticGearbox->Initialize(AutomaticGearboxValues);
    AutomaticReverse->Initialize(AutomaticReverseValues);
    DriveMode->Initialize(DriveModeValues);
    SuspensionEnabled->Initialize(SuspensionEnabledValues);
    WheelFrictionEnabled->Initialize(WheelFrictionEnabledValues);
    TractionControlEnabled->Initialize(TractionControlEnabledValues);
    AbsEnabled->Initialize(AbsEnabledValues);

    OptionMap.Add(TEXT("ManualGearbox"), ManualGearbox);
    OptionMap.Add(TEXT("AutomaticGearbox"), AutomaticGearbox);
    OptionMap.Add(TEXT("AutomaticReverse"), AutomaticReverse);
    OptionMap.Add(TEXT("DriveMode"), DriveMode);
    OptionMap.Add(TEXT("SuspensionEnabled"), SuspensionEnabled);
    OptionMap.Add(TEXT("WheelFrictionEnabled"), WheelFrictionEnabled);
    OptionMap.Add(TEXT("TractionControlEnabled"), TractionControlEnabled);
    OptionMap.Add(TEXT("AbsEnabled"), AbsEnabled);
}

	
	static constexpr bool bDefaultManualGearbox = false;
	static constexpr bool bDefaultAutomaticGearbox = true;
	static constexpr bool bDefaultAutomaticReverse = false;
	static EDriveMode DefaultDriveMode;
	static constexpr bool bDefaultSuspensionEnabled = true;
	static constexpr bool bDefaultWheelFrictionEnabled = true;
	static constexpr bool bDefaultTractionControlEnabled = true;
	static constexpr bool bDefaultAbsEnabled = true;
};

USTRUCT(NotBlueprintType)
struct FDefaultPhysicsUserOption
{
	GENERATED_BODY()

	FDefaultPhysicsUserOption() = default;

	static void Create(TMap<FName, UOptionBase*> &OptionMap)
	{
		
		TUOption<FVehicle> VehicleMassesValues = {Physics, "Vehicle Masses",
		{ DefaultChassisMass, DefaultWheelMass, DefaultWheelMass, DefaultWheelMass, DefaultWheelMass},
		{ DefaultChassisMass, DefaultWheelMass, DefaultWheelMass, DefaultWheelMass, DefaultWheelMass},
		{0, 0, 0, 0, 0},
		{10000, 10000, 10000, 10000, 10000},
		10, "kg",
		"Set the masses of the vehicle parts",
		false };
		TUOption<float> HorsePowerValues = {Physics, "Horse Power", DefaultHorsePower, DefaultHorsePower, 0, 1000, 1, "kW", "Set the power of the engine", true };
		TUOption<float> MaxRpmValues = {Physics, "Max RPM", DefaultMaxRpm, DefaultMaxRpm, 0, 10000, 1, "RPM", "Set the maximum RPM of the engine", true };
		TUOption<float> MaxTorqueValues = {Physics, "Max Torque", DefaultMaxTorque, DefaultMaxTorque, 0, 1000, 1, "Nm", "Set the maximum torque of the engine", true };
		// Ratio of the wheelbase to the track width
		TUOption<float> AngleRatioValues = {Physics, "Angle Ratio", DefaultAngleRatio, DefaultAngleRatio, 0, 1, 0.1, "", "Set the ratio of the wheelbase to the track width", false };
		// Ratio of front to rear torque distribution, <0.5 means more torque to the front wheels, >0.5 means more torque to the rear wheels
		TUOption<float> FrontRearSplitValues = {Physics, "Front Rear Split", DefaultFrontRearSplit, DefaultFrontRearSplit, 0, 1, 0.1, "", "Set the ratio of front to rear torque distribution", false };
		// Drag coefficient of the vehicle
		TUOption<float> DragCoefficientValues = {Physics, "Drag Coefficient", DefaultDragCoefficient, DefaultDragCoefficient, 0, 1, 0.1, "", "Set the drag coefficient of the vehicle", false };
		// Rolling resistance coefficient of the vehicle
		TUOption<float> DownForceCoefficientValues = {Physics, "Down Force Coefficient", DefaultDownForceCoefficient, DefaultDownForceCoefficient, 0, 1, 0.1, "", "Set the down force coefficient of the vehicle", false };
		TUOption<float> AutomaticGearboxUpShiftRpmValues = { Physics,"Automatic Gearbox Up Shift RPM", DefaultAutomaticGearboxUpShiftRpm, DefaultAutomaticGearboxUpShiftRpm, 0, 10000, 1, "RPM", "Set the RPM at which the automatic gearbox will upshift", false };
		TUOption<float> AutomaticGearboxDownShiftRpmValues = {Physics, "Automatic Gearbox Down Shift RPM", DefaultAutomaticGearboxDownShiftRpm, DefaultAutomaticGearboxDownShiftRpm, 0, 10000, 1, "RPM", "Set the RPM at which the automatic gearbox will downshift", false };
		TUOption<float> GearboxChangeTimeValues = {Physics, "Gearbox Change Time", DefaultGearboxChangeTime, DefaultGearboxChangeTime, 0, 10, 0.1, "s", "Set the time it takes to change gears", false };
		TUOption<float> GearboxTransmissionEfficiencyValues = {Physics, "Gearbox Transmission Efficiency", DefaultGearboxTransmissionEfficiency, DefaultGearboxTransmissionEfficiency, 0, 1, 0.1, "", "Set the efficiency of the gearbox transmission", false };
		TUOption<float> MaxWheelsSteeringAngleValues = {Physics, "Max Wheels Steering Angle", DefaultMaxWheelsSteeringAngle, DefaultMaxWheelsSteeringAngle, 0, 90, 1, "deg", "Set the maximum steering angle of the wheels", false };
		TUOption<FVehicleWheels> WheelsFrictionForceMultiplierValues = {Physics, "Wheels Friction Force Multiplier",
			{ DefaultWheelsFrictionForceMultiplier, DefaultWheelsFrictionForceMultiplier,DefaultWheelsFrictionForceMultiplier,DefaultWheelsFrictionForceMultiplier },
			{ DefaultWheelsFrictionForceMultiplier, DefaultWheelsFrictionForceMultiplier,DefaultWheelsFrictionForceMultiplier,DefaultWheelsFrictionForceMultiplier },
			{ 0, 0, 0, 0 },
			{ 10, 10, 10, 10 },
			0.1, "",
			"Set the friction force multiplier of the wheels",
			false };
		TUOption<float> SuspensionMaxRaiseValues = {Physics, "Suspension Max Raise", DefaultSuspensionMaxRaise, DefaultSuspensionMaxRaise, 0, 100, 1, "cm", "Set the maximum raise of the suspension", false };
		TUOption<float> SuspensionMaxDropValues = {Physics, "Suspension Max Drop", DefaultSuspensionMaxDrop, DefaultSuspensionMaxDrop, 0, 100, 1, "cm", "Set the maximum drop of the suspension", false };
		TUOption<float> SuspensionDumpRatioValues = {Physics, "Suspension Dump Ratio", DefaultSuspensionDumpRatio, DefaultSuspensionDumpRatio, 0, 1, 0.1, "", "Set the dump ratio of the suspension", false };
		TUOption<float> SuspensionSpringRatioValues = {Physics, "Suspension Spring Ratio", DefaultSuspensionSpringRatio, DefaultSuspensionSpringRatio, 0, 1000, 1, "", "Set the spring ratio of the suspension", false };
		TUOption<float> SuspensionPreloadValues = {Physics, "Suspension Preload", DefaultSuspensionPreload, DefaultSuspensionPreload, 0, 100, 1, "cm", "Set the preload of the suspension", false };
		TUOption<float> SuspensionSmoothnessValues = {Physics,"Suspension Smoothness", DefaultSuspensionSmoothness, DefaultSuspensionSmoothness, 0, 10, 0.1, "", "Set the smoothness of the suspension", false };
		TUOption<FVehicleWheels> WheelsBrakeTorqueValues = {Physics, "Wheels Brake Torque",
			{ DefaultFrontWheelsBrakeTorque, DefaultRearWheelsBrakeTorque, DefaultFrontWheelsBrakeTorque, DefaultRearWheelsBrakeTorque },
			{ DefaultFrontWheelsBrakeTorque, DefaultRearWheelsBrakeTorque, DefaultFrontWheelsBrakeTorque, DefaultRearWheelsBrakeTorque },
			{ 0, 0, 0, 0 },
			{ 10000, 10000, 10000, 10000 },
			10, "Nm",
			"Set the brake torque of the wheels",
			false };
		TUOption<FVehicleWheels> WheelsHandBrakeTorqueValues = {Physics, "Wheels Hand Brake Torque",
			{ DefaultFrontWheelsHandBrakeTorque, DefaultRearWheelsHandBrakeTorque, DefaultFrontWheelsHandBrakeTorque, DefaultRearWheelsHandBrakeTorque },
			{ DefaultFrontWheelsHandBrakeTorque, DefaultRearWheelsHandBrakeTorque, DefaultFrontWheelsHandBrakeTorque, DefaultRearWheelsHandBrakeTorque },
			{ 0, 0, 0, 0 },
			{ 10000, 10000, 10000, 10000 },
			10, "Nm",
			"Set the hand brake torque of the wheels",
			false };

		UOptionVehicle* VehicleMasses = NewObject<UOptionVehicle>(GetTransientPackage(), UOptionVehicle::StaticClass());
		UOptionFloat* HorsePower = NewObject<UOptionFloat>(GetTransientPackage(), UOptionFloat::StaticClass());
		UOptionFloat* MaxRpm = NewObject<UOptionFloat>(GetTransientPackage(), UOptionFloat::StaticClass());
		UOptionFloat* MaxTorque = NewObject<UOptionFloat>(GetTransientPackage(), UOptionFloat::StaticClass());
		UOptionFloat* AngleRatio = NewObject<UOptionFloat>(GetTransientPackage(), UOptionFloat::StaticClass());
		UOptionFloat* FrontRearSplit = NewObject<UOptionFloat>(GetTransientPackage(), UOptionFloat::StaticClass());
		UOptionFloat* DragCoefficient = NewObject<UOptionFloat>(GetTransientPackage(), UOptionFloat::StaticClass());
		UOptionFloat* DownForceCoefficient = NewObject<UOptionFloat>(GetTransientPackage(), UOptionFloat::StaticClass());
		UOptionFloat* AutomaticGearboxUpShiftRpm = NewObject<UOptionFloat>(GetTransientPackage(), UOptionFloat::StaticClass());
		UOptionFloat* AutomaticGearboxDownShiftRpm = NewObject<UOptionFloat>(GetTransientPackage(), UOptionFloat::StaticClass());
		UOptionFloat* GearboxChangeTime = NewObject<UOptionFloat>(GetTransientPackage(), UOptionFloat::StaticClass());
		UOptionFloat* GearboxTransmissionEfficiency = NewObject<UOptionFloat>(GetTransientPackage(), UOptionFloat::StaticClass());
		UOptionWheels* WheelsFrictionForceMultiplier = NewObject<UOptionWheels>(GetTransientPackage(), UOptionWheels::StaticClass());
		UOptionFloat* MaxWheelsSteeringAngle = NewObject<UOptionFloat>(GetTransientPackage(), UOptionFloat::StaticClass());
		UOptionFloat* SuspensionMaxRaise = NewObject<UOptionFloat>(GetTransientPackage(), UOptionFloat::StaticClass());
		UOptionFloat* SuspensionMaxDrop = NewObject<UOptionFloat>(GetTransientPackage(), UOptionFloat::StaticClass());
		UOptionFloat* SuspensionDumpRatio = NewObject<UOptionFloat>(GetTransientPackage(), UOptionFloat::StaticClass());
		UOptionFloat* SuspensionSpringRatio = NewObject<UOptionFloat>(GetTransientPackage(), UOptionFloat::StaticClass());
		UOptionFloat* SuspensionPreload = NewObject<UOptionFloat>(GetTransientPackage(), UOptionFloat::StaticClass());
		UOptionFloat* SuspensionSmoothness = NewObject<UOptionFloat>(GetTransientPackage(), UOptionFloat::StaticClass());
		UOptionWheels* WheelsBrakeTorque = NewObject<UOptionWheels>(GetTransientPackage(), UOptionWheels::StaticClass());
		UOptionWheels* WheelsHandBrakeTorque = NewObject<UOptionWheels>(GetTransientPackage(), UOptionWheels::StaticClass());

		VehicleMasses->Initialize(VehicleMassesValues);
		HorsePower->Initialize(HorsePowerValues);
		MaxRpm->Initialize(MaxRpmValues);
		MaxTorque->Initialize(MaxTorqueValues);
		AngleRatio->Initialize(AngleRatioValues);
		FrontRearSplit->Initialize(FrontRearSplitValues);
		DragCoefficient->Initialize(DragCoefficientValues);
		DownForceCoefficient->Initialize(DownForceCoefficientValues);
		AutomaticGearboxUpShiftRpm->Initialize(AutomaticGearboxUpShiftRpmValues);
		AutomaticGearboxDownShiftRpm->Initialize(AutomaticGearboxDownShiftRpmValues);
		GearboxChangeTime->Initialize(GearboxChangeTimeValues);
		GearboxTransmissionEfficiency->Initialize(GearboxTransmissionEfficiencyValues);
		WheelsFrictionForceMultiplier->Initialize(WheelsFrictionForceMultiplierValues);
		MaxWheelsSteeringAngle->Initialize(MaxWheelsSteeringAngleValues);
		SuspensionMaxRaise->Initialize(SuspensionMaxRaiseValues);
		SuspensionMaxDrop->Initialize(SuspensionMaxDropValues);
		SuspensionDumpRatio->Initialize(SuspensionDumpRatioValues);
		SuspensionSpringRatio->Initialize(SuspensionSpringRatioValues);
		SuspensionPreload->Initialize(SuspensionPreloadValues);
		SuspensionSmoothness->Initialize(SuspensionSmoothnessValues);
		WheelsBrakeTorque->Initialize(WheelsBrakeTorqueValues);
		WheelsHandBrakeTorque->Initialize(WheelsHandBrakeTorqueValues);
		
		OptionMap.Add(TEXT("VehicleMasses"), VehicleMasses);
		OptionMap.Add(TEXT("HorsePower"), HorsePower);
		OptionMap.Add(TEXT("MaxRpm"), MaxRpm);
		OptionMap.Add(TEXT("MaxTorque"), MaxTorque);
		OptionMap.Add(TEXT("AngleRatio"), AngleRatio);
		OptionMap.Add(TEXT("FrontRearSplit"), FrontRearSplit);
		OptionMap.Add(TEXT("DragCoefficient"), DragCoefficient);
		OptionMap.Add(TEXT("DownForceCoefficient"), DownForceCoefficient);
		OptionMap.Add(TEXT("AutomaticGearboxUpShiftRpm"), AutomaticGearboxUpShiftRpm);
		OptionMap.Add(TEXT("AutomaticGearboxDownShiftRpm"), AutomaticGearboxDownShiftRpm);
		OptionMap.Add(TEXT("GearboxChangeTime"), GearboxChangeTime);
		OptionMap.Add(TEXT("GearboxTransmissionEfficiency"), GearboxTransmissionEfficiency);
		OptionMap.Add(TEXT("WheelsFrictionForceMultiplier"), WheelsFrictionForceMultiplier);
		OptionMap.Add(TEXT("MaxWheelsSteeringAngle"), MaxWheelsSteeringAngle);
		OptionMap.Add(TEXT("SuspensionMaxRaise"), SuspensionMaxRaise);
		OptionMap.Add(TEXT("SuspensionMaxDrop"), SuspensionMaxDrop);
		OptionMap.Add(TEXT("SuspensionDumpRatio"), SuspensionDumpRatio);
		OptionMap.Add(TEXT("SuspensionSpringRatio"), SuspensionSpringRatio);
		OptionMap.Add(TEXT("SuspensionPreload"), SuspensionPreload);
		OptionMap.Add(TEXT("SuspensionSmoothness"), SuspensionSmoothness);
		OptionMap.Add(TEXT("WheelsBrakeTorque"), WheelsBrakeTorque);
		OptionMap.Add(TEXT("WheelsHandBrakeTorque"), WheelsHandBrakeTorque);
	}
	
	static constexpr float DefaultChassisMass = 1000.0f;
	static constexpr float DefaultWheelMass = 250.0f;
	static constexpr float DefaultHorsePower = 685.8f;
	static constexpr float DefaultMaxRpm = 6000.0f;
	static constexpr float DefaultMaxTorque = 600.0f;
	static constexpr float DefaultAngleRatio = 0.5f;
	static constexpr float DefaultFrontRearSplit = 0.5f;
	static constexpr float DefaultDragCoefficient = 0.3f;
	static constexpr float DefaultDownForceCoefficient = 0.3f;
	static constexpr float DefaultAutomaticGearboxUpShiftRpm = 4500.0f;
	static constexpr float DefaultAutomaticGearboxDownShiftRpm = 2000.0f;
	static constexpr float DefaultGearboxChangeTime = 0.4f;
	static constexpr float DefaultGearboxTransmissionEfficiency = 0.95f;
	static constexpr float DefaultWheelsFrictionForceMultiplier = 2.0f;
	static constexpr float DefaultMaxWheelsSteeringAngle = 50.0f;
	static constexpr float DefaultSuspensionMaxRaise = 10.0f;
	static constexpr float DefaultSuspensionMaxDrop = 10.0f;
	static constexpr float DefaultSuspensionDumpRatio = 0.5f;
	static constexpr float DefaultSuspensionSpringRatio = 250.0f;
	static constexpr float DefaultSuspensionPreload = 50.0f;
	static constexpr float DefaultSuspensionSmoothness = .0f;
	static constexpr float DefaultFrontWheelsBrakeTorque = 4500.0f;
	static constexpr float DefaultRearWheelsBrakeTorque = 1500.0f;
	static constexpr float DefaultFrontWheelsHandBrakeTorque = 6000.0f;
	static constexpr float DefaultRearWheelsHandBrakeTorque = 3000.0f;
	
	
};

USTRUCT(NotBlueprintType)
struct FDefaultAdvanceUserOption
{
	GENERATED_BODY()

	FDefaultAdvanceUserOption() = default;
	
	static void Create(TMap<FName, UOptionBase*> &OptionMap)
	{
		TUOption<BVehicleWheels> WheelsAffectedByBrakesValues = {Advance, "Wheels Affected By Brakes",
				DefaultWheelsAffectedByBrakes,
				DefaultWheelsAffectedByBrakes,
				{ false, false, false, false },
				{ true, true, true, true },
				1, "",
				"Set which wheels are affected by the brakes",
				true };
		
		TUOption<BVehicleWheels> WheelsAffectedByHandBrakesValues = {Advance, "Wheels Affected By Hand Brakes",
			DefaultWheelsAffectedByHandBrakes,
			DefaultWheelsAffectedByHandBrakes,
			{ false, false, false, false },
			{ true, true, true, true },
			1, "",
			"Set which wheels are affected by the hand brakes",
			true };
		TUOption<BVehicleWheels> WheelsAffectedByEngineValues = {Advance, "Wheels Affected By Engine",
			DefaultWheelsAffectedByEngine,
			DefaultWheelsAffectedByEngine,
			{ false, false, false, false },
			{ true, true, true, true },
			1, "",
			"Set which wheels are affected by the engine",
			false };
		
		TUOption<BVehicleWheels> WheelsAffectedBySteeringValues = {Advance, "Wheels Affected By Steering",
			DefaultWheelsAffectedBySteering,
			DefaultWheelsAffectedBySteering,
			{ false, false, false, false },
			{ true, true, true, true },
			1, "",
			"Set which wheels are affected by the steering",
			true };
		TUOption<BVehicleWheels> WheelsSuspensionEnabledValues = {Advance, "Wheels Suspension Enabled",
			DefaultWheelsSuspensionEnabled,
			DefaultWheelsSuspensionEnabled,
			{ false, false, false, false },
			{ true, true, true, true },
			1, "",
			"Set which wheels have the suspension enabled",
			true };

		UOptionWheels* WheelsAffectedByBrakes = NewObject<UOptionWheels>(GetTransientPackage(), UOptionWheels::StaticClass());
		UOptionWheels* WheelsAffectedByHandBrakes = NewObject<UOptionWheels>(GetTransientPackage(), UOptionWheels::StaticClass());
		UOptionWheels* WheelsAffectedByEngine = NewObject<UOptionWheels>(GetTransientPackage(), UOptionWheels::StaticClass());
		UOptionWheels* WheelsAffectedBySteering = NewObject<UOptionWheels>(GetTransientPackage(), UOptionWheels::StaticClass());
		UOptionWheels* WheelsSuspensionEnabled = NewObject<UOptionWheels>(GetTransientPackage(), UOptionWheels::StaticClass());

		WheelsAffectedByBrakes->Initialize(WheelsAffectedByBrakesValues);
		WheelsAffectedByHandBrakes->Initialize(WheelsAffectedByHandBrakesValues);
		WheelsAffectedByEngine->Initialize(WheelsAffectedByEngineValues);
		WheelsAffectedBySteering->Initialize(WheelsAffectedBySteeringValues);
		WheelsSuspensionEnabled->Initialize(WheelsSuspensionEnabledValues);
		
		OptionMap.Add(TEXT("WheelsAffectedByBrakes"), WheelsAffectedByBrakes);
		OptionMap.Add(TEXT("WheelsAffectedByHandBrakes"), WheelsAffectedByHandBrakes);
		OptionMap.Add(TEXT("WheelsAffectedByEngine"), WheelsAffectedByEngine);
		OptionMap.Add(TEXT("WheelsAffectedBySteering"), WheelsAffectedBySteering);
		OptionMap.Add(TEXT("WheelsSuspensionEnabled"), WheelsSuspensionEnabled);
	}
	
	static constexpr BVehicleWheels DefaultWheelsAffectedByBrakes = { false, false, false, false };
	static constexpr BVehicleWheels DefaultWheelsAffectedByHandBrakes = { false, false, false, false };
	static constexpr BVehicleWheels DefaultWheelsAffectedByEngine = { true, true, true, true };
	static constexpr BVehicleWheels DefaultWheelsAffectedBySteering = { true, false, true, false };
	static constexpr BVehicleWheels DefaultWheelsSuspensionEnabled = { true, true, true, true };
	
	
};

UCLASS(BlueprintType, Blueprintable)
class SIMULATOR_API UDefaultPlayerOptions : public UObject
{
	GENERATED_BODY()
	
	bool bUseDefaultBasicUserOption = true;
	bool bUseDefaultPhysicsUserOption = true;
	bool bUseDefaultAdvanceUserOption = true;

	const FString BasicPath = "DefaultPlayerOptions.json";

	UOptionBase* GetOption(const FName OptionName);
	int UpdateBasicOptionValue(const FString& OptionName);
	int UpdatePhysicsOptionValue(const FString& OptionName, const float& Value);
	int UpdateAdvanceOptionValue(const FString& OptionName, const UINT8 WheelIndex);
public:
	UDefaultPlayerOptions();

	UFUNCTION(BlueprintCallable, Category = "PlayerOptions")
	static UDefaultPlayerOptions* GetPlayerOptionsInstance();
	
	static UDefaultPlayerOptions* PlayerOptionsInstance;

	UFUNCTION(BlueprintCallable, Category = "PlayerOptions")
	void PrintOptionMap();
	
	UFUNCTION(BlueprintCallable, Category = "PlayerOptions")
	int UpdateOptionValue(const EOptionType OptionType, const FString& OptionName, const float& Value, const uint8 WheelIndex = 0);
	UFUNCTION(BlueprintCallable, Category = "PlayerOptions")
	bool TryLoadUserOption(const FString& Path);
	UFUNCTION(BlueprintCallable, Category = "PlayerOptions")
	bool TrySaveUserOption(const FString& Path);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerOptions")
	TMap<FName, UOptionBase*> OptionMap;
};
