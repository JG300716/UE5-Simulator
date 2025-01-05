// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionBoolButton.h"

FSlateBrushOutlineSettings UOptionBoolButton::BasicOutlineSettings = FSlateBrushOutlineSettings(FVector4(8,8,8,8), FLinearColor::White, 2);
UTexture2D* UOptionBoolButton::OffTexture = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/Simulator/GUI/Textures/CheckBoxOff.CheckBoxOff'"));
UTexture2D* UOptionBoolButton::OnTexture = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/Simulator/GUI/Textures/CheckBoxOn.CheckBoxOn'"));

void UOptionBoolButton::InitOptionBoolButton(const TArray<UButton*> &Buttons, const EMenuButtonType MenuType, const EOptionButtonType OptionsType, const FString &Name, const FString ParentName, const bool &Value)
{
	InitOptionBaseButton(Buttons, MenuType, OptionsType, Name, ParentName);
	this->BValue = Value;
}

void UOptionBoolButton::UpdateGraphics()
{
	if (MenuButton.IsEmpty()) return;
	
	UTexture2D *Texture = BValue ? OnTexture : OffTexture;
	UE_LOG(LogTemp, Warning, TEXT("BValue: %d"), BValue);
	if (!IsValid(Texture)) return;
	for(auto &Button : MenuButton)
	{
		if (!IsValid(Button)) continue;
		FButtonStyle Style = Button->GetStyle();
		FSlateBrush Brush = Style.Normal;
		Brush.SetResourceObject(Texture);
		Brush.ImageSize = FVector2D(Texture->GetSizeX(), Texture->GetSizeY());
		Brush.OutlineSettings = BasicOutlineSettings;
		Brush.OutlineSettings.Color = FLinearColor::White;
		Style.Normal = Brush;
		Button->SetStyle(Style);
	}
}