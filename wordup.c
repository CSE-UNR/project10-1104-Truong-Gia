//Gia Truong
//Project 10
//5.5.2025

#include <stdio.h>
#include <stdbool.h>

void read_word(char word[]);
bool valid_guess(char guess[]);
void to_lowercase(char word[]);
bool correct_guess(char guess[], char word[]);
void capitalized(char guess[], char word[]);
void pointer(char guess[], char word[]);

int main() {
    char word[6];
    read_word(word);

    int guess_count = 0;
    char guesses[6][6];
    bool won = false;

    while (guess_count < 6) {
        char guess[100];
        if (guess_count == 5)
            printf("FINAL GUESS : ");
        else
            printf("GUESS %d! Enter your guess: ", guess_count + 1);

        scanf("%s", guess);

        to_lowercase(guess);

        if (!valid_guess(guess)) {
            printf("Your guess must be 5 letters long.\n");
            printf("Please try again: ");
            continue;
        }

        if (correct_guess(guess, word)) {
            to_lowercase(guess);
            capitalized(guess, word);
            printf("================================\n");
            printf("\t\t%s\n", guess);
            printf("\tYou won in %d guesses!\n", guess_count + 1);
            printf("\t\tAmazing!\n");
            won = true;
            break;
        }

        for (int i = 0; i < 5; i++) {
            guesses[guess_count][i] = guess[i];
        }
        guesses[guess_count][5] = '\0';

        printf("================================\n");
        for (int i = 0; i <= guess_count; i++) {
            char temp[6];
            for (int j = 0; j < 6; j++)
                temp[j] = guesses[i][j];
            capitalized(temp, word);
            printf("%s\n", temp);
            pointer(guesses[i], word);
        }

        guess_count++;
    }

    if (!won) {
        printf("You lost, better luck next time!\n");
    }

    return 0;
}

void read_word(char word[]) {
    FILE *f = fopen("mystery.txt", "r");
    if (f == NULL) {
        printf("Error: cannot open mystery.txt\n");
        return;
    }
    fscanf(f, "%5s", word);
    fclose(f);
}

bool valid_guess(char guess[]) {
    int len = 0;
    while (guess[len] != '\0') {
        if (guess[len] < 'a' || guess[len] > 'z') return false;
        len++;
    }
    return len == 5;
}

void to_lowercase(char word[]) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] >= 'A' && word[i] <= 'Z') {
            word[i] = word[i] - 'A' + 'a';
        }
    }
}

bool correct_guess(char guess[], char word[]) {
    for (int i = 0; i < 5; i++) {
        if (guess[i] != word[i]) return false;
    }
    return true;
}

void capitalized(char guess[], char word[]) {
    for (int i = 0; i < 5; i++) {
        if (guess[i] == word[i] && guess[i] >= 'a' && guess[i] <= 'z') {
            guess[i] = guess[i] - 'a' + 'A';
        }
    }
}

void pointer(char guess[], char word[]) {
    bool used[5] = {false};
    char line[6] = {' ', ' ', ' ', ' ', ' ', '\0'};

    for (int i = 0; i < 5; i++) {
        if (guess[i] == word[i]) {
            used[i] = true;
        }
    }

    for (int i = 0; i < 5; i++) {
        if (guess[i] == word[i]) continue;
        for (int j = 0; j < 5; j++) {
            if (!used[j] && guess[i] == word[j]) {
                line[i] = '^';
                used[j] = true;
                break;
            }
        }
    }

    printf("%s\n", line);
}
