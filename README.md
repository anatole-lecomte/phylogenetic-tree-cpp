# Phylogenetic Tree Construction from a Distance Matrix

A C++ program that builds a binary phylogenetic tree from a species dissimilarity matrix, using a UPGMA-style agglomerative clustering approach.

*University project — INFO-H-304 "Compléments de Programmation et d'Algorithmique", ULB (2024–2025). Team of 3 students.*

## Overview

Given a distance (dissimilarity) matrix between N species, the program repeatedly merges the two most similar species under a common ancestor, recalculates distances to the new ancestor, and repeats until a single root (the common ancestor of all species) remains.

The project had to satisfy strict complexity constraints, since it is designed to scale to matrices of **up to several thousand species**.

## Data structure choice

Two data structures were considered and compared using a full complexity analysis before implementation:

- **Balanced binary search tree** — theoretically attractive for its O(log n) minimum search, but the implementation hit a dead end when updating cross-references between merged nodes.
- **Vector of vectors** (final choice) — simpler, lower memory footprint, and direct index-based access. Minimum search is not natively fast, but this was mitigated with targeted optimizations (see below).

This dead-end-and-pivot process, including the complexity trade-off table that motivated it, is documented in full in the [project report](report/Rapport_Projet_CPA.pdf).

## Optimizations

Three key optimizations were implemented to keep the program fast on large matrices:

1. Minimum-per-row is computed **during** matrix reading, avoiding a second full pass.
2. Row minima are **cached across iterations** and only recomputed when the cached minimum was actually deleted.
3. The new ancestor's minimum is computed **while** its distances are being calculated, avoiding an extra pass over its row.

Combined, these optimizations reduced runtime by a factor of ~4 on a 1050-species matrix.

**Overall complexity:** O(n³) for the full tree construction (matrix reading: O(n²); per-iteration minimum search: O(n); row/column deletion: O(n) / O(n²), repeated O(n) times).

## Build & run

```bash
make projetprelim   # preliminary version: performs a single merge step
make projet          # final version: builds the full tree

./projet matrice.txt              # prints the root ancestor's name to the terminal
./projet matrice.txt output.txt   # writes it to output.txt instead
```

**Input format:** a `.txt` file where each line starts with a species name followed by its dissimilarity values to all preceding species (lower-triangular matrix). See the [assignment statement](https://en.wikipedia.org/wiki/UPGMA) for the UPGMA method this project is based on.

## Project structure

```
.
├── Ligne.h / Ligne.cpp        # Represents a single species (row): values, running minimum
├── Matrice.h / Matrice.cpp    # Represents the full matrix and drives the merging algorithm
├── projet.cpp                 # Entry point — full algorithm
├── projetprelim.cpp           # Entry point — preliminary version (single merge step)
├── Makefile
└── report/
    └── Rapport_Projet_CPA.pdf # Full write-up: design choices, class structure, complexity analysis
```

## Authors

- Lecomte Anatole
- Moussiaux Hugo
- Samadov Komildzhon

Supervised by Prof. Jérémie Roland
