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
USTRUCT(BlueprintType)                                     \
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
USTRUCT(BlueprintType)                                                     \
struct StructName                                                          \
{                                                                          \
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleBodyParts") \
Type Chassis;                                                          \
\
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VehicleBodyParts") \
WheelStructName Wheels;                                                \
};

DEFINE_VEHICLE_WHEEL_PARTS_STRUCT(BVehicleWheels, bool)

USTRUCT(BlueprintType, Blueprintable)
struct FVehicleWheels
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wheels")
	float FrontLeftWheel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wheels")
	float FrontRightWheel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wheels")
	float RearLeftWheel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wheels")
	float RearRightWheel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wheels")
	FString FrontLeftWheelName = "Front Left Wheel";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wheels")
	FString FrontRightWheelName = "Front Right Wheel";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wheels")
	FString RearLeftWheelName = "Rear Left Wheel";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wheels")
	FString RearRightWheelName = "Rear Right Wheel";

	
};

USTRUCT(BlueprintType)
struct FVehicle
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle")
	float Chassis;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle")
	FVehicleWheels Wheels;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vehicle")
	FString ChassisName = "Chassis";
	
};

UENUM(BlueprintType, Category = "OptionButton|Enum")
enum EDriveMode : uint8
{
	AllWheels = 0,
	FrontWheels = 1,
	RearWheels = 2
};
UENUM(BlueprintType, Category = "OptionButton|Enum")
enum ESettingsType : uint8
{
	Basic = 0,
	Physics = 1,
	Advance = 2
};
UENUM(BlueprintType)
enum EOptionButtonType : uint8
{
	Option_BoolButton = 0,
	Option_ValueButton = 1,
	Option_CustomValueButton = 2,
	Option_WheelsBoolButton = 3,
	Option_WheelsValueButton = 4,
	Option_VehicleValueButton = 5,
};

UCLASS(BlueprintType)
class SIMULATOR_API UOptionBase : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|Logic Class|Base")
	TEnumAsByte<ESettingsType> SettingsType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|Logic Class|Base")
	TEnumAsByte<EOptionButtonType> BaseOptionButtonType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|Logic Class|Base")
	FString OptionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|Logic Class|Base")
	FString OptionTooltip;
	
	UFUNCTION(BlueprintCallable, Category = "OptionButton|Logic Class|Base")
	void InitializeBase(const ESettingsType &Type, const EOptionButtonType &OptionType, const FString &Name, const FString &Tooltip)
	{
		this->AddToRoot();
		this->OptionName = Name;
		this->BaseOptionButtonType = OptionType;
		this->SettingsType = Type;
		this->OptionTooltip = Tooltip;
	}
};
template <typename T>
USTRUCT(NotBlueprintType)
struct TUOption
{
public:
	TEnumAsByte<ESettingsType> OptionType;
	TEnumAsByte<EOptionButtonType> OptionsButtonType;
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
		const ESettingsType &Type,
		const EOptionButtonType &OptionType,
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
	OptionsButtonType(OptionType),
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
	float FValue;
	float FDefaultValue;
	float FMinValue;
	float FMaxValue;
	float Step;
	FString Unit;
	FString Tooltip;
	bool IsAffectingOtherOptions;
	void Initialize(const TUOption<float> &Option)
	{
		InitializeBase(Option.OptionType, Option.OptionsButtonType, Option.OptionName, Option.Tooltip);
		this->FValue = Option.Value;
		this->FDefaultValue = Option.DefaultValue;
		this->FMinValue = Option.MinValue;
		this->FMaxValue = Option.MaxValue;
		this->Step = Option.Step;
		this->Unit = Option.Unit;
		this->IsAffectingOtherOptions = Option.IsAffectingOtherOptions;
	}

	UFUNCTION(BlueprintCallable, Category = "OptionButton|Logic Class|Float")
	float ReadFloatValue() const
	{
		return FValue;
	}

	UFUNCTION(BlueprintCallable, Category = "OptionButton|Logic Class|Float")
	FString ReadFloatUnit() const
	{
		return " " + Unit;
	}

