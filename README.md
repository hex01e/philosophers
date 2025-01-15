# Philosophers

## Overview

*Philosophers** is a project designed to teach the basics of threading and process management in C. Through this project, you will learn to implement and manage threads, mutexes, and semaphores while simulating the classic dining philosophers problem.

---

## Features

### Mandatory Part
- **Program Name**: `philo`
- **Key Concepts**:
  - Each philosopher is represented by a thread.
  - Forks are shared resources, protected by mutexes.
  - The simulation manages states like eating, thinking, and sleeping while avoiding data races.
- **Simulation Rules**:
  - Philosophers alternate between eating, sleeping, and thinking.
  - Forks are placed between philosophers; each philosopher requires two forks to eat.
  - The simulation ends if a philosopher dies of starvation or when all philosophers have eaten a defined number of times.

### Bonus Part
- **Program Name**: `philo_bonus`
- **Key Concepts**:
  - Each philosopher is represented by a separate process.
  - Forks are shared resources, tracked using semaphores.
  - The simulation ensures synchronization and avoids race conditions.
- **Enhanced Features**:
  - All forks are placed in the center of the table and managed using a semaphore.
  - The main process orchestrates the simulation, while child processes represent philosophers.

---

## Setup Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/hex01e/philosophers
   cd philosophers```
2. Run
   - Make and run the mandatory part
   ```bash
   cd philo
   make 
   ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat```
  - Make and run the bonus part
    ```bash
    cd philo_bonus
    make
    ./philo_bonus <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]```
  Replace the arguments with appropriate values:

  - number_of_philosophers: Total number of philosophers.
      - `time_to_die`: Time in milliseconds before a philosopher dies if they do not start eating.
      - `time_to_eat`: Time in milliseconds a philosopher spends eating.
      - `time_to_sleep`: Time in milliseconds a philosopher spends sleeping.
      - `number_of_times_each_philosopher_must_eat` (optional): Stops the simulation after all philosophers have eaten this many times.
  
