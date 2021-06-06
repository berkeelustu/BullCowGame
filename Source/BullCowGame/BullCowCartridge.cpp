
#include "BullCowCartridge.h"
#include "HiddenWordList.h"


void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();
	Isograms = GetValidWords(Words);
    SetupGame();
	// PrintLine(TEXT("Valid words are %i."), GetValidWords(Words).Num());
	
}

void UBullCowCartridge::OnInput(const FString& PlayerInput)
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(PlayerInput);
    }
}

 void UBullCowCartridge::SetupGame()
    {
        PrintLine(TEXT("Hi!"));
		HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num()-1)];
        Lives = HiddenWord.Len();
        bGameOver = false;
        PrintLine(TEXT("Your lives are: %i."), Lives);
        PrintLine(TEXT("Hidden Word is:%s."), *HiddenWord);
        PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
        PrintLine(TEXT("Type your guess and press enter!"));
    }

void UBullCowCartridge::EndGame() 
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again!"));
}


void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You won!"));
        EndGame();
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The Hidden Word is %i characters long"), HiddenWord.Len());
        PrintLine(TEXT("Your lives are %i now"), Lives);
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters! Try again!"));
        return;
    }

    PrintLine(TEXT("You lost a live!"));
    --Lives;

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You lost the game!"));
        PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord);
        EndGame();
        return;
    }
	
	FBullCowCount Score = GetBullCows(Guess);
    PrintLine(TEXT("You have %i Bulls and %i Cows."), Score.Bulls,Score.Cows);
    PrintLine(TEXT("Guess again, you have %i lives left!"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int32 i = 0; i < Word.Len(); i++)
    {
        for (int32 compare = i + 1; compare < Word.Len(); compare++)
        {
            if (Word[i] == Word[compare])
            {
                return false;
            }
        }
    }
        return true;
    }

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& Words) const
{
	TArray<FString>ValidWords;
	for (int32 i = 0; i < Words.Num(); i++)
	{
		if (Words[i].Len() >= 4 && Words[i].Len() <= 8 && IsIsogram(Words[i]))
		{
			ValidWords.Emplace(Words[i]);
		}
	}
	return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
	FBullCowCount Count;

	for (int32 i = 0; i < Guess.Len(); i++)
	{
		if(Guess[i]==HiddenWord[i])
		{
			Count.Bulls++;
		}
		else 
		{
			Count.Cows++;
		}
	}
	return Count;
}
