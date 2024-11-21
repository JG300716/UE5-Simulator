// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeButtonOutline.h"

void UChangeButtonOutline::ChangeButtonOutline(UButton* Button, bool bIsOutline)
{
	if (Button == nullptr) return;
	FButtonStyle Style = Button->GetStyle();
	Style.Normal.OutlineSettings.Color = bIsOutline ? FLinearColor::Yellow : FLinearColor::Black;
	Button->SetStyle(Style);
}
