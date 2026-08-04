# Distributed Leader Election and Token Passing Network

A distributed networking application written in **C** that implements a complete communication protocol among multiple network nodes. The project demonstrates peer discovery, leader election, randomized token passing, and network performance measurement using TCP sockets.

## Features

* Automatic node discovery using a handshake protocol
* Distributed leader election
* Randomized token/message passing between active nodes
* Detection of available and unavailable nodes
* Network latency and transmission time measurement
* Bandwidth estimation
* Logging of protocol execution
* TCP socket-based communication
* Modular implementation using a custom networking library (`arpnet`)

---

## Protocol Overview

The protocol consists of three phases.

### 1. Handshake

Each node discovers the other active nodes in the network.

* The first node initializes the handshake.
* The handshake packet circulates through every available node.
* Each node marks itself as available.
* The IP table is synchronized across all participating nodes.

```
Node A
   │
   ▼
Node B
   │
   ▼
Node C
   │
   ▼
Node D
   │
   └──────────────► Node A
```

---

### 2. Leader Election

After the handshake, all nodes participate in a distributed voting process.

Each node:

* receives the voting message
* inserts its vote
* forwards the updated message

Once the voting packet returns, a leader is selected.

```
Voting Packet

A → B → C → D → A

Winner:
Node C
```

The elected leader becomes responsible for coordinating the next phase.

---

### 3. Token Passing

The leader creates a message (token) that must visit every active node exactly once.

Each participating node:

* records reception time
* records transmission time
* marks itself as visited
* randomly selects the next unvisited node
* forwards the token

```
Leader

      ▼

Node 3

      ▼

Node 1

      ▼

Node 5

      ▼

Leader
```

---

## Performance Measurement

During token circulation, every node records timestamps.

The leader computes:

* Total communication time
* Packet flight time
* Average latency
* Total bandwidth
* Effective bandwidth

The resulting statistics are packaged into a `stat_t` message and transmitted to the statistics server.

---

## Project Structure

```
.
├── main.c
├── arpnet.h
├── assignment3.log
└── README.md
```

---

## Technologies Used

* C
* POSIX Sockets
* TCP/IP Networking
* Linux System Calls
* Time Measurement (`struct timeval`)
* Distributed Algorithms

---

## Main Components

### Handshake

Responsible for:

* discovering active nodes
* validating protocol compatibility
* synchronizing the address table

---

### Voting

Responsible for:

* distributed leader election
* notifying the elected leader

---

### Token Passing

Responsible for:

* randomized network traversal
* collecting timing information
* measuring communication performance

---

## Communication Messages

The protocol exchanges four message types.

| Structure     | Description                        |
| ------------- | ---------------------------------- |
| `handshake_t` | Node discovery and synchronization |
| `votation_t`  | Leader election                    |
| `message_t`   | Token passed among nodes           |
| `stat_t`      | Performance statistics             |

---

## State Machine

```
          +------------+
          | Handshake  |
          +------------+
                 |
                 ▼
          +------------+
          |   Voting   |
          +------------+
                 |
                 ▼
          +------------+
          | Token Pass |
          +------------+
                 |
                 ▼
          Statistics
```

---

## Network Architecture

Each instance of the program acts as both:

* a TCP server
* a TCP client

This allows peer-to-peer communication without relying on a central coordinator during protocol execution.

```
           Node A
         /   |   \
        /    |    \
    Node B Node C Node D
```

---

## Building

Compile using GCC.

```bash
gcc main.c -o assignment3
```

If the project uses additional source files:

```bash
gcc *.c -o assignment3
```

Link against the custom `arpnet` library if required.

Example:

```bash
gcc *.c -larpnet -o assignment3
```

---

## Running

Launch one instance on each participating machine.

```bash
./assignment3
```

Each node should have:

* a valid IP address in the address table
* connectivity to the other nodes
* the `arpnet` library installed

---

## Logging

Execution information is written to

```
assignment3.log
```

The log includes:

* handshake status
* voting progress
* sent messages
* received messages
* protocol errors

---

## Learning Objectives

This project demonstrates practical implementation of several distributed systems concepts:

* Distributed leader election
* Peer discovery
* Token passing protocols
* Fault detection
* TCP socket programming
* Network performance evaluation
* Randomized communication algorithms

---

## Future Improvements

* Dynamic node joins and departures
* Improved fault tolerance
* Asynchronous communication
* Encryption (TLS)
* IPv6 support
* Multi-threaded message handling
* Consensus algorithms (e.g., Raft or Paxos)
* Real-time monitoring dashboard

---

## License

This project is intended for educational purposes as part of a distributed systems/networking assignment.
