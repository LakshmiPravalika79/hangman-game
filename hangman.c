#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h> // For time()

#define MAX_WORD_LENGTH 50
#define MAX_TRIES 6

// Function to choose a random word for the game
char* chooseRandomWord() {
    const char *wordList[] = {"hangman", "programming", "challenge", "cryptography", "algorithm", "computer"};
    int wordCount = sizeof(wordList) / sizeof(wordList[0]);

    // Choose a random index
    int randomIndex = rand() % wordCount;

    // Allocate memory for the selected word
    char *selectedWord = (char *)malloc(MAX_WORD_LENGTH * sizeof(char));
    if (selectedWord == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Copy the word to the allocated memory
    strcpy(selectedWord, wordList[randomIndex]);
    return selectedWord;
}

// Function to display the current state of the word with guessed letters
void displayWord(char *word, char *guessedLetters) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (strchr(guessedLetters, word[i]) != NULL || !isalpha(word[i])) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

// Function to check if the player has guessed the entire word
int hasGuessedWord(char *word, char *guessedLetters) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (strchr(guessedLetters, word[i]) == NULL && isalpha(word[i])) {
            return 0; // Not all letters guessed
        }
    }
    return 1; // All letters guessed
}

// Function to play the Hangman game
void playHangman() {
    char *word = chooseRandomWord();
    char guessedLetters[MAX_WORD_LENGTH] = "";
    int incorrectAttempts = 0;

    printf("Welcome to Hangman!\n");

    do {
        printf("\nCurrent word: ");
        displayWord(word, guessedLetters);

        // Display guessed letters
        printf("Guessed letters: %s\n", guessedLetters);

        // Get user input
        char guess;
        printf("Enter a letter: ");
        scanf(" %c", &guess);

        // Convert to lowercase for consistency
        guess = tolower(guess);

        // Check if the letter has already been guessed
        if (strchr(guessedLetters, guess) != NULL) {
            printf("You already guessed that letter. Try again.\n");
            continue;
        }

        // Add the guessed letter to the list
        strncat(guessedLetters, &guess, 1);

        // Check if the guessed letter is in the word
        if (strchr(word, guess) == NULL) {
            printf("Incorrect guess!\n");
            incorrectAttempts++;
        }

        // Check if the player has guessed the entire word
        if (hasGuessedWord(word, guessedLetters)) {
            printf("\nCongratulations! You guessed the word: %s\n", word);
            break;
        }

        // Check if the player has run out of attempts
        if (incorrectAttempts == MAX_TRIES) {
            printf("\nSorry, you've run out of attempts. The word was: %s\n", word);
            break;
        }
    } while (1);

    free(word); // Free allocated memory
}

int main() {
    // Seed the random number generator
    srand((unsigned int)time(NULL));

    // Play the Hangman game
    playHangman();

    return 0;
}
