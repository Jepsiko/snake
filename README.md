# RATTLESNAKE
This repo is a the Snake Game for unix (maybe Windows) in **C++** using the **SDL2** librairy and the **NCurses** librairy

# Play the game
Play in console mode : `./Snake -c` or `./Snake --console`

Play in graphic mode : `./Snake`

# Rules
**How to move :** use ZQSD keys to move

**Grow :** you grow when you eat food (red squares)

**Kill :**
- You can kill another snake by eating the end of his tail (another color than the rest of the tail)
- You can also kill by making a loop around the other snake and touching the end of your tail

**Die :** You die if you eat your own tail except the end or another tail

# Future changes
- Multiplayer mode

# Recent changes
- 12/04/17 Graphic mode
- 13/04/17 We can see the path taken by the snake
- 14/04/17 The snake has a random color
- 14/04/17 The end of the snake's tail can be passed through
- 15/04/17 We can zoom in and out in the GUI with the mouse wheel