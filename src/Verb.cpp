#include "header/Verb.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

vector<VerbForms> read_from_file(const string& file_path)
{
    vector<VerbForms> verbs;
    VerbForms forms;
    ifstream file(file_path);
    while (!file.eof()) {
        getline(file, forms.infinitive, ' ');
        getline(file, forms.simple, ' ');
        getline(file, forms.participle, '\n');
        verbs.emplace_back(forms);
    }
    file.close();
    return verbs;
}

vector<int> rand_verbs(int size)
{
    random_device rd;
    mt19937 g(rd());
    vector<int> verb_indexes;
    verb_indexes.reserve(size);
    for (int i = 0; i < size; ++i) {
        verb_indexes.emplace_back(i);
    }
    shuffle(verb_indexes.begin(), verb_indexes.end(), g);
    return verb_indexes;
}

int check_verbs(const vector<string>& user_verbs, const VerbForms& reference)
{
    if (user_verbs[0] == reference.simple) {
        if (user_verbs[1] == reference.participle) {
            return 2;
        }
        return 1;
    }
    if (user_verbs[1] == reference.participle) {
        return -1;
    }
    return 0;
}

int result(int number_of_verbs, int right_value)
{
    if (number_of_verbs <= 0) {
        return 0;
    }
    int result = int((float(right_value) / (float(number_of_verbs) * 2)) * 100);
    return result;
}

void accrual_of_points(int temp, int& right_value)
{
    if (temp == 2) {
        right_value += 2;
    }
    if (temp == 1) {
        right_value += 1;
    }
    if (temp == -1) {
        right_value += 1;
    }
}

void message_right(int result)
{
    cout << "\n-------------------------------------------------------\n";
    if (result == 2) {
        cout << "All required forms entered \x1b[32mcorrectly.\n"
             << "\x1b[0mMove on to the next.";
    }
}

void message_wrong(const VerbForms& verb, int result)
{
    if (result == 0) {
        cout << "You made the mistake in form Past Simple and Past Participle. "
                "Right version: \x1b[31m"
             << verb.simple << "\x1b[0m and \x1b[31m" << verb.participle
             << "\n\x1b[0mMove on to the next.";
    } else if (result == -1) {
        cout << "You made the mistake in form Past Simple. "
             << "Right version: \x1b[31m" << verb.simple
             << "\n\x1b[0mMove on to the next.";
    } else if (result == 1) {
        cout << "You made the mistake in form Past Participle. "
             << "Right version: \x1b[31m" << verb.participle
             << "\n\x1b[0mMove on to the next.";
    }
    cout << "\n-------------------------------------------------------\n";
}

void print_random_verb(const VerbForms& verb)
{
    if (verb.simple == "was") {
        cout << "\nWrite in the singular\n";
    } else if (verb.simple == "were") {
        cout << "\nWrite in the plural\n";
    }
    cout << "\nYour verb: " << verb.infinitive;
    cout << "\nInput other form\n";
}

void message_mark(int percent)
{
    int mark = 0;
    cout << "\n=======================================================\n";

    if (percent == 0) {
        mark = 1;
        cout << "| Percentage of correct answers: \x1b[31m " << percent
             << setw(25) << "\x1b[0m |\n";
        cout << "| Your mark: " << mark << setw(42) << "|\n";
        cout << "| You need to repeat the verbs before the next attempt"
             << "|";
    }

    if (percent < 50 && percent != 0) {
        mark = 2;
        cout << "| Percentage of correct answers: \x1b[31m " << percent
             << setw(24) << "\x1b[0m |\n";
        cout << "| Your mark: " << mark << setw(42) << "|\n";
        cout << "| Don't worry, next time you will able to. " << setw(12)
             << "|";
    }

    if (percent > 49 && percent < 69) {
        mark = 3;
        cout << "| Percentage of correct answers: \x1b[31m" << percent
             << setw(25) << "\x1b[0m|\n";
        cout << "| Your mark: " << mark << setw(42) << "|\n";
        cout << "| Not bad, but i'm sure you can do better." << setw(13) << "|";
    }

    if (percent > 70 && percent < 85) {
        mark = 4;
        cout << "| Percentage of correct answers: \x1b[33m" << percent
             << setw(25) << "\x1b[0m|\n";
        cout << "| Your mark: " << mark << setw(42) << "|\n";
        cout << "| Your knowledge is high enough." << setw(23) << "|";
    }

    if (percent > 84 && percent != 100) {
        mark = 5;
        cout << "| Percentage of correct answers:\x1b[32m " << percent
             << "\x1b[0m" << setw(21) << " |\n";
        cout << "| Your mark: " << mark << setw(42) << "|\n";
        cout << "| Such excellent result! " << setw(30) << "|";
    }

    if (percent == 100) {
        mark = 5;
        cout << "| Percentage of correct answers: \x1b[32m" << percent
             << setw(24) << " \x1b[0m|\n";
        cout << "| Your mark: " << mark << "+" << setw(41) << "|\n";
        cout << "| Such excellent result! " << setw(30) << "|";
    }
    cout << "\n=======================================================\n";
}
