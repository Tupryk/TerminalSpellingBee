#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

char alphabet[] = {'a', 'b', 'c', 'd',
                   'e', 'f', 'g', 'e',
                   'i', 'j', 'k', 'l',
                   'm', 'n', 'o', 'p',
                   'q', 'r', 's', 't',
                   'u', 'v', 'w', 'x',
                   'y', 'z'};

int vocals[] = {0, 4, 8, 14, 20};

void letter_convos(std::vector<std::string> words);

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
    "|                            /  |\n"
    "|   S    Spelling - Bee     ()  |\n"
    "|   p                           |\n"
    "|   e       _\\\\//___            |\n"
    "|   l     / U  | | | \\       B  |\n"
    "|   l    |     | | |  |--    e  |\n"
    "|   i     \\·___|_|_|_/       e  |\n"
    "|   n                           |\n"
    "|   g    Spelling - Bee         |\n"
    "|                               |\n"
    "+-------------------------------+\n"
    << std::endl;

    std::cout << "Welcome to Spelling-Bee!" << std::endl;

    std::cout << "Here are your Letters: \n" << std::endl;

    print_chars(letters);

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
        if (letters_allowed(w, letters))
            results.push_back(w);
    }
    return results;
}


int main ()
{
    srand(time(NULL));

    std::vector<std::string> words = getFileWords();

    letter_convos(words);

    std::vector<char> letters = getLetters();

    std::vector<std::string> results = possible_results(words, letters);

    printIntro(letters);

    std::cout << "Possible words: " << results.size() << std::endl;

    std::vector<std::string> found_words;

    while (true)
    {
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

        if (found_words.size() > 0) {
            std::cout << "Your words(" << found_words.size() << "): " << std::endl;
            for (auto w : found_words)
                std::cout << w << std::endl;
        }
        std::cout << "Words left: " << results.size()-found_words.size() << std::endl;
        std::cout << "Your letters: " << std::endl;
        print_chars(letters);
    }

    std::cout << "Thanks for playing, see you soon!" << std::endl;
    return 0;
}

void letter_convos(std::vector<std::string> words) {
    std::cout << "Calculating best convos..." << std::endl;
    std::vector<char> letters(7);
    std::vector<std::string> best_convos;
    for (int a = 0; a < 26; a++) {
        for (int b = 0; b < 26; b++) {
            for (int c = 0; c < 26; c++) {
                for (int d = 0; d < 26; d++) {
                    for (int e = 0; e < 26; e++) {
                        for (int f = 0; f < 26; f++) {
                            for (int g = 0; g < 26; g++) {
                                if (a != b && a != c && a != d && a != e && a != f && a != g &&
                                    b != c && b != d && b != e && b != f && b != g &&
                                    c != d && c != e && c != f && c != g &&
                                    d != e && d != f && d != g &&
                                    e != f && e != g &&
                                    f != g) {
                                    letters[0] = alphabet[a];
                                    letters[1] = alphabet[b];
                                    letters[2] = alphabet[c];
                                    letters[3] = alphabet[d];
                                    letters[4] = alphabet[e];
                                    letters[5] = alphabet[f];
                                    letters[6] = alphabet[g];
                                    
                                    std::vector<std::string> results = possible_results(words, letters);
                                    if (results.size() >= 16) {
                                        std::string set(7, 'x');
                                        set[0] = letters[0];
                                        set[1] = letters[1];
                                        set[2] = letters[2];
                                        set[3] = letters[3];
                                        set[4] = letters[4];
                                        set[5] = letters[5];
                                        set[6] = letters[6];
                                        best_convos.push_back(set);
                                    }
                                }
                            }
                        }
                    }
                }
                std::cout << "c: " << c << "/26" << std::endl;
            }
            std::cout << "b: " << b << "/26" << std::endl;
        }
        std::cout << "a: " << a << "/26" << std::endl;
    }
    std::cout << "Done." << std::endl;

    std::ofstream output_file("./best_letter_convos.txt");
    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
    std::copy(best_convos.begin(), best_convos.end(), output_iterator);
}