	static UOptionFloat* CreateOption(const TUOption<float> &Option)
	{
		UOptionFloat* NewOption = NewObject<UOptionFloat>(GetTransientPackage(), UOptionFloat::StaticClass());
		NewOption->Initialize(Option);
		return NewOption;
	}
};
UCLASS(BlueprintType)
class UOptionBool : public UOptionBase
{
	GENERATED_BODY()

public:
	bool BValue;
	bool BDefaultValue;
	FString Tooltip;
	bool IsAffectingOtherOptions;
	void Initialize(const TUOption<bool> &Option)
	{
		InitializeBase(Option.OptionType, Option.OptionsButtonType, Option.OptionName, Option.Tooltip);
		this->BValue = Option.Value;
		this->BDefaultValue = Option.DefaultValue;
		this->IsAffectingOtherOptions = Option.IsAffectingOtherOptions;
	}

	UFUNCTION(BlueprintCallable, Category = "OptionButton|Logic Class|Bool")
	bool ReadBoolValue() const
	{
		return BValue;
	}

	static UOptionBool* CreateOption(const TUOption<bool> &Option)
	{
		UOptionBool* NewOption = NewObject<UOptionBool>(GetTransientPackage(), UOptionBool::StaticClass());
		NewOption->Initialize(Option);
		return NewOption;
	}
	
};

UCLASS(BlueprintType)
class UOptionDriveMode : public UOptionBase
{
	GENERATED_BODY()

public:
	TEnumAsByte<EDriveMode> DriveModeValue;
	TEnumAsByte<EDriveMode> DriveModeDefaultValue;
	TEnumAsByte<EDriveMode> DriveModeMinValue;
	TEnumAsByte<EDriveMode> DriveModeMaxValue;
	float Step;
	FString Tooltip;
	bool IsAffectingOtherOptions;
	void Initialize(const TUOption<EDriveMode> &Option)
	{
		InitializeBase(Option.OptionType, Option.OptionsButtonType, Option.OptionName, Option.Tooltip);
		this->DriveModeValue = Option.Value;
		this->DriveModeDefaultValue = Option.DefaultValue;
		this->DriveModeMinValue = Option.MinValue;
		this->DriveModeMaxValue = Option.MaxValue;
		this->Step = Option.Step;
		this->IsAffectingOtherOptions = Option.IsAffectingOtherOptions;
	}
	
	UFUNCTION(BlueprintCallable, Category = "OptionButton|Logic Class|EDriveMode")
	TEnumAsByte<EDriveMode> ReadDriveModeValue() const
	{
		return DriveModeValue;
	}

	static UOptionDriveMode* CreateOption(const TUOption<EDriveMode> &Option)
	{
		UOptionDriveMode* NewOption = NewObject<UOptionDriveMode>(GetTransientPackage(), UOptionDriveMode::StaticClass());
		NewOption->Initialize(Option);
		return NewOption;
	}
};

UCLASS(BlueprintType)
class UOptionVehicle : public UOptionBase
{
	GENERATED_BODY()
public:

	FVehicle FVehicleValue;
	FVehicle FVehicleDefaultValue;
	FVehicle FVehicleMinValue;
	FVehicle FVehicleMaxValue;
	float Step;
	FString Unit;
	bool IsAffectingOtherOptions;

	void Initialize(const TUOption<FVehicle> &Option)
	{
		InitializeBase(Option.OptionType, Option.OptionsButtonType, Option.OptionName, Option.Tooltip);
		this->FVehicleValue = Option.Value;
		this->FVehicleDefaultValue = Option.DefaultValue;
		this->FVehicleMinValue = Option.MinValue;
		this->FVehicleMaxValue = Option.MaxValue;
		this->Step = Option.Step;
		this->Unit = Option.Unit;
		this->IsAffectingOtherOptions = Option.IsAffectingOtherOptions;
	}

	UFUNCTION(BlueprintCallable, Category = "OptionButton|Logic Class|FVehicle")
	FVehicle ReadVehicleValue() const
	{
		return FVehicleValue;
	}

