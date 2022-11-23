#include <array>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

template <int W, int H>
class Board {
public:
    Board() {
        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x) {
                data.at(y).at(x) = 0;
            }
        }
    }

    void randomize() {
        srand(time(0));
        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x) {
                data.at(y).at(x) = rand() % 2;
            }
        }
    }

    void display() const {
        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x) {
                if (data.at(y).at(x)) {
                    std::cout << '*';
                } else {
                    std::cout << ' ';
                }
            }
            std::cout << std::endl;
        }
    }

    bool isAlive(int x, int y) const {
        if (x < 0 || y < 0 || x >= W || y >= H) {
            return false;
        }
        return data.at(y).at(x);
    }

    void iterate(Board<W, H>& other) const {
        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x) {
                int neighbors = 0;
                for (int y2 = y - 1; y2 <= y + 1; ++y2) {
                    for (int x2 = x - 1; x2 <= x + 1; ++x2) {
                        if (x == x2 && y == y2) { 
                            continue;
                        }
                        if (isAlive(x2, y2)) {
                            ++neighbors;
                        }
                    }
                }
                other.data.at(y).at(x) = (neighbors == 3) || (isAlive(x, y) && neighbors == 2);
            }
        }
    }

    bool equals(Board<W, H> const& other) const {
        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x) {
                if (data.at(y).at(x) != other.data.at(y).at(x)) {
                    return false;
                }
            }
        }
        return true;
    }
private:
    std::array<std::array<bool, W>, H> data; 
};

int main() {
    auto front = Board<180, 40>();
    auto back = Board<180, 40>();
    front.randomize();
    int count = 0;
    while (count < 1'000) {
        std::cout << "\x1b[2J";
        front.display();
        front.iterate(back);
        front = back;
        //usleep(10'000);
        ++count;
    }
}
