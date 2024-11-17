/**
* Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
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

class FOptionBase
{
public:
	virtual ~FOptionBase() = default;
};

template <typename T>
USTRUCT(NotBlueprintType)
class TFOption : public FOptionBase
{
public:
	FString Name;
	T Value;
	T DefaultValue;
	T MinValue;
	T MaxValue;
	float Step = 0;
	FString Unit;
	FString Tooltip;
	bool IsAffectingOtherOptions = false;

	TFOption(const FString &Name, T Value, T DefaultValue, T MinValue, T MaxValue,const float Step,const FString &Unit,const FString &Tooltip,const bool IsAffectingOtherOptions)
		: Name(Name), Value(Value), DefaultValue(DefaultValue), MinValue(MinValue), MaxValue(MaxValue), Step(Step), Unit(Unit), Tooltip(Tooltip), IsAffectingOtherOptions(IsAffectingOtherOptions) {}
};

USTRUCT(NotBlueprintType)
struct FDefaultBasicUserOption
{
	GENERATED_BODY()

	FDefaultBasicUserOption() = default;

	explicit FDefaultBasicUserOption(TMap<FName, FOptionBase*> &OptionMap)
	{
		OptionMap.Add(TEXT("ManualGearbox"), &ManualGearbox);
		OptionMap.Add(TEXT("AutomaticGearbox"), &AutomaticGearbox);
		OptionMap.Add(TEXT("AutomaticReverse"), &AutomaticReverse);
		OptionMap.Add(TEXT("DriveMode"), &DriveMode);
		OptionMap.Add(TEXT("SuspensionEnabled"), &SuspensionEnabled);
		OptionMap.Add(TEXT("WheelFrictionEnabled"), &WheelFrictionEnabled);
		OptionMap.Add(TEXT("TractionControlEnabled"), &TractionControlEnabled);
		OptionMap.Add(TEXT("AbsEnabled"), &AbsEnabled);
	}
	
	static constexpr bool bDefaultManualGearbox = false;
	static constexpr bool bDefaultAutomaticGearbox = true;
	static constexpr bool bDefaultAutomaticReverse = false;
	static EDriveMode DefaultDriveMode;
	static constexpr bool bDefaultSuspensionEnabled = true;
	static constexpr bool bDefaultWheelFrictionEnabled = true;
	static constexpr bool bDefaultTractionControlEnabled = true;
	static constexpr bool bDefaultAbsEnabled = true;
	
	TFOption<bool> ManualGearbox = {"Manual Gearbox", bDefaultManualGearbox, bDefaultManualGearbox, false, true, 1, "", "Use manual gearbox", true};
	TFOption<bool> AutomaticGearbox = {"Automatic Gearbox", bDefaultAutomaticGearbox, bDefaultAutomaticGearbox, false, true, 1, "", "Use automatic gearbox", true};
	TFOption<bool> AutomaticReverse = {"Automatic Reverse", bDefaultAutomaticReverse, bDefaultAutomaticReverse, false, true, 1, "", "Use automatic reverse", true};
	TFOption<EDriveMode> DriveMode = {"Drive Mode", DefaultDriveMode, DefaultDriveMode, EDriveMode::AllWheelDrive, EDriveMode::RearWheelDrive, 1, "", "Select drive mode", true};
	TFOption<bool> SuspensionEnabled = {"Suspension Enabled", bDefaultSuspensionEnabled, bDefaultSuspensionEnabled, false, true, 1, "", "Enable suspension", true};
	TFOption<bool> WheelFrictionEnabled = {"Wheel Friction Enabled", bDefaultWheelFrictionEnabled, bDefaultWheelFrictionEnabled, false, true, 1, "", "Enable wheel friction", true};
	TFOption<bool> TractionControlEnabled = {"Traction Control Enabled", bDefaultTractionControlEnabled, bDefaultTractionControlEnabled, false, true, 1, "", "Enable traction control", true};
	TFOption<bool> AbsEnabled = {"ABS Enabled", bDefaultAbsEnabled, bDefaultAbsEnabled, false, true, 1, "", "Enable ABS", true};
	
};

USTRUCT(NotBlueprintType)
struct FDefaultPhysicsUserOption
{
	GENERATED_BODY()

	FDefaultPhysicsUserOption() = default;

	explicit FDefaultPhysicsUserOption(TMap<FName, FOptionBase*> &OptionMap)
	{
		OptionMap.Add(TEXT("VehicleMasses"), &VehicleMasses);
		OptionMap.Add(TEXT("HorsePower"), &HorsePower);
		OptionMap.Add(TEXT("MaxRpm"), &MaxRpm);
		OptionMap.Add(TEXT("MaxTorque"), &MaxTorque);
		OptionMap.Add(TEXT("AngleRatio"), &AngleRatio);
		OptionMap.Add(TEXT("FrontRearSplit"), &FrontRearSplit);
		OptionMap.Add(TEXT("DragCoefficient"), &DragCoefficient);
		OptionMap.Add(TEXT("DownForceCoefficient"), &DownForceCoefficient);
		OptionMap.Add(TEXT("AutomaticGearboxUpShiftRpm"), &AutomaticGearboxUpShiftRpm);
		OptionMap.Add(TEXT("AutomaticGearboxDownShiftRpm"), &AutomaticGearboxDownShiftRpm);
		OptionMap.Add(TEXT("GearboxChangeTime"), &GearboxChangeTime);
		OptionMap.Add(TEXT("GearboxTransmissionEfficiency"), &GearboxTransmissionEfficiency);
		OptionMap.Add(TEXT("WheelsFrictionForceMultiplier"), &WheelsFrictionForceMultiplier);
		OptionMap.Add(TEXT("MaxWheelsSteeringAngle"), &MaxWheelsSteeringAngle);
		OptionMap.Add(TEXT("SuspensionMaxRaise"), &SuspensionMaxRaise);
		OptionMap.Add(TEXT("SuspensionMaxDrop"), &SuspensionMaxDrop);
		OptionMap.Add(TEXT("SuspensionDumpRatio"), &SuspensionDumpRatio);
		OptionMap.Add(TEXT("SuspensionSpringRatio"), &SuspensionSpringRatio);
		OptionMap.Add(TEXT("SuspensionPreload"), &SuspensionPreload);
		OptionMap.Add(TEXT("SuspensionSmoothness"), &SuspensionSmoothness);
		OptionMap.Add(TEXT("WheelsBrakeTorque"), &WheelsBrakeTorque);
		OptionMap.Add(TEXT("WheelsHandBrakeTorque"), &WheelsHandBrakeTorque);
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
	
	TFOption<FVehicle> VehicleMasses = { "Vehicle Masses",
		{ DefaultChassisMass, DefaultWheelMass, DefaultWheelMass, DefaultWheelMass, DefaultWheelMass},
		{ DefaultChassisMass, DefaultWheelMass, DefaultWheelMass, DefaultWheelMass, DefaultWheelMass},
		{0, 0, 0, 0, 0},
		{10000, 10000, 10000, 10000, 10000},
		10, "kg",
		"Set the masses of the vehicle parts",
		false };
	TFOption<float> HorsePower = { "Horse Power", DefaultHorsePower, DefaultHorsePower, 0, 1000, 1, "kW", "Set the power of the engine", true };
	TFOption<float> MaxRpm = { "Max RPM", DefaultMaxRpm, DefaultMaxRpm, 0, 10000, 1, "RPM", "Set the maximum RPM of the engine", true };
	TFOption<float> MaxTorque = { "Max Torque", DefaultMaxTorque, DefaultMaxTorque, 0, 1000, 1, "Nm", "Set the maximum torque of the engine", true };
	// Ratio of the wheelbase to the track width
	TFOption<float> AngleRatio = { "Angle Ratio", DefaultAngleRatio, DefaultAngleRatio, 0, 1, 0.1, "", "Set the ratio of the wheelbase to the track width", false };
	// Ratio of front to rear torque distribution, <0.5 means more torque to the front wheels, >0.5 means more torque to the rear wheels
	TFOption<float> FrontRearSplit = { "Front Rear Split", DefaultFrontRearSplit, DefaultFrontRearSplit, 0, 1, 0.1, "", "Set the ratio of front to rear torque distribution", false };
	// Drag coefficient of the vehicle
	TFOption<float> DragCoefficient = { "Drag Coefficient", DefaultDragCoefficient, DefaultDragCoefficient, 0, 1, 0.1, "", "Set the drag coefficient of the vehicle", false };
	// Rolling resistance coefficient of the vehicle
	TFOption<float> DownForceCoefficient = { "Down Force Coefficient", DefaultDownForceCoefficient, DefaultDownForceCoefficient, 0, 1, 0.1, "", "Set the down force coefficient of the vehicle", false };
	TFOption<float> AutomaticGearboxUpShiftRpm = { "Automatic Gearbox Up Shift RPM", DefaultAutomaticGearboxUpShiftRpm, DefaultAutomaticGearboxUpShiftRpm, 0, 10000, 1, "RPM", "Set the RPM at which the automatic gearbox will upshift", false };
	TFOption<float> AutomaticGearboxDownShiftRpm = { "Automatic Gearbox Down Shift RPM", DefaultAutomaticGearboxDownShiftRpm, DefaultAutomaticGearboxDownShiftRpm, 0, 10000, 1, "RPM", "Set the RPM at which the automatic gearbox will downshift", false };
	TFOption<float> GearboxChangeTime = { "Gearbox Change Time", DefaultGearboxChangeTime, DefaultGearboxChangeTime, 0, 10, 0.1, "s", "Set the time it takes to change gears", false };
	TFOption<float> GearboxTransmissionEfficiency = { "Gearbox Transmission Efficiency", DefaultGearboxTransmissionEfficiency, DefaultGearboxTransmissionEfficiency, 0, 1, 0.1, "", "Set the efficiency of the gearbox transmission", false };
	TFOption<float> MaxWheelsSteeringAngle = { "Max Wheels Steering Angle", DefaultMaxWheelsSteeringAngle, DefaultMaxWheelsSteeringAngle, 0, 90, 1, "deg", "Set the maximum steering angle of the wheels", false };
	TFOption<FVehicleWheels> WheelsFrictionForceMultiplier = { "Wheels Friction Force Multiplier",
		{ DefaultWheelsFrictionForceMultiplier, DefaultWheelsFrictionForceMultiplier,DefaultWheelsFrictionForceMultiplier,DefaultWheelsFrictionForceMultiplier },
		{ DefaultWheelsFrictionForceMultiplier, DefaultWheelsFrictionForceMultiplier,DefaultWheelsFrictionForceMultiplier,DefaultWheelsFrictionForceMultiplier },
		{ 0, 0, 0, 0 },
		{ 10, 10, 10, 10 },
		0.1, "",
		"Set the friction force multiplier of the wheels",
		false };
	TFOption<float> SuspensionMaxRaise = { "Suspension Max Raise", DefaultSuspensionMaxRaise, DefaultSuspensionMaxRaise, 0, 100, 1, "cm", "Set the maximum raise of the suspension", false };
	TFOption<float> SuspensionMaxDrop = { "Suspension Max Drop", DefaultSuspensionMaxDrop, DefaultSuspensionMaxDrop, 0, 100, 1, "cm", "Set the maximum drop of the suspension", false };
	TFOption<float> SuspensionDumpRatio = { "Suspension Dump Ratio", DefaultSuspensionDumpRatio, DefaultSuspensionDumpRatio, 0, 1, 0.1, "", "Set the dump ratio of the suspension", false };
	TFOption<float> SuspensionSpringRatio = { "Suspension Spring Ratio", DefaultSuspensionSpringRatio, DefaultSuspensionSpringRatio, 0, 1000, 1, "", "Set the spring ratio of the suspension", false };
	TFOption<float> SuspensionPreload = { "Suspension Preload", DefaultSuspensionPreload, DefaultSuspensionPreload, 0, 100, 1, "cm", "Set the preload of the suspension", false };
	TFOption<float> SuspensionSmoothness = { "Suspension Smoothness", DefaultSuspensionSmoothness, DefaultSuspensionSmoothness, 0, 10, 0.1, "", "Set the smoothness of the suspension", false };
	TFOption<FVehicleWheels> WheelsBrakeTorque = { "Wheels Brake Torque",
		{ DefaultFrontWheelsBrakeTorque, DefaultRearWheelsBrakeTorque, DefaultFrontWheelsBrakeTorque, DefaultRearWheelsBrakeTorque },
		{ DefaultFrontWheelsBrakeTorque, DefaultRearWheelsBrakeTorque, DefaultFrontWheelsBrakeTorque, DefaultRearWheelsBrakeTorque },
		{ 0, 0, 0, 0 },
		{ 10000, 10000, 10000, 10000 },
		10, "Nm",
		"Set the brake torque of the wheels",
		false };
	TFOption<FVehicleWheels> WheelsHandBrakeTorque = { "Wheels Hand Brake Torque",
		{ DefaultFrontWheelsHandBrakeTorque, DefaultRearWheelsHandBrakeTorque, DefaultFrontWheelsHandBrakeTorque, DefaultRearWheelsHandBrakeTorque },
		{ DefaultFrontWheelsHandBrakeTorque, DefaultRearWheelsHandBrakeTorque, DefaultFrontWheelsHandBrakeTorque, DefaultRearWheelsHandBrakeTorque },
		{ 0, 0, 0, 0 },
		{ 10000, 10000, 10000, 10000 },
		10, "Nm",
		"Set the hand brake torque of the wheels",
		false };
};

USTRUCT(NotBlueprintType)
struct FDefaultAdvanceUserOption
{
	GENERATED_BODY()

	FDefaultAdvanceUserOption() = default;
	
	explicit FDefaultAdvanceUserOption(TMap<FName, FOptionBase*> &OptionMap)
	{
		OptionMap.Add(TEXT("WheelsAffectedByBrakes"), &WheelsAffectedByBrakes);
		OptionMap.Add(TEXT("WheelsAffectedByHandBrakes"), &WheelsAffectedByHandBrakes);
		OptionMap.Add(TEXT("WheelsAffectedByEngine"), &WheelsAffectedByEngine);
		OptionMap.Add(TEXT("WheelsAffectedBySteering"), &WheelsAffectedBySteering);
		OptionMap.Add(TEXT("WheelsSuspensionEnabled"), &WheelsSuspensionEnabled);
	}
	
	static constexpr BVehicleWheels DefaultWheelsAffectedByBrakes = { false, false, false, false };
	static constexpr BVehicleWheels DefaultWheelsAffectedByHandBrakes = { false, false, false, false };
	static constexpr BVehicleWheels DefaultWheelsAffectedByEngine = { true, true, true, true };
	static constexpr BVehicleWheels DefaultWheelsAffectedBySteering = { true, false, true, false };
	static constexpr BVehicleWheels DefaultWheelsSuspensionEnabled = { true, true, true, true };
	
	TFOption<BVehicleWheels> WheelsAffectedByBrakes = { "Wheels Affected By Brakes",
		DefaultWheelsAffectedByBrakes,
		DefaultWheelsAffectedByBrakes,
		{ false, false, false, false },
		{ true, true, true, true },
		1, "",
		"Set which wheels are affected by the brakes",
		true };

	TFOption<BVehicleWheels> WheelsAffectedByHandBrakes = { "Wheels Affected By Hand Brakes",
		DefaultWheelsAffectedByHandBrakes,
		DefaultWheelsAffectedByHandBrakes,
		{ false, false, false, false },
		{ true, true, true, true },
		1, "",
		"Set which wheels are affected by the hand brakes",
		true };
	TFOption<BVehicleWheels> WheelsAffectedByEngine = { "Wheels Affected By Engine",
		DefaultWheelsAffectedByEngine,
		DefaultWheelsAffectedByEngine,
		{ false, false, false, false },
		{ true, true, true, true },
		1, "",
		"Set which wheels are affected by the engine",
		false };
		
	TFOption<BVehicleWheels> WheelsAffectedBySteering = { "Wheels Affected By Steering",
		DefaultWheelsAffectedBySteering,
		DefaultWheelsAffectedBySteering,
		{ false, false, false, false },
		{ true, true, true, true },
		1, "",
		"Set which wheels are affected by the steering",
		true };
	TFOption<BVehicleWheels> WheelsSuspensionEnabled = { "Wheels Suspension Enabled",
		DefaultWheelsSuspensionEnabled,
		DefaultWheelsSuspensionEnabled,
		{ false, false, false, false },
		{ true, true, true, true },
		1, "",
		"Set which wheels have the suspension enabled",
		true };
};

UCLASS(BlueprintType, Blueprintable)
class SIMULATOR_API UDefaultPlayerOptions : public UObject
{
	GENERATED_BODY()
	
	TUniquePtr<FDefaultBasicUserOption> BasicUserOptionInstance;
	TUniquePtr<FDefaultPhysicsUserOption> PhysicsUserOptionInstance;
	TUniquePtr<FDefaultAdvanceUserOption> AdvanceUserOptionInstance;
	
	bool bUseDefaultBasicUserOption = true;
	bool bUseDefaultPhysicsUserOption = true;
	bool bUseDefaultAdvanceUserOption = true;

	const FString BasicPath = "DefaultPlayerOptions.json";

	TMap<FName, FOptionBase*> OptionMap;
	FOptionBase* GetOption(const FName OptionName);
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
	
};
