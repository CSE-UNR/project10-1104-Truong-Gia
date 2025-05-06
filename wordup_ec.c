//Gia Truong
//wordup ec
//project 10

#include <stdio.h>
#include <stdbool.h>

#define WORD_LENGTH 5
#define MAX_GUESSES 6

void read_mystery_word(char word[]);
void get_guess(char guess[]);
bool is_valid_guess(char guess[]);
void to_lowercase(char word[]);
bool check_guess(char guess[], char word[]);
void print_guesses(char guesses[][WORD_LENGTH + 1], char word[], int num_guesses);

int main() {
    char word[WORD_LENGTH + 1];
    char guesses[MAX_GUESSES][WORD_LENGTH + 1];
    int guess_count = 0;
    bool won = false;

    read_mystery_word(word);
    to_lowercase(word);

    while (guess_count < MAX_GUESSES) {
        if (guess_count == MAX_GUESSES - 1) {
            printf("FINAL GUESS : ");
        } else {
            printf("GUESS %d! Enter your guess: ", guess_count + 1);
        }

        char guess[WORD_LENGTH + 2];
        get_guess(guess);

        while (!is_valid_guess(guess)) {
            printf("Your guess must be 5 letters long.\n");
            printf("Please try again: ");
            get_guess(guess);
        }

        to_lowercase(guess);
        for (int i = 0; i < WORD_LENGTH; i++) {
            guesses[guess_count][i] = guess[i];
        }
        guesses[guess_count][WORD_LENGTH] = '\0';

        if (check_guess(guess, word)) {
            printf("================================\n");
            printf("\t\t");
            for (int i = 0; i < WORD_LENGTH; i++) {
                if (guess[i] == word[i]) {
                    printf("%c", guess[i] - 32); // uppercase
                } else {
                    printf("%c", guess[i]);
                }
            }
            printf("\n\tYou won in %d guesses!\n\t\tAmazing!\n", guess_count + 1);
            won = true;
            break;
        } else {
            printf("================================\n");
            print_guesses(guesses, word, guess_count + 1);
        }

        guess_count++;
    }

    if (!won) {
        printf("You lost, better luck next time!\n");
    }

    return 0;
}

void read_mystery_word(char word[]) {
    FILE *file = fopen("words.txt", "r");
    if (file == NULL) {
        printf("Error opening words.txt\n");
        word[0] = '\0';
        return;
    }

    int i = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF && i < WORD_LENGTH) {
        if (ch >= 'A' && ch <= 'Z') ch = ch + 32; // convert to lowercase
        word[i++] = ch;
    }
    word[WORD_LENGTH] = '\0';
    fclose(file);
}

void get_guess(char guess[]) {
    int i = 0;
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF && i < WORD_LENGTH) {
        guess[i++] = ch;
    }
    guess[i] = '\0';

    while (ch != '\n' && ch != EOF) {
        ch = getchar();
    }
}

bool is_valid_guess(char guess[]) {
    int len = 0;
    while (guess[len] != '\0') len++;

    if (len != WORD_LENGTH)
        return false;

    for (int i = 0; i < WORD_LENGTH; i++) {
        if (!(guess[i] >= 'a' && guess[i] <= 'z') &&
            !(guess[i] >= 'A' && guess[i] <= 'Z'))
            return false;
    }
    return true;
}

void to_lowercase(char word[]) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] >= 'A' && word[i] <= 'Z') {
            word[i] += 32;
        }
    }
}

bool check_guess(char guess[], char word[]) {
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (guess[i] != word[i]) return false;
    }
    return true;
}

void print_guesses(char guesses[][WORD_LENGTH + 1], char word[], int num_guesses) {
    for (int g = 0; g < num_guesses; g++) {
        // print word with capital letters for correct spots
        for (int i = 0; i < WORD_LENGTH; i++) {
            if (guesses[g][i] == word[i]) {
                putchar(guesses[g][i] - 32);
            } else {
                putchar(guesses[g][i]);
            }
        }
        printf("\n");

        // print pointer line
        bool printed = false;
        for (int i = 0; i < WORD_LENGTH; i++) {
            if (guesses[g][i] != word[i]) {
                // check if this letter exists elsewhere and hasn't been matched
                bool found = false;
                for (int j = 0; j < WORD_LENGTH; j++) {
                    if (j != i && guesses[g][i] == word[j] && guesses[g][j] != word[j]) {
                        found = true;
                        break;
                    }
                }
                if (found) {
                    putchar('^');
                    printed = true;
                } else {
                    putchar(' ');
                }
            } else {
                putchar(' ');
            }
        }
        printf("\n");
    }
}
