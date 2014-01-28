#include "CGameEngine.h"

int main() {
    CGameEngine *Othello = new CGameEngine();

    if(!Othello->GameLoop()) {
        return EXIT_SUCCESS;
    }
}
