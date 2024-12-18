# A Word-Woven Dungeon

## 🎲 Game Overview
*A Word-Woven Dungeon* is a fully text-based puzzle dungeon game played on the terminal. The player must make choices to rescue **Dilemma**, who is trapped in a dungeon. The goal of the game is to find the **three keys** (circle, square, and triangle) and reach the exit room with these keys. Defeating monsters may yield items or the necessary keys. Carefully read the provided text to visualize your surroundings and make the correct decisions.

## 🗝️ Rules and Gameplay

### General Gameplay
- The player progresses through the game by **entering numbers** corresponding to options displayed in menus.
- Goal: **Escape the dungeon with the highest score by making the fewest moves.**
- Scoring system:
   - The player starts with **1000 points**.
   - Each move reduces the score by **1 point**.
   - Menu interactions do not affect the score.
   - If the move count exceeds 1000, the score can go into **negative values**.

### Interactions System
- The main interaction screen is labeled **"Interactions"**.
- After each selection in Interactions, the terminal is **cleared**, and new text is displayed. You **cannot go back** to previous text, so pay close attention.
- **Main Commands**:
   - **Look Around**: Examine your surroundings.
   - **Move**: Move between rooms.
   - **Attack**: Attack monsters if they are present.
   - **Pick up the item**: Pick up an item from the ground.
   - **Open Inventory**: Manage items in your inventory.
     - **Note**: Items in your inventory do not affect stats. You must **equip them** to gain benefits.
     - Inventory space is limited; you must drop items to make room for new ones.
   - **Menu**: Access menu operations. From here, you can **save** or **load** your progress. You can also exit the game by selecting **Exit Game**.

### Player Stats
- The player has the following stats: **Health**, **Attack**, and **Shield**.
- You can carry a maximum of **two items** at a time.

### Exiting the Game
- To exit the game, go to the menu and select **Exit Game**.
- The game will ask for confirmation. Selecting **Yes** will close the game.
- **Warning**: If you exit without saving, your progress will be **lost**, and you will return to your last saved state.

## 💿 Setup Instructions

To run the game, ensure you have a **C compiler** (e.g., GCC) installed.

### Makefile Usage
The project includes a **Makefile** with the following commands:

```bash
# Clean previously compiled files
make clean

# Compile the game
make

# Compile and run the game
make run
```

### Project Directory Structure
```
A-Word-Woven-Dungeon/
│
├── headers/         # Header files (.h)
├── src/             # C source files (.c)
├── gamedata/        # Game data files (.txt)
│   ├── creature.txt          # Creature information
│   ├── item.txt              # Item definitions
│   ├── room_descriptions.txt # Room descriptions
│   ├── rooms.txt             # Dungeon connection details
│   └── save_files/           # Save game files
│
├── obj/                     # Object files
├── A-Word-Woven-Dungeon.exe # Executable game file
├── Makefile                 # Compilation and run instructions
└── README.md                # Project description
```

## 🗃️ Game Logic
The dungeon consists of interconnected rooms. Each room:
- Can have up to **5 connections**: **East, West, North, South**, and a **hidden passage**.
- Only some of these connections are available in each room; no room has all options.

The player must make correct decisions, solve puzzles, and defeat monsters to progress. Keys (circle, square, triangle) must be collected to unlock the exit room and complete the game.

## 📜 License
This project is licensed under the **MIT License**, allowing anyone to access and use the source code.

## 🛠️ Developer Notes
This game was developed as a **project assignment**. However, it provides a solid foundation for expansion. By making small modifications, anyone can create their own **puzzle dungeon game**. The project is flexible and open for further development.