	UFUNCTION(BlueprintCallable, Category = "OptionButton|Logic Class|FVehicle")
	FString ReadVehicleUnit() const
	{
		return " " + Unit;
	}
	
	static UOptionVehicle* CreateOption(const TUOption<FVehicle> &Option)
	{
		UOptionVehicle* NewOption = NewObject<UOptionVehicle>(GetTransientPackage(), UOptionVehicle::StaticClass());
		NewOption->Initialize(Option);
		return NewOption;
	}
	
};

UCLASS(BlueprintType)
class UOptionWheels : public UOptionBase
{
	GENERATED_BODY()
public:
	FVehicleWheels FVehicleWheelsValue;
	FVehicleWheels FVehicleWheelsDefaultValue;
	FVehicleWheels FVehicleWheelsMinValue;
	FVehicleWheels FVehicleWheelsMaxValue;
	float Step;
	FString Unit;
	FString Tooltip;
	bool IsAffectingOtherOptions;

	void Initialize(const TUOption<FVehicleWheels> &Option)
	{
		InitializeBase(Option.OptionType, Option.OptionsButtonType, Option.OptionName, Option.Tooltip);
		this->FVehicleWheelsValue = Option.Value;
		this->FVehicleWheelsDefaultValue = Option.DefaultValue;
		this->FVehicleWheelsMinValue = Option.MinValue;
		this->FVehicleWheelsMaxValue = Option.MaxValue;
		this->Step = Option.Step;
		this->Unit = Option.Unit;
		this->IsAffectingOtherOptions = Option.IsAffectingOtherOptions;
	}
	void Initialize(const TUOption<BVehicleWheels> &Option)
	{
		InitializeBase(Option.OptionType, Option.OptionsButtonType, Option.OptionName, Option.Tooltip);
		this->FVehicleWheelsValue = ConvertToVehicleWheels(Option.Value);
		this->FVehicleWheelsDefaultValue = ConvertToVehicleWheels(Option.DefaultValue);
		this->FVehicleWheelsMinValue = ConvertToVehicleWheels(Option.MinValue);
		this->FVehicleWheelsMaxValue = ConvertToVehicleWheels(Option.MaxValue);
		this->Step = Option.Step;
		this->Unit = Option.Unit;
		this->IsAffectingOtherOptions = Option.IsAffectingOtherOptions;
	}

	UFUNCTION(BlueprintCallable, Category = "OptionButton|Logic Class|FVehicleWheels")
	FVehicleWheels ReadVehicleWheelsValue() const
	{
		return FVehicleWheelsValue;
	}

	UFUNCTION(BlueprintCallable, Category = "OptionButton|Logic Class|FVehicleWheels")
	FString ReadVehicleWheelsUnit() const
	{
		return " " + Unit;
	}

	static UOptionWheels* CreateOption(const TUOption<FVehicleWheels> &Option)
	{
		UOptionWheels* NewOption = NewObject<UOptionWheels>(GetTransientPackage(), UOptionWheels::StaticClass());
		NewOption->Initialize(Option);
		return NewOption;
	}
	static UOptionWheels* CreateOption(const TUOption<BVehicleWheels> &Option)
	{
		UOptionWheels* NewOption = NewObject<UOptionWheels>(GetTransientPackage(), UOptionWheels::StaticClass());
		NewOption->Initialize(Option);
		return NewOption;
	}

	FVehicleWheels& operator=(const BVehicleWheels &Other)
	{
		this->FVehicleWheelsValue = ConvertToVehicleWheels(Other);
		return this->FVehicleWheelsValue;
	}

private:
	static FVehicleWheels ConvertToVehicleWheels(const BVehicleWheels& Source)
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

