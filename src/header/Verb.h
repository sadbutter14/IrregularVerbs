#ifndef VERB
#define VERB

#include <string>

class Verb {
private:
    std::string array_of_verbs[121][3];
    std::string word;
    std::string form;
    std::string userVerb;
    bool simple{};
    bool participle{};
    int right{};
    int wrong{};
    int index_i{};
    int index_j{};
    int right_value{};

public:
    bool read_from_file(const std::string& filePath);
    static void rand_verbs(int* array, int size);
    void check_verbs(const int* array, int size);
    bool equality_right(const int* array);
    bool equality_wrong(const int* array);
    int result(int number_of_verbs) const;
    void Set_user_verb(std::string verb);
    void Set_index_i(int i);
    void Set_index_j(int j);
    void Set_right_value(int value);

private:
    void message_right() const;
    void message_wrong(const int* array);
    void print_form() const;
    void print_random_verb(const int* array);
};

#endif