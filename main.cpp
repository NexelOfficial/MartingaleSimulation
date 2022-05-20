#include <iostream>
#include <time.h>
#include <random>

const double bet = 1; // The starting bet in dollars
const double playerBalance = 1024; // Balance each player starts with
const double winningMultiplier = 2; // The multiplier for winning a round e.g. say the multiplier is 2 then bet 1 -> win 2
const int roundWinningOdds = 50; // Chance in % to win a round
const int amtRounds = 100; // The amount of rounds each player plays
const int players = 4; // The amount of players

double profit = 0;
double highestInput = 0;

const bool isWin()
{
    // generate new seeds
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> r(1, (100 / roundWinningOdds * 100));

    return r(rng) % (100 / roundWinningOdds) == 0;
}

const double runRoundTillWin(const double bet, double balance)
{
    int rounds = 0;
    double currentInput = bet / 2;
    double total = 0;
    bool win = false;

    while (!win)
    {
        if (currentInput * 2 > balance) // Can't afford another round
            return total;

        rounds++;
        currentInput *= 2;
        total += currentInput;
        balance -= currentInput;
        win = isWin();
    }

    if (currentInput > highestInput)
        highestInput = currentInput;

    return currentInput;
}

const void calculate()
{
    int playerWins = 0;
    int amtBankrupt = 0;

    for (int j = 0; j < players; j++)
    {
        double balance = playerBalance;

        for (int i = 0; i < amtRounds; i++)
        {
            const double spent = runRoundTillWin(bet, balance);

            if (spent * 2 > balance)
            {
                amtBankrupt++;
                profit -= (spent);
                break;
            }
            else
            {
                balance += (bet * winningMultiplier / 2);
                profit += (bet * winningMultiplier / 2);
            }

            if (i == amtRounds - 1) // Every round is won
                playerWins++;
        }
    }

    std::cout << "\nPlayers that went bankrupt: " << std::to_string(amtBankrupt) << "/" << std::to_string(players) << "\n";
    std::cout << "Ending profit: " << std::to_string(profit) << "\nAmount of players that won every round: " << std::to_string(playerWins) << "/" << std::to_string(players) << "\n";
}

int main()
{
    calculate();
    return 1;
}