	static void Create(TMap<FName, UOptionBase*> &OptionMap)
	{
		TUOption<bool> ManualGearboxValues = {Basic, Option_BoolButton, "Manual Gearbox", bDefaultManualGearbox, bDefaultManualGearbox, false, true, 1, "", "Use manual gearbox", true};
		TUOption<bool> AutomaticReverseValues = {Basic, Option_BoolButton, "Automatic Reverse", bDefaultAutomaticReverse, bDefaultAutomaticReverse, false, true, 1, "", "Use automatic reverse", true};
		TUOption<EDriveMode> DriveModeValues = {Basic, Option_CustomValueButton, "Drive Mode", DefaultDriveMode, DefaultDriveMode, EDriveMode::AllWheels, EDriveMode::RearWheels, 1, "", "Select drive mode", true};
		TUOption<bool> SuspensionEnabledValues = {Basic, Option_BoolButton, "Suspension Enabled", bDefaultSuspensionEnabled, bDefaultSuspensionEnabled, false, true, 1, "", "Enable suspension", true};
		TUOption<bool> WheelFrictionEnabledValues = {Basic, Option_BoolButton, "Wheel Friction Enabled", bDefaultWheelFrictionEnabled, bDefaultWheelFrictionEnabled, false, true, 1, "", "Enable wheel friction", true};
		TUOption<bool> TractionControlEnabledValues = {Basic, Option_BoolButton, "Traction Control Enabled", bDefaultTractionControlEnabled, bDefaultTractionControlEnabled, false, true, 1, "", "Enable traction control", true};
		TUOption<bool> AbsEnabledValues = {Basic, Option_BoolButton, "ABS Enabled", bDefaultAbsEnabled, bDefaultAbsEnabled, false, true, 1, "", "Enable ABS", true};

		UOptionBool* ManualGearbox = UOptionBool::CreateOption(ManualGearboxValues);
		UOptionBool* AutomaticReverse = UOptionBool::CreateOption(AutomaticReverseValues);
		UOptionDriveMode* DriveMode = UOptionDriveMode::CreateOption(DriveModeValues);
		UOptionBool* SuspensionEnabled = UOptionBool::CreateOption(SuspensionEnabledValues);
		UOptionBool* WheelFrictionEnabled = UOptionBool::CreateOption(WheelFrictionEnabledValues);
		UOptionBool* TractionControlEnabled = UOptionBool::CreateOption(TractionControlEnabledValues);
		UOptionBool* AbsEnabled = UOptionBool::CreateOption(AbsEnabledValues);

		OptionMap.Add(FName(ManualGearbox->OptionName), ManualGearbox);
		OptionMap.Add(FName(AutomaticReverse->OptionName), AutomaticReverse);
		OptionMap.Add(FName(DriveMode->OptionName), DriveMode);
		OptionMap.Add(FName(SuspensionEnabled->OptionName), SuspensionEnabled);
		OptionMap.Add(FName(WheelFrictionEnabled->OptionName), WheelFrictionEnabled);
		OptionMap.Add(FName(TractionControlEnabled->OptionName), TractionControlEnabled);
		OptionMap.Add(FName(AbsEnabled->OptionName), AbsEnabled);
		
	}
	static constexpr bool bDefaultManualGearbox = false;
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
		
