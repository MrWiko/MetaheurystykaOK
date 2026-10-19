Szanowny mgr. Witczak

## 🗂️ Project Structure

```
project-root/
│
├── include/
│   ├── graph.h          # Graph class (data structure)
│   ├── graph-algos.h    # Graph algorithms (static functions)
│   ├── message.h        # Message structure
│   └── menu.h           # getMessage / dispatchMessage declarations
│
├── src/
│   ├── main.cpp         # Entry point, main loop
│   ├── graph.cpp        # Graph implementation
│   ├── graph-algos.cpp  # Algorithms implementation
├   ├── message.cpp      # Creates tokens and reads input
│   └── menu.cpp         # Message handling logic
│
├── README.md
└── CMakeLists.txt / Makefile
```
================================================
---

## 🔄 Execution Flow

```
User (stdin / args)
        │
        ▼
+------------------+
|  getToken()      |
|  - parsing       |   -> enum type {stdin,args}; struct Token { std::string token, type origin};
|  - createsTokens |
|  - hasStructContainingTokenAndOrigin(stdin/args)|
+------------------+
        │
        ▼
+----------------------+
| MenuClass            |
| - interpretsToken    | -> responsible for conversion
| - checksForErrors    | -> stdOut/getAnotherToken
| - executes operation |
| - asksMessageForTokens|
+----------------------+
        │
        ▼
+----------------------+
| Graph / GraphAlgos   |
| - graph operations   |
+----------------------+
        │
        ▼
      Result (stdout)
```

=========================================

# 📌 Project Overview

This project implements a modular graph processing system using a message-driven architecture. The application logic is divided into:

- graph representation,
- a set of graph algorithms,
- a user command processing system.

The core control mechanism is a message queue (`std::deque`), which ensures sequential and deterministic execution of operations.

---

# 🧠 Core Concepts

## 🔹 1. Separation of Concerns

- `graph.h` — definition of the Graph class and basic operations  
- `graph-algos.h` — static functions implementing graph algorithms (e.g., BFS, DFS, Dijkstra)

This approach ensures:
- clear separation between data structures and algorithmic logic,
- easier maintenance and extensibility.

---

## 🔹 2. Message-Based Communication

The system operates using a message structure:

```cpp
struct Message {
    // operation type + input data
};

====================================================================================

Message Queue
    container used: std::deque<Message>
    operates as a FIFO queue

Workflow:
    getMessage():
        reads input from stdin or program arguments
        constructs a Message
        pushes it into the queue
dispatchMessage():
        takes the first message from the queue
        executes the corresponding operation
        removes the message from the queue


===============================================================

Main Application Loop
    while (isRunning) {
        getMessage();
        dispatchMessage();
    }

Provides:
    continuous input handling,
    controlled execution flow.