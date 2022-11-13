#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <bitset>

char alphabet[] = {'a', 'b', 'c', 'd',
                   'e', 'f', 'g', 'e',
                   'i', 'j', 'k', 'l',
                   'm', 'n', 'o', 'p',
                   'q', 'r', 's', 't',
                   'u', 'v', 'w', 'x',
                   'y', 'z'};

int vocals[] = {0, 4, 8, 14, 20};

void letter_convos(std::vector<std::string> words);
std::vector<uint32_t> words_to_numbers(std::vector<std::string> words);

struct letter_convo_t {
    uint32_t must_have = 0;
    uint32_t legal_letters = 0;
};

void print_chars(std::vector<char> letters) {
    for (int i = 0; i < letters.size(); i++) {
        std::cout << letters[i];
        if (i < letters.size()-1)
            std::cout << ", ";
    }
    std::cout << "\n";
}

bool inList(std::vector<std::string> list, std::string param) {
    return std::find(list.begin(), list.end(), param) != list.end();
}

bool inList(std::vector<char> list, char param) {
    return std::find(list.begin(), list.end(), param) != list.end();
}

void printIntro(std::vector<char> letters)
{
    std::cout <<
    "+-------------------------------+\n"
    "|                            \033[1;32m/\033[0m  |\n"
    "|   \033[1;32mS\033[0m    \033[1;32mSpelling - Bee\033[0m     \033[1;32m()\033[0m  |\n"
    "|   \033[1;32mp\033[0m                           |\n"
    "|   \033[1;32me\033[0m       \033[1;33m_\033[0m\033[1;36m\\\\//\033[0m\033[1;33m___\033[0m            |\n"
    "|   \033[1;32ml\033[0m     \033[1;33m/\033[0m U  | | | \033[1;33m\\\033[0m       \033[1;32mB\033[0m  |\n"
    "|   \033[1;32ml\033[0m    \033[1;33m|\033[0m     | | |  \033[1;33m|\033[0m--    \033[1;32me\033[0m  |\n"
    "|   \033[1;32mi\033[0m     \033[1;33m\\\033[0m·\033[1;33m___\033[0m|\033[1;33m_\033[0m|\033[1;33m_\033[0m|\033[1;33m_/\033[0m       \033[1;32me\033[0m  |\n"
    "|   \033[1;32mn\033[0m                           |\n"
    "|   \033[1;32mg\033[0m    \033[1;32mSpelling - Bee\033[0m         |\n"
    "|                               |\n"
    "+-------------------------------+\n"
    << std::endl;

    std::cout << "Welcome to Spelling-Bee!" << std::endl;

    std::cout << "Here are your Letters: " << std::endl;
    print_chars(letters);
    std::cout << std::endl;

    std::cout << "The first letter must always be on the word, " << std::endl;
    std::cout << "write -exit to exit or -giveup for the awnsers." << std::endl;

    std::cout << "Good luck!!!" << std::endl;
}

std::vector<char> getLetters() {
    std::vector<char> letters;
    std::ifstream file("best_letter_convos.txt");
    std::vector<std::string> best_cons;
    for(std::string con; file >> con; )
        best_cons.push_back(con);
    int index = rand()%best_cons.size();
    for (int i = 0; i < 7; i++)
        letters.push_back(best_cons[index][i]);
    return letters;
}

std::vector<std::string> getFileWords()
{
    std::ifstream file("words.txt");
    std::vector<std::string> words;
    for(std::string word; file >> word; )
        words.push_back(word);
    return words;
}

bool letters_allowed(std::string input, std::vector<char> letters)
{
    for (std::string::size_type i = 0; i < input.size(); i++) {
        if (!inList(letters, static_cast<char>(input[i])))
            return false;
    }
    return input.find(letters[0]) != std::string::npos;
}

std::vector<std::string> possible_results(std::vector<std::string> words, std::vector<char> letters) {
    std::vector<std::string> results;
    for (std::string w : words) {
        if (letters_allowed(w, letters) && w.size() > 3)
            results.push_back(w);
    }
    return results;
}