		TUOption<FVehicle> VehicleMassesValues = {Physics, Option_VehicleValueButton, "Vehicle Masses",
		{ DefaultChassisMass, DefaultWheelMass, DefaultWheelMass, DefaultWheelMass, DefaultWheelMass},
		{ DefaultChassisMass, DefaultWheelMass, DefaultWheelMass, DefaultWheelMass, DefaultWheelMass},
		{0, 0, 0, 0, 0},
		{10000, 10000, 10000, 10000, 10000},
		10, "kg",
		"Set the masses of the vehicle parts",
		false };
		TUOption<float> HorsePowerValues = {Physics, Option_ValueButton, "Horse Power", DefaultHorsePower, DefaultHorsePower, 0, 1000, 1, "kW", "Set the power of the engine, [kW]", true };
		TUOption<float> MaxRpmValues = {Physics, Option_ValueButton, "Max RPM", DefaultMaxRpm, DefaultMaxRpm, 0, 10000, 1, "RPM", "Set the maximum RPM of the engine", true };
		TUOption<float> MaxTorqueValues = {Physics, Option_ValueButton, "Max Torque", DefaultMaxTorque, DefaultMaxTorque, 0, 1000, 1, "Nm", "Set the maximum torque of the engine", true };
		// Ratio of the wheelbase to the track width
		TUOption<float> AngleRatioValues = {Physics, Option_ValueButton, "Angle Ratio", DefaultAngleRatio, DefaultAngleRatio, 0, 1, 0.1, "", "Set the ratio of the wheelbase to the track width", false };
		// Ratio of front to rear torque distribution, <0.5 means more torque to the front wheels, >0.5 means more torque to the rear wheels
		TUOption<float> FrontRearSplitValues = {Physics, Option_ValueButton, "Front Rear Split", DefaultFrontRearSplit, DefaultFrontRearSplit, 0, 1, 0.1, "", "Set the ratio of front to rear torque distribution", false };
		// Drag coefficient of the vehicle
		TUOption<float> DragCoefficientValues = {Physics, Option_ValueButton, "Drag Coefficient", DefaultDragCoefficient, DefaultDragCoefficient, 0, 1, 0.1, "", "Set the drag coefficient of the vehicle", false };
		// Rolling resistance coefficient of the vehicle
		TUOption<float> DownForceCoefficientValues = {Physics, Option_ValueButton, "Down Force Coefficient", DefaultDownForceCoefficient, DefaultDownForceCoefficient, 0, 1, 0.1, "", "Set the down force coefficient of the vehicle", false };
		TUOption<float> AutomaticGearboxUpShiftRpmValues = { Physics, Option_ValueButton, "Automatic Gearbox Up Shift RPM", DefaultAutomaticGearboxUpShiftRpm, DefaultAutomaticGearboxUpShiftRpm, 0, 10000, 1, "RPM", "Set the RPM at which the automatic gearbox will upshift", false };
		TUOption<float> AutomaticGearboxDownShiftRpmValues = {Physics, Option_ValueButton, "Automatic Gearbox Down Shift RPM", DefaultAutomaticGearboxDownShiftRpm, DefaultAutomaticGearboxDownShiftRpm, 0, 10000, 1, "RPM", "Set the RPM at which the automatic gearbox will downshift", false };
		TUOption<float> GearboxChangeTimeValues = {Physics, Option_ValueButton, "Gearbox Change Time", DefaultGearboxChangeTime, DefaultGearboxChangeTime, 0, 10, 0.1, "s", "Set the time it takes to change gears", false };
		TUOption<float> GearboxTransmissionEfficiencyValues = {Physics, Option_ValueButton, "Gearbox Transmission Efficiency", DefaultGearboxTransmissionEfficiency, DefaultGearboxTransmissionEfficiency, 0, 1, 0.1, "", "Set the efficiency of the gearbox transmission", false };
		TUOption<float> MaxWheelsSteeringAngleValues = {Physics, Option_ValueButton, "Max Wheels Steering Angle", DefaultMaxWheelsSteeringAngle, DefaultMaxWheelsSteeringAngle, 0, 90, 1, "deg", "Set the maximum steering angle of the wheels", false };
		TUOption<FVehicleWheels> WheelsFrictionForceMultiplierValues = {Physics, Option_WheelsValueButton, "Wheels Friction Force Multiplier",
			{ DefaultWheelsFrictionForceMultiplier, DefaultWheelsFrictionForceMultiplier,DefaultWheelsFrictionForceMultiplier,DefaultWheelsFrictionForceMultiplier },
			{ DefaultWheelsFrictionForceMultiplier, DefaultWheelsFrictionForceMultiplier,DefaultWheelsFrictionForceMultiplier,DefaultWheelsFrictionForceMultiplier },
			{ 0, 0, 0, 0 },
			{ 10, 10, 10, 10 },
			0.1, "",
			"Set the friction force multiplier of the wheels",
			false };
		TUOption<float> SuspensionMaxRaiseValues = {Physics, Option_ValueButton, "Suspension Max Raise", DefaultSuspensionMaxRaise, DefaultSuspensionMaxRaise, 0, 100, 1, "cm", "Set the maximum raise of the suspension", false };
		TUOption<float> SuspensionMaxDropValues = {Physics, Option_ValueButton, "Suspension Max Drop", DefaultSuspensionMaxDrop, DefaultSuspensionMaxDrop, 0, 100, 1, "cm", "Set the maximum drop of the suspension", false };
		TUOption<float> SuspensionDumpRatioValues = {Physics, Option_ValueButton, "Suspension Dump Ratio", DefaultSuspensionDumpRatio, DefaultSuspensionDumpRatio, 0, 1, 0.1, "", "Set the dump ratio of the suspension", false };
		TUOption<float> SuspensionSpringRatioValues = {Physics, Option_ValueButton, "Suspension Spring Ratio", DefaultSuspensionSpringRatio, DefaultSuspensionSpringRatio, 0, 1000, 1, "", "Set the spring ratio of the suspension", false };
		TUOption<float> SuspensionPreloadValues = {Physics, Option_ValueButton, "Suspension Preload", DefaultSuspensionPreload, DefaultSuspensionPreload, 0, 100, 1, "cm", "Set the preload of the suspension", false };
		TUOption<float> SuspensionSmoothnessValues = {Physics, Option_ValueButton, "Suspension Smoothness", DefaultSuspensionSmoothness, DefaultSuspensionSmoothness, 0, 10, 0.1, "", "Set the smoothness of the suspension", false };
		TUOption<FVehicleWheels> WheelsBrakeTorqueValues = {Physics, Option_WheelsValueButton, "Wheels Brake Torque",
			{ DefaultFrontWheelsBrakeTorque, DefaultRearWheelsBrakeTorque, DefaultFrontWheelsBrakeTorque, DefaultRearWheelsBrakeTorque },
			{ DefaultFrontWheelsBrakeTorque, DefaultRearWheelsBrakeTorque, DefaultFrontWheelsBrakeTorque, DefaultRearWheelsBrakeTorque },
			{ 0, 0, 0, 0 },
			{ 10000, 10000, 10000, 10000 },
			10, "Nm",
			"Set the brake torque of the wheels",
			false };
		TUOption<FVehicleWheels> WheelsHandBrakeTorqueValues = {Physics, Option_WheelsValueButton, "Wheels Hand Brake Torque",
			{ DefaultFrontWheelsHandBrakeTorque, DefaultRearWheelsHandBrakeTorque, DefaultFrontWheelsHandBrakeTorque, DefaultRearWheelsHandBrakeTorque },
			{ DefaultFrontWheelsHandBrakeTorque, DefaultRearWheelsHandBrakeTorque, DefaultFrontWheelsHandBrakeTorque, DefaultRearWheelsHandBrakeTorque },
			{ 0, 0, 0, 0 },
			{ 10000, 10000, 10000, 10000 },
			10, "Nm",
			"Set the hand brake torque of the wheels",
			false };

