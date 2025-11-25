// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/MainMenu.h"

#include "MainMenu/ButtonWidget.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (PlayButton)
	{
		if (MenuStyle&&!PlayButton->MenuStyleData)
			PlayButton->MenuStyleData = MenuStyle;
		
		PlayButton->Label=NSLOCTEXT("Menu", "PlayButton", "Play");//sets the name of the text in the label
		PlayButton->OnButtonClicked.AddDynamic(this, &UMainMenu::HandlePlay);
	}

	if (QuitButton)
	{
		if (MenuStyle&&!QuitButton->MenuStyleData)
			QuitButton->MenuStyleData = MenuStyle;
		
		QuitButton->Label=NSLOCTEXT("Menu", "QuitButton", "Quit");
		QuitButton->OnButtonClicked.AddDynamic(this, &UMainMenu::HandleQuit);
	}
}

void UMainMenu::NativeDestruct()
{
	if (PlayButton)
		PlayButton->OnButtonClicked.RemoveAll(this);
	
	if (QuitButton)
		QuitButton->OnButtonClicked.RemoveAll(this);
	
	Super::NativeDestruct();
}
