# Game Leaderboard System

## Project Overview
The **Game Leaderboard System** is a C++ application designed to efficiently manage and display player scores in a gaming environment. This project was developed based on specific requirements:
- **Linked List**: Used to store and manage player data.
- **Heap (Min-Heap Priority Queue)**: Used to track the top 10 highest scores efficiently.
- **Array**: Used for quick access and display of leaderboard data.

## Features
- **Profile Management**: Players can have unique profiles associated with their scores.
- **Score Submission**: New scores can be added while ensuring no duplicate player entries.
- **Score Updates**: Existing player scores can be modified, and the leaderboard will be updated accordingly.
- **Leaderboard Display**: Displays the top 10 players in real-time.
- **File Storage**: Scores can be saved and retrieved from a file for persistence.
- **Error Handling**: Manages invalid scores, duplicate entries, and maintains data integrity.

## Technologies Used
- **Programming Language**: C++
- **Libraries**:
  - `iostream` - Handles input/output operations.
  - `fstream` - Reads/writes leaderboard data from files.
  - `string` - Manages text-based player names.
  - `iomanip` - Formats leaderboard output neatly.

## Data Structures
### **Linked List**
- Stores full player data.
- Ensures efficient insertions and updates.
- Implements **insertion sort** for ordered storage.

### **Heap (Min-Heap Priority Queue)**
- Maintains the top 10 scores.
- Provides quick access to the lowest-ranked player in the top 10.
- Implements **heapify** to maintain order.

### **Array**
- Stores leaderboard data for quick display.
- Uses **bubble sort** for sorting small datasets efficiently.

## Installation and Setup
1. **Compile the program** using a C++ compiler (e.g., g++):
   ```sh
   g++ leaderboard.cpp -o leaderboard
   ```
2. **Run the program**:
   ```sh
   ./leaderboard
   ```
3. Alternatively, use an online compiler like **OnlineGDB**.

## Usage Instructions
### **Main Menu Options:**
1. **Add Player Score**:
   - Enter player name and score.
   - Automatically updates the leaderboard if needed.

2. **Update Player Score**:
   - Select an existing player and modify their score.
   - Adjusts the leaderboard accordingly.

3. **Display Top 10 Scores**:
   - Shows the highest 10 scores in order.

4. **Display All Scores**:
   - Lists all players and their respective scores.

5. **Open Leaderboard File**:
   - Saves leaderboard data to a text file.
   - Allows viewing in a text editor.

6. **Exit**:
   - Closes the program.

## Challenges and Solutions
### **Challenges:**
- Synchronizing **Linked List** and **Heap** to ensure real-time updates.
- Managing efficient **insertion sorting** of new scores.
- Handling updates where scores drop below the top 10.

### **Solutions:**
- Used a **Min-Heap** to quickly remove the lowest top-10 score when needed.
- Implemented **Insertion Sort** for ordered storage in the linked list.
- Updated the leaderboard dynamically to reflect the latest scores.

## Future Enhancements
- **Integrate with an actual game** to generate scores automatically.
- **Improve the user interface (UI)** for better visual representation.
- **Enhance file handling** for better persistence and database integration.

## Contributors
- **Mikhael Edman Gomez** - Programmer
- **Jiro Gonzales** - Documentation

## License
This project is developed for academic purposes and is not intended for commercial use.

## Link & References
- [Documentation](https://docs.google.com/document/d/1UBN_P3klfGtZclKHItBNM2Ct4FPYBcPORdNm2MvxexM/edit?usp=sharing)
- [Bubble Sort Algorithm](https://www.programiz.com/dsa/bubble-sort)
- [Insertion Sort Algorithm](https://www.geeksforgeeks.org/insertion-sort-algorithm/)
- [Linked List in C++](https://www.geeksforgeeks.org/program-to-implement-singly-linked-list-in-c-using-class/)
- [Min-Heap Explanation](https://www.youtube.com/watch?v=pAU21g-jBiE)

