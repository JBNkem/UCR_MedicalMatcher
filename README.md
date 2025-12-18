# UCR MedicalMatcher

## Description
This program simulates the matching of 100 UCR medical graduates to Doctors Without Borders assignments across 10 countries.
Matches are determined based on language fluency and medical specialization. The program calculates and displays the
probability of successful matches using discrete structures concepts such as relations, matrices, and probability.

## Programming Approach
- Used C++ structs to model Participants and Countries.
- Used a nested-loop matching algorithm to compare:
  - participant.language == country.requiredLanguage
  - participant.specialization == country.neededSpecialization
- Stored match results in a boolean eligibility matrix (relation).
- Computed probability:
  - P(match) = (number of eligible countries) / 10
- Used a menu-driven interface for user interaction.

## Author(s)
- Jeremy Barron-Ohiaeri

## Date Published
- 2025-12-18

## How to Use
1. Compile the program using a C++ compiler (C++17 or later).
2. Run the executable.
3. Use the menu options displayed to view matches and probabilities.

### Program Menu
- Option 1: Show all participants  
- Option 2: Show all countries  
- Option 3: Show all valid matches  
- Option 4: Show match probability for a participant  
- Option 5: Show overall matching statistics  
- Option 0: Exit
