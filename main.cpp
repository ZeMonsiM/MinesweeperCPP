#include "Game.h"
#include "TermColor.h"

int main() {
    setTerminalColor(COLOR_WHITE);
    while (true) {
        Game game;
        if (game.play()) {
            game.victory();
            return 0;
        }

        if (!game.defeat()) {
            return 0;
        }
    }
}
