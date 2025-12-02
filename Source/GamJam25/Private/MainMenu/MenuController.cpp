#include "MainMenu/MenuController.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenu/ButtonWidget.h"
#include "MainMenu/MainMenu.h"
#include "MainMenu/MenuStyleDA.h"

#if WITH_EDITOR
#include "Editor/EditorEngine.h"
#include "Editor.h"
#endif//runs when the game is being played in the editor

void AMenuController::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuClass)
	{
		MainMenu = CreateWidget<UMainMenu>(this, MainMenuClass);
		if (MainMenu)
		{
			MainMenu->AddToViewport();
			MainMenu->OnPlayRequest.AddDynamic(this, &AMenuController::HandleOnPlayGame);
			MainMenu->OnQuitRequest.AddDynamic(this, &AMenuController::HandleOnQuitGame);
		}

		FInputModeUIOnly InputMode;

		InputMode.SetWidgetToFocus(MainMenu->PlayButton->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(InputMode);
		bShowMouseCursor = true;
	}
}

void AMenuController::HandleOnPlayGame()
{
	FSoftObjectPath MapRef = MenuFlow->Gameplaylevel.ToSoftObjectPath();
	if (!MapRef.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Map soft path is not valid"));
		return;
	}
	FString MapPath = MapRef.ToString();
	FName MapName = FName(*FPackageName::ObjectPathToPackageName(MapPath));
	UGameplayStatics::OpenLevel(this, MapName);
}

void AMenuController::HandleOnQuitGame()
{
#if WITH_EDITOR
	if (GEditor)
	{
		//ends the specific PIE session
		if (GEditor->IsPlayingSessionInEditor())
		{
			GEditor->RequestEndPlayMap();
			return;
		}

		UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
		return;
	}
#else
	UWorld* world = GetWorld();
	if (IsValid(world)
		UKismetSystemLibrary::QuitGame(world, nullptr, EQuitPreference::Quit, false);
#endif
}

void AMenuController::BeginDestroy()
{
	if (MainMenu)
	{
		MainMenu->OnQuitRequest.RemoveAll(this);
	}

	Super::BeginDestroy();
}