		UOptionVehicle* VehicleMasses = UOptionVehicle::CreateOption(VehicleMassesValues);
		UOptionFloat* HorsePower = UOptionFloat::CreateOption(HorsePowerValues);
		UOptionFloat* MaxRpm = UOptionFloat::CreateOption(MaxRpmValues);
		UOptionFloat* MaxTorque = UOptionFloat::CreateOption(MaxTorqueValues);
		UOptionFloat* AngleRatio = UOptionFloat::CreateOption(AngleRatioValues);
		UOptionFloat* FrontRearSplit = UOptionFloat::CreateOption(FrontRearSplitValues);
		UOptionFloat* DragCoefficient = UOptionFloat::CreateOption(DragCoefficientValues);
		UOptionFloat* DownForceCoefficient = UOptionFloat::CreateOption(DownForceCoefficientValues);
		UOptionFloat* AutomaticGearboxUpShiftRpm = UOptionFloat::CreateOption(AutomaticGearboxUpShiftRpmValues);
		UOptionFloat* AutomaticGearboxDownShiftRpm = UOptionFloat::CreateOption(AutomaticGearboxDownShiftRpmValues);
		UOptionFloat* GearboxChangeTime = UOptionFloat::CreateOption(GearboxChangeTimeValues);
		UOptionFloat* GearboxTransmissionEfficiency = UOptionFloat::CreateOption(GearboxTransmissionEfficiencyValues);
		UOptionWheels* WheelsFrictionForceMultiplier = UOptionWheels::CreateOption(WheelsFrictionForceMultiplierValues);
		UOptionFloat* MaxWheelsSteeringAngle = UOptionFloat::CreateOption(MaxWheelsSteeringAngleValues);
		UOptionFloat* SuspensionMaxRaise = UOptionFloat::CreateOption(SuspensionMaxRaiseValues);
		UOptionFloat* SuspensionMaxDrop = UOptionFloat::CreateOption(SuspensionMaxDropValues);
		UOptionFloat* SuspensionDumpRatio = UOptionFloat::CreateOption(SuspensionDumpRatioValues);
		UOptionFloat* SuspensionSpringRatio = UOptionFloat::CreateOption(SuspensionSpringRatioValues);
		UOptionFloat* SuspensionPreload = UOptionFloat::CreateOption(SuspensionPreloadValues);
		UOptionFloat* SuspensionSmoothness = UOptionFloat::CreateOption(SuspensionSmoothnessValues);
		UOptionWheels* WheelsBrakeTorque = UOptionWheels::CreateOption(WheelsBrakeTorqueValues);
		UOptionWheels* WheelsHandBrakeTorque = UOptionWheels::CreateOption(WheelsHandBrakeTorqueValues);
		
