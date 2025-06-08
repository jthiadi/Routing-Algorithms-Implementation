# Implementing Routing Algorithms 

A hands‐on C implementation and simulation of two fundamental network‐layer routing algorithms—Link‐State (Dijkstra’s) and Distance‐Vector (Bellman–Ford)

## 📋 Project Overview

- **Link‐State Routing (Task 1):**  
  - Completed the `dijkstra()` function in `di.c` to compute minimum‐cost paths from a given source node.  
  - Verified output against provided and hidden topologies.

- **Distance‐Vector Routing (Task 2):**  
  - Implemented `rtinitX()`, `rtupdateX()`, and `rtlinkhandlerX()` in `node0.c` through `node3.c`, emulating asynchronous Bellman–Ford exchanges.  
  - Handled dynamic link‐cost changes at runtime, updating neighbor tables and propagating new routes correctly.

- **Comparative Analysis (Task 3):**  
  - Benchmarked time complexities: O(N²) for Dijkstra vs. O(N·E) for Bellman–Ford.  
  - Discussed packet propagation scopes and algorithmic responses to topology changes.

## 🔧 Key Technologies

- **Language:** C  
- **Platform:** Ubuntu 20.04 (VM)  
- **Build:** GNU Make  
- **Testing:** Custom simulation harness (`bf.c`) and hidden test configurations  
