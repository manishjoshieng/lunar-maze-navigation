# Lunar Maze Navigation with Maximum Safety

## Problem Statement

In the context of lunar exploration, our robot embarks on a mission to navigate a maze-like terrain filled with craters. The primary objective is to find the shortest path from the source to the destination while maximizing the minimum distance between the robot's path and the craters encountered along the way. The overarching goal is to ensure the robot maintains a safe distance from craters throughout its entire trajectory.

### Solution Overview

The provided C++ solution employs a priority queue-based approach to find the optimal path. The distance between the robot's path and the craters is defined as the minimum distance from any cell on the selected path to the nearest crater. The Manhattan distance metric is used to calculate distances between locations.

### Key Components

1. **Location Struct:**
   - Represents a 2D location in the maze.
   - Overloaded equality operator for location comparison.
   - Calculates the distance between two locations.

2. **QueueNode Struct:**
   - Represents a node in the priority queue.
   - Stores location, parent node, current distance, distance from the cat, and distance from the target.
   - Custom comparison operator for prioritizing nodes in the queue.

3. **Path Construction and Hashing:**
   - Utilizes a custom hash function for locations.
   - Constructs the path from the destination back to the source.

4. **Priority Queue and BFS:**
   - Implements a priority queue with a custom comparator.
   - Utilizes Breadth-First Search (BFS) to explore possible paths.

### How to Run

- The `main` function demonstrates how to use the solution to find the shortest path in a 6x6 maze.
- Customize `max_row`, `max_col`, `start`, `end`, and `cat` for different scenarios.


---

Feel free to replace `"path_to_image.png"` with the actual path to an image representing your lunar maze. Customize this README based on your specific implementation details and any additional information you'd like to provide.
