/*
------------------------------------------------------------
Project Title: UCR Medical Matching System
Course: Discrete Structures
Case: Case 2 – UCR Medical Center Volunteers
Team Name: Team UCR Med
Member(s): Jeremy Barron-Ohiaeri

Description:
This program simulates the matching of 100 UCR medical graduates to Doctors Without Borders assignments across 10 countries.
Matches are determined based on language fluency and medical specialization. The program calculates and displays the
probability of successful matches using discrete structures concepts such as relations, matrices, and probability.
------------------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>



using namespace std;

struct Participant {
    int id;
    string name;
    string language;
    string specialization;
};

struct Country {
    int id;
    string name;
    string requiredLanguage;
    string neededSpecialization;
};

const int NUM_PARTICIPANTS = 100;
const int NUM_COUNTRIES   = 10;
const int DAYS_ON_ASSIGNMENT = 60;

//  Function Declarations
void initializeCountries(vector<Country>& countries);
void initializeParticipants(vector<Participant>& participants,
                            const vector<string>& languages,
                            const vector<string>& specializations);
void buildEligibility(const vector<Participant>& participants,
                      const vector<Country>& countries,
                      vector<vector<bool>>& eligible);

void displayParticipants(const vector<Participant>& participants);
void displayCountries(const vector<Country>& countries);
void displayAllMatches(const vector<Participant>& participants,
                       const vector<Country>& countries,
                       const vector<vector<bool>>& eligible);
void showProbabilityForParticipant(const vector<Participant>& participants,
                                   const vector<vector<bool>>& eligible);
void showOverallStatistics(const vector<vector<bool>>& eligible);

// main
int main() {
    // 5 Languages
    vector<string> languages = {
        "English",
        "Spanish",
        "French",
        "Arabic",
        "Portuguese"
    };

    // Specializations
    vector<string> specializations = {
        "Neurology",
        "Geriatrics",
        "Pediatrics",
        "Radiology",
        "Rheumatology"
    };

    vector<Participant> participants;
    vector<Country> countries;
    vector<vector<bool>> eligible;

    initializeCountries(countries);
    initializeParticipants(participants, languages, specializations);
    buildEligibility(participants, countries, eligible);

    int choice = -1;
    do {
        cout << "\n========== UCR Medical Matcher ==========\n";
        cout << "1. Show all participants\n";
        cout << "2. Show all countries\n";
        cout << "3. Show all valid matches\n";
        cout << "4. Show match probability for a participant\n";
        cout << "5. Show overall matching statistics\n";
        cout << "0. Exit\n";
        cout << "----------------------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayParticipants(participants);
                break;
            case 2:
                displayCountries(countries);
                break;
            case 3:
                displayAllMatches(participants, countries, eligible);
                break;
            case 4:
                showProbabilityForParticipant(participants, eligible);
                break;
            case 5:
                showOverallStatistics(eligible);
                break;
            case 0:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}

// Initialization Functions
void initializeCountries(vector<Country>& countries) {
    countries.clear();
    countries.reserve(NUM_COUNTRIES);

    // 10 example countries with language + needed specialization
    countries.push_back({0, "Kenya",       "English",    "Pediatrics"});
    countries.push_back({1, "Peru",        "Spanish",    "Geriatrics"});
    countries.push_back({2, "France",      "French",     "Neurology"});
    countries.push_back({3, "Morocco",     "Arabic",     "Radiology"});
    countries.push_back({4, "Mozambique",  "Portuguese", "Rheumatology"});
    countries.push_back({5, "Canada",      "English",    "Neurology"});
    countries.push_back({6, "Mexico",      "Spanish",    "Pediatrics"});
    countries.push_back({7, "Lebanon",     "Arabic",     "Geriatrics"});
    countries.push_back({8, "Brazil",      "Portuguese", "Radiology"});
    countries.push_back({9, "Belgium",     "French",     "Rheumatology"});
}

void initializeParticipants(vector<Participant>& participants,
                            const vector<string>& languages,
                            const vector<string>& specializations) {
    participants.clear();
    participants.reserve(NUM_PARTICIPANTS);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> langDist(0, (int)languages.size() - 1);
    uniform_int_distribution<> specDist(0, (int)specializations.size() - 1);

    for (int i = 0; i < NUM_PARTICIPANTS; ++i) {
        Participant p;
        p.id = i;
        p.name = "Participant_" + to_string(i + 1);
        p.language = languages[langDist(gen)];
        p.specialization = specializations[specDist(gen)];
        participants.push_back(p);
    }
}

void buildEligibility(const vector<Participant>& participants,
                      const vector<Country>& countries,
                      vector<vector<bool>>& eligible) {
    eligible.assign(NUM_PARTICIPANTS, vector<bool>(NUM_COUNTRIES, false));

    for (int i = 0; i < NUM_PARTICIPANTS; ++i) {
        for (int j = 0; j < NUM_COUNTRIES; ++j) {
            bool languageMatch =
                participants[i].language == countries[j].requiredLanguage;
            bool specMatch =
                participants[i].specialization == countries[j].neededSpecialization;

            if (languageMatch && specMatch) {
                eligible[i][j] = true;
            }
        }
    }
}

// Display / Menu Functions
void displayParticipants(const vector<Participant>& participants) {
    cout << "\n--- Participants (100 UCR Graduates) ---\n";
    for (const auto& p : participants) {
        cout << "ID: " << p.id
             << " | Name: " << p.name
             << " | Language: " << p.language
             << " | Specialization: " << p.specialization
             << '\n';
    }
}

void displayCountries(const vector<Country>& countries) {
    cout << "\n--- Countries and Requirements (Doctors Without Borders) ---\n";
    for (const auto& c : countries) {
        cout << "ID: " << c.id
             << " | Country: " << c.name
             << " | Required language: " << c.requiredLanguage
             << " | Needed specialization: " << c.neededSpecialization
             << '\n';
    }
}

void displayAllMatches(const vector<Participant>& participants,
                       const vector<Country>& countries,
                       const vector<vector<bool>>& eligible) {
    cout << "\n--- Eligible Matches (Language + Specialization) ---\n";
    cout << "Each assignment lasts " << DAYS_ON_ASSIGNMENT
         << " days with on-site physicians.\n\n";

    bool anyMatch = false;

    for (int i = 0; i < NUM_PARTICIPANTS; ++i) {
        for (int j = 0; j < NUM_COUNTRIES; ++j) {
            if (eligible[i][j]) {
                anyMatch = true;
                cout << participants[i].name
                     << " (" << participants[i].language << ", "
                     << participants[i].specialization << ")"
                     << "  -->  " << countries[j].name
                     << " [" << countries[j].requiredLanguage << ", "
                     << countries[j].neededSpecialization << "]\n";
            }
        }
    }

    if (!anyMatch) {
        cout << "No valid matches found.\n";
    }
}

void showProbabilityForParticipant(const vector<Participant>& participants,
                                   const vector<vector<bool>>& eligible) {
    int pid;
    cout << "\nEnter participant ID (0 - " << NUM_PARTICIPANTS - 1 << "): ";
    cin >> pid;

    if (pid < 0 || pid >= NUM_PARTICIPANTS) {
        cout << "Invalid participant ID.\n";
        return;
    }

    int matchCount = 0;
    for (int j = 0; j < NUM_COUNTRIES; ++j) {
        if (eligible[pid][j]) {
            matchCount++;
        }
    }

    double probability = static_cast<double>(matchCount) / NUM_COUNTRIES;

    cout << fixed << setprecision(2);
    cout << "\nParticipant: " << participants[pid].name << '\n';
    cout << "Language: " << participants[pid].language
         << " | Specialization: " << participants[pid].specialization << '\n';
    cout << "Matches " << matchCount << " out of " << NUM_COUNTRIES
         << " countries.\n";
    cout << "P(match) = Number of eligible countries / 10 = "
         << matchCount << " / " << NUM_COUNTRIES
         << " = " << probability << '\n';
}

void showOverallStatistics(const vector<vector<bool>>& eligible) {
    int totalMatches = 0;

    for (int i = 0; i < NUM_PARTICIPANTS; ++i) {
        for (int j = 0; j < NUM_COUNTRIES; ++j) {
            if (eligible[i][j]) {
                totalMatches++;
            }
        }
    }

    int totalPairs = NUM_PARTICIPANTS * NUM_COUNTRIES;
    double overallProbability =
        static_cast<double>(totalMatches) / totalPairs;

    cout << fixed << setprecision(4);
    cout << "\n--- Overall Matching Statistics ---\n";
    cout << "Total participant-country pairs: " << totalPairs << '\n';
    cout << "Total valid matches (language + specialization): "
         << totalMatches << '\n';
    cout << "Probability that a random participant-country pair is a match:\n";
    cout << "P(match) = " << totalMatches << " / " << totalPairs
         << " = " << overallProbability << '\n';
}