int main ()
{
    srand(time(NULL));

    std::vector<std::string> words = getFileWords();

    //letter_convos(words);

    std::vector<char> letters = getLetters();

    std::vector<std::string> results = possible_results(words, letters);

    printIntro(letters);

    std::cout << "Possible words: " << results.size() << std::endl;

    std::vector<std::string> found_words;

    while (true)
    {
        std::cout << "________________________" << std::endl;
        std::string input;
        std::cin >> input;

        if (input.compare("-exit") == 0)
            break;
        if (input.compare("-giveup") == 0) {
            for (auto r : results) {
                std::cout << r;
                std::cout << ", ";
            }
            std::cout << "\n";
            break;
        }

        if (input.size() <= 3)
            std::cout << "Word too short." << std::endl;
        else if (!letters_allowed(input, letters))
            std::cout << "Invalid letters." << std::endl;
        else if (!inList(words, input))
            std::cout << "Word does not exist!" << std::endl;
        else if (inList(found_words, input))
            std::cout << "Already found word!" << std::endl;
        else
            found_words.push_back(input);

        if (found_words.size() == results.size())
            std::cout << "You found all words!" << std::endl;

        if (found_words.size() > 0) {
            std::cout << "\nYour words(" << found_words.size() << "): " << std::endl;
            for (auto w : found_words)
                std::cout << w << std::endl;
        }
        std::cout << "\nWords left: " << results.size()-found_words.size() << std::endl;
        std::cout << "Your letters: " << std::endl;
        print_chars(letters);
        std::cout << "________________________\n" << std::endl;
    }

    std::cout << "Thanks for playing, see you soon!" << std::endl;
    return 0;
}

std::vector<uint32_t> words_to_numbers(std::vector<std::string> words) {
    std::vector<uint32_t> numbers;
    for (std::string w : words) {
        if (w.size() > 3) {
            uint32_t num = 0;
            for (std::string::size_type i = 0; i < w.size(); i++) {
                num |= 1 << (int(w[i])-97);
            }
            numbers.push_back(num);
        }
    }
    std::ofstream output_file("./words_as_numbers.txt");
    std::ostream_iterator<uint32_t> output_iterator(output_file, "\n");
    std::copy(numbers.begin(), numbers.end(), output_iterator);

    return numbers;
}

bool bitwise_allowed_letters(uint32_t word, uint32_t illegal_letters, uint32_t must_have) {
    return !(word & illegal_letters) && (word & must_have);
}

unsigned int bitwise_allowed_words_count(std::vector<uint32_t> words, uint32_t illegal_letters, uint32_t must_have) {
    unsigned int sum = 0;
    for (auto w : words) {
        if (bitwise_allowed_letters(w, illegal_letters, must_have))
            sum++;
    }
    return sum;
}

std::vector<std::string> bitmask_to_string(std::vector<letter_convo_t> letters_mask) {
    std::vector<std::string> strings;
    for (auto lm : letters_mask) {
        std::string new_s = "+++++++";
        unsigned int index = 1;
        std::bitset<32> legal_set(lm.legal_letters);
        std::bitset<32> must_set(lm.must_have);
        for (int j = 0; j < 32; j++) {
            if (legal_set[j] && !must_set[j]) {
                new_s[index] = char(j+97);
                index++;
            } else if (legal_set[j]) {
                new_s[0] = char(j+97);
            }
        }
        strings.push_back(new_s);
    }
    return strings;
}

void letter_convos(std::vector<std::string> words) {
    std::cout << "Calculating best convos..." << std::endl;

    std::vector<uint32_t> words_as_numbers = words_to_numbers(words);

    std::vector<letter_convo_t> best_convos;

    uint32_t illegal_letters = 0;

    std::vector<letter_convo_t> bitmasks;

    uint32_t length = pow(2, 26);
    for (uint32_t i = 0; i < length; i++) {
        std::bitset<32> bitSet(i);
        unsigned int count = bitSet.count();
        if (count == 7) {
            for (int j = 0; j < 32; j++) {
                if (bitSet[j]) {
                    letter_convo_t bitmask;
                    bitmask.must_have |= 1 << j;
                    bitmask.legal_letters = i;
                    bitmasks.push_back(bitmask);
                }
            }
        }
    }

    static const unsigned int possible_letter_convos = bitmasks.size();
    std::cout << "Possible letter convos: " << possible_letter_convos << std::endl;

    for (auto bm : bitmasks)
    {
        illegal_letters = 0;
        illegal_letters = ~(illegal_letters & 0);
        illegal_letters = ~(bm.legal_letters & illegal_letters);
        
        if (bitwise_allowed_words_count(words_as_numbers, illegal_letters, bm.must_have) >= 7)
            best_convos.push_back(bm);
    }
    std::cout << "Done." << std::endl;

    std::vector<std::string> best_convos_s = bitmask_to_string(best_convos);

    std::ofstream output_file("./best_letter_convos.txt");
    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
    std::copy(best_convos_s.begin(), best_convos_s.end(), output_iterator);
}
