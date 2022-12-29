# jSnake

![play](./docs/play2.png)

## Features

1. Up to 4 human players
2. Up to 10 computer players (using a really stupid depth-first search pathfinding strategy)
3. Wrapping between edges of screen
4. Level selection
5. Speed selection

## Dependencies

Install `ncurses`. On debian based distros like ubuntu for example:

```bash
apt-get install libncurses5-dev
```

Install build tools. On debian based distros like ubuntu for example:

```bash
sudo apt install g++ make
```

## Play

The game expects an approximately 16x9 aspect ratio for the terminal. Make sure to resize the window as appropriate.

```bash
make
./jsnake.app
```

Navigate the menus using the `up` and `down` arrows. Press `enter` to select an option and `backspace` to move to the previous menu.

![menu](./docs/menu.png)

Playing with 3 or 4 players is quite a bit easier with a second keyboard because there is more room for everyones hands.

- P1 has `[UP][LEFT][RIGHT][DOWN]`
- P2 has `wasd`
- P3 has `ijkl`
- P4 has `tfgh`
