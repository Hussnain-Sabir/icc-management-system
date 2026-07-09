# ICC Cricket Management System

A C++ console application simulating international cricket management — including boards, teams, players, match simulations, rankings, and statistics — built using core Object-Oriented Programming principles.

## Overview

This system models a simplified version of how an international cricket governing body might manage teams, run matches, and track rankings. It combines inheritance, polymorphism, templates, and file persistence into a multi-file, layered architecture.

## Features

- **Player & team management** — create teams, add players, and track cricket-specific stats (runs, wickets, matches played)
- **Match simulation** — simulate T20 (20 overs) and ODI (50 overs) matches with randomized outcomes
- **Tournaments** — schedule and run multiple matches as part of a tournament cycle
- **Ranking system** — automatically tracks match results and updates team standings (+2 points per win)
- **Global ICC entity** — bundles multiple national boards, tournaments, and a unified ranking dashboard
- **Coaches & umpires** — additional personnel modeled using the same base entity structure as players
- **Venue management** — stores location and structural details for match venues
- **Statistics engine** — computes top run-scorer, highest wicket-taker, and team win-ratios
- **CSV persistence** — teams and venues can be saved to and loaded from `.csv` files
- **Generic list utility** — a custom `List<T>` template class wrapping `std::vector` for clean, reusable data handling

## Architecture

The project is organized into a main driver file and three header-based phases, reflecting incremental development:

### `main.cpp` — Controller
Drives a console-based menu loop (`while(running)`), routing user choices (1–12) through a central `Menu` object that orchestrates all other components.

### `Phase1.h` — Core Entities & File I/O
- **`Person`** — abstract base class defining a virtual interface for all people in the system
- **`Player`** — concrete class extending `Person`, storing cricket-specific metrics (runs, wickets, matches)
- **`Team`** — aggregates a `vector` of `Player` objects; supports saving/loading squad data via CSV
- **`CricketBoard`** — manages multiple `Team` instances representing a country or region
- **`Menu`** — interface layer connecting console input to board operations, scheduling, and simulations

### `Phase2.h` — Match Engine & Ranking
- **`Match`** (abstract) — models a single fixture
- **`T20Match`** / **`ODIMatch`** — concrete match types overriding `playMatch()` to simulate randomized results
- **`Tournament`** — holds a group of `Match*` pointers and drives scheduling across a full cycle
- **`RankingSystem`** — processes match results sequentially, updating team points and standings

### `Phase3.h` — Extensions, Templates & Statistics
- **`ICC`** — top-level global entity bundling multiple boards, tournaments, and a unified ranking dashboard
- **`Coach`** / **`Umpire`** — additional personnel classes reusing the polymorphic `Person` base
- **`Venue`** — stores location and structural details, with CSV read/write support
- **`Statistics`** — static utility class for computing top scorers, top wicket-takers, and win-ratios
- **`List<T>`** — generic template class wrapping `std::vector` for clean add/remove/index operations on custom types

## Key OOP Concepts Demonstrated

- **Abstraction & Inheritance** — `Person` → `Player`, `Coach`, `Umpire`
- **Polymorphism** — `Match` → `T20Match`, `ODIMatch` via overridden `playMatch()`
- **Aggregation & Composition** — `Team` contains `Player`s, `CricketBoard` contains `Team`s, `ICC` contains multiple boards
- **Templates & Generics** — custom `List<T>` class for reusable, type-safe collections
- **File I/O** — persistent CSV storage for teams and venues

## How to Run

```bash
g++ -o icc_system main.cpp
./icc_system
```

## Usage

Once running, the console menu offers 12 options covering team management, player registration, match scheduling, tournament simulation, rankings, and statistics viewing. Follow the on-screen prompts to navigate.

## Tech Stack

- C++ (STL: `vector`, file streams for CSV I/O)
- Object-Oriented Programming (inheritance, polymorphism, templates)

## Author

Hussain Sabir