		OptionMap.Add(FName(VehicleMasses->OptionName), VehicleMasses);
		OptionMap.Add(FName(HorsePower->OptionName), HorsePower);
		OptionMap.Add(FName(MaxRpm->OptionName), MaxRpm);
		OptionMap.Add(FName(MaxTorque->OptionName), MaxTorque);
		OptionMap.Add(FName(AngleRatio->OptionName), AngleRatio);
		OptionMap.Add(FName(FrontRearSplit->OptionName), FrontRearSplit);
		OptionMap.Add(FName(DragCoefficient->OptionName), DragCoefficient);
		OptionMap.Add(FName(DownForceCoefficient->OptionName), DownForceCoefficient);
		OptionMap.Add(FName(AutomaticGearboxUpShiftRpm->OptionName), AutomaticGearboxUpShiftRpm);
		OptionMap.Add(FName(AutomaticGearboxDownShiftRpm->OptionName), AutomaticGearboxDownShiftRpm);
		OptionMap.Add(FName(GearboxChangeTime->OptionName), GearboxChangeTime);
		OptionMap.Add(FName(GearboxTransmissionEfficiency->OptionName), GearboxTransmissionEfficiency);
		OptionMap.Add(FName(WheelsFrictionForceMultiplier->OptionName), WheelsFrictionForceMultiplier);
		OptionMap.Add(FName(MaxWheelsSteeringAngle->OptionName), MaxWheelsSteeringAngle);
		OptionMap.Add(FName(SuspensionMaxRaise->OptionName), SuspensionMaxRaise);
		OptionMap.Add(FName(SuspensionMaxDrop->OptionName), SuspensionMaxDrop);
		OptionMap.Add(FName(SuspensionDumpRatio->OptionName), SuspensionDumpRatio);
		OptionMap.Add(FName(SuspensionSpringRatio->OptionName), SuspensionSpringRatio);
		OptionMap.Add(FName(SuspensionPreload->OptionName), SuspensionPreload);
		OptionMap.Add(FName(SuspensionSmoothness->OptionName), SuspensionSmoothness);
		OptionMap.Add(FName(WheelsBrakeTorque->OptionName), WheelsBrakeTorque);
		OptionMap.Add(FName(WheelsHandBrakeTorque->OptionName), WheelsHandBrakeTorque);
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
		TUOption<BVehicleWheels> WheelsAffectedByBrakesValues = {Advance, Option_WheelsBoolButton, "Wheels Affected By Brakes",
				DefaultWheelsAffectedByBrakes,
				DefaultWheelsAffectedByBrakes,
				{ false, false, false, false },
				{ true, true, true, true },
				1, "",
				"Set which wheels are affected by the brakes",
				true };
		
