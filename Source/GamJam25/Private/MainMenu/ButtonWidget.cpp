#include "MainMenu/ButtonWidget.h"

#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "MainMenu/MenuStyleDA.h"

void UButtonWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (ButtonText)
	{
		ButtonText->SetText(Label);
		if (MenuStyleData)
		{
			ButtonText->SetFont(MenuStyleData->ButtonFont);
			ButtonText->SetColorAndOpacity(MenuStyleData->TextColour);
		}
	}
	if (WB_Button && MenuStyleData)
	{
		FButtonStyle Style = WB_Button->GetStyle();
		Style.Normal.TintColor = FSlateColor(MenuStyleData->ButtonColour);
		Style.Hovered.TintColor = FSlateColor(MenuStyleData->ButtonHoverColour);
		Style.Pressed.TintColor = FSlateColor(MenuStyleData->ButtonHoverColour);
		WB_Button->SetStyle(Style);
	}

	if (WB_SizeBox)
	{
		WB_SizeBox->SetWidthOverride((MenuStyleData->ButtonSize.X));
		WB_SizeBox->SetHeightOverride((MenuStyleData->ButtonSize.Y));
	}
}

void UButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (WB_Button)
	{
		WB_Button->OnClicked.AddDynamic(this, &UButtonWidget::HandleClicked);
	}
}

void UButtonWidget::HandleClicked()
{
	OnButtonClicked.Broadcast();
}
