#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

class GameOfLife
{
public:
    // Outputs a n*n game of life, with living cells with proba p
    // then runs it.
    GameOfLife(int n, double p) : size(n)
    {
        size2 = n*n;
        for (auto i = 0; i < n*n; ++i)
            game.push_back(random() < p);
        run();
    }

private:
    // outputs a random number in [0, 1)
    double random()
    {
        return double(rand()) / (double(RAND_MAX) + 1.0);
    }

    // count of living neighbours of (i, j)
    auto livingNeighbours(int i, int j)
    {
        return game[i + (j + 1)%size]
             + game[i + (j - 1 + size)%size]
             + game[(i + size)%size2 + j]
             + game[(i - size + size2)%size2 + j]
             + game[(i + size)%size2 + (j + 1)%size]
             + game[(i + size)%size2 + (j - 1 + size)%size]
             + game[(i - size + size2)%size2 + (j + 1)%size]
             + game[(i - size + size2)%size2 + (j - 1 + size)%size];
    }

    void run()
    {
        std::vector<bool> temp(size2);
        while (true)
        {
            print();
            for (auto i = 0; i < size2; i+=size)
            {
                for (auto j = 0; j < size; ++j)
                {
                    auto state = game[i + j];
                    auto living = livingNeighbours(i, j);
                    if (!state)
                        temp[i + j] = living == 3;
                    else
                        temp[i + j] = living == 2 || living == 3;
                }
            }
            std::swap(game, temp);
            std::this_thread::sleep_for(std::chrono::milliseconds(750));
        }
    }

    void print()
    {
        for (auto i = 0; i < size2; i+=size)
        {
            for (auto j = 0; j < size; ++j)
                std::cout << (game[i + j] ? '0' : ' ');
            std::cout << '\n';
        }
        std::cout << std::endl;
        for (auto i = 0; i <= size; ++i) {
            std::cout << "\e[A";
        }
    }

    std::vector<bool> game;
    int size;
    int size2;
};

int main(int, char** argv)
{
    GameOfLife game(std::stoi(argv[1]), std::stod(argv[2]));
}