		TUOption<BVehicleWheels> WheelsAffectedByHandBrakesValues = {Advance, Option_WheelsBoolButton, "Wheels Affected By Hand Brakes",
			DefaultWheelsAffectedByHandBrakes,
			DefaultWheelsAffectedByHandBrakes,
			{ false, false, false, false },
			{ true, true, true, true },
			1, "",
			"Set which wheels are affected by the hand brakes",
			true };
		TUOption<BVehicleWheels> WheelsAffectedByEngineValues = {Advance, Option_WheelsBoolButton, "Wheels Affected By Engine",
			DefaultWheelsAffectedByEngine,
			DefaultWheelsAffectedByEngine,
			{ false, false, false, false },
			{ true, true, true, true },
			1, "",
			"Set which wheels are affected by the engine",
			false };
		
		TUOption<BVehicleWheels> WheelsAffectedBySteeringValues = {Advance, Option_WheelsBoolButton, "Wheels Affected By Steering",
			DefaultWheelsAffectedBySteering,
			DefaultWheelsAffectedBySteering,
			{ false, false, false, false },
			{ true, true, true, true },
			1, "",
			"Set which wheels are affected by the steering",
			true };
		TUOption<BVehicleWheels> WheelsSuspensionEnabledValues = {Advance, Option_WheelsBoolButton, "Wheels Suspension Enabled",
			DefaultWheelsSuspensionEnabled,
			DefaultWheelsSuspensionEnabled,
			{ false, false, false, false },
			{ true, true, true, true },
			1, "",
			"Set which wheels have the suspension enabled",
			true };

		UOptionWheels* WheelsAffectedByBrakes = UOptionWheels::CreateOption(WheelsAffectedByBrakesValues);
		UOptionWheels* WheelsAffectedByHandBrakes = UOptionWheels::CreateOption(WheelsAffectedByHandBrakesValues);
		UOptionWheels* WheelsAffectedByEngine = UOptionWheels::CreateOption(WheelsAffectedByEngineValues);
		UOptionWheels* WheelsAffectedBySteering = UOptionWheels::CreateOption(WheelsAffectedBySteeringValues);
		UOptionWheels* WheelsSuspensionEnabled = UOptionWheels::CreateOption(WheelsSuspensionEnabledValues);
		
		OptionMap.Add(FName(WheelsAffectedByBrakes->OptionName), WheelsAffectedByBrakes);
		OptionMap.Add(FName(WheelsAffectedByHandBrakes->OptionName), WheelsAffectedByHandBrakes);
		OptionMap.Add(FName(WheelsAffectedByEngine->OptionName), WheelsAffectedByEngine);
		OptionMap.Add(FName(WheelsAffectedBySteering->OptionName), WheelsAffectedBySteering);
		OptionMap.Add(FName(WheelsSuspensionEnabled->OptionName), WheelsSuspensionEnabled);
		
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

	static TMap<FName, UOptionBase*> OptionMap;
public:
	UDefaultPlayerOptions();
	static UOptionBase* GetOption(const FName OptionName);

	UFUNCTION(BlueprintCallable, Category = "PlayerOptions")
	static UDefaultPlayerOptions* GetPlayerOptionsInstance();
	
	static UDefaultPlayerOptions* PlayerOptionsInstance;

	UFUNCTION(BlueprintCallable, Category = "PlayerOptions")
	void PrintOptionMap();
	
	UFUNCTION(BlueprintCallable, Category = "PlayerOptions")
	static TMap<FName, UOptionBase*> GetOptionMap();

	UFUNCTION(BlueprintCallable, Category = "PlayerOptions")
	static void GetOptionByName(const FName OptionName, UOptionBase* &Option, TEnumAsByte<EOptionButtonType> &OptionType);
	
	UFUNCTION(BlueprintCallable, Category = "PlayerOptions")
	static void LogOptionMap();

};
