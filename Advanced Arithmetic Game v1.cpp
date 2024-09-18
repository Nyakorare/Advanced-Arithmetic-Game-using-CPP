#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>

using namespace std;


void countdown(int seconds) {
    for (int i = seconds; i > 0; --i) {
        cout << i << "...";
        cout.flush();
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "Go!" << endl;
}

class User {
public:
    string username;
    string password;
    User* next;
    bool loggedIn;
    int additionScore;
    int subtractionScore;
    int multiplicationScore;
    int divisionScore;

    User(const string& name, const string& pass) {
        username = name;
        password = pass;
        next = nullptr;
        loggedIn = false;
        additionScore = 0;
        subtractionScore = 0;
        multiplicationScore = 0;
        divisionScore = 0;
    }
};

class UserDatabase {
private:
    User* head;

public:
    UserDatabase() {
        head = nullptr;
    }

    ~UserDatabase() {
        while (head != nullptr) {
            User* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool isUsernameTaken(const string& username) {
        User* current = head;
        while (current != nullptr) {
            if (current->username == username) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void addUser(const string& username, const string& password) {
        if (isUsernameTaken(username)) {
            cout << "===========================================================\n";
            cout << "Username already taken. Please choose a different username.\n";
            system("pause");
            return;
        }
        User* newUser = new User(username, password);
        if (head == nullptr) {
            head = newUser;
        } else {
            User* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newUser;
        }
    }

    User* getUser(const string& username, const string& password) {
        User* current = head;
        while (current != nullptr) {
            if (current->username == username && current->password == password) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void saveToFile() {
    ofstream file("userdata.txt");
    if (file.is_open()) {
        User* current = head;
        while (current != nullptr) {
            file << current->username << " " << current->password << " "
                 << current->additionScore << " " << current->subtractionScore << " "
                 << current->multiplicationScore << " " << current->divisionScore << endl;
            current = current->next;
        }
        file.close();
        system("cls");
        cout << "\n****************************************************";
        cout << "\n*              Thank you for Playing!              *";
        cout << "\n****************************************************";
    } else {
        cout << "Unable to open the file for saving user data." << endl;
    }
}

    void loadFromFile() {
        ifstream file("userdata.txt");
        if (file.is_open()) {
            string username, password;
            int additionScore, subtractionScore, multiplicationScore, divisionScore;
            while (file >> username >> password >> additionScore >> subtractionScore
                        >> multiplicationScore >> divisionScore) {
                addUser(username, password);
                User* user = getUser(username, password);
                user->additionScore = additionScore;
                user->subtractionScore = subtractionScore;
                user->multiplicationScore = multiplicationScore;
                user->divisionScore = divisionScore;
            }
            file.close();
            cout << "User data loaded from file." << endl;
        } else {
            cout << "Unable to open the file for loading user data." << endl;
        }
    }

    void displayAdditionLeaderboard() {
    vector<User*> users;
    User* current = head;
    while (current != nullptr) {
        users.push_back(current);
        current = current->next;
    }

    sort(users.begin(), users.end(), [](User* a, User* b) {
        return a->additionScore > b->additionScore;
    });

    cout << "====================================\n";
    cout << "=       Addition Leaderboard       =\n";
    cout << "====================================\n";
    cout << "Rank\tUsername\tScore\n";
    for (int i = 0; i < min(10, static_cast<int>(users.size())); i++) {
        cout << i + 1 << "\t" << users[i]->username << "\t\t" << users[i]->additionScore << endl;
    }
    cout << endl;
}
    void displaySubtractionLeaderboard() {
    vector<User*> users;
    User* current = head;
    while (current != nullptr) {
        users.push_back(current);
        current = current->next;
    }

    sort(users.begin(), users.end(), [](User* a, User* b) {
        return a->subtractionScore > b->subtractionScore;
    });

    cout << "=====================================\n";
    cout << "=      Subtraction Leaderboard      =\n";
    cout << "=====================================\n";
    cout << "Rank\tUsername\tScore\n";
    for (int i = 0; i < min(10, static_cast<int>(users.size())); i++) {
        cout << i + 1 << "\t" << users[i]->username << "\t\t" << users[i]->subtractionScore << endl;
    }
    cout << endl;
}

    void displayMultiplicationLeaderboard() {
    vector<User*> users;
    User* current = head;
    while (current != nullptr) {
        users.push_back(current);
        current = current->next;
    }

    sort(users.begin(), users.end(), [](User* a, User* b) {
        return a->multiplicationScore > b->multiplicationScore;
    });

    cout << "========================================\n";
    cout << "=      Multiplication Leaderboard      =\n";
    cout << "========================================\n";
    cout << "Rank\tUsername\tScore\n";
    for (int i = 0; i < min(10, static_cast<int>(users.size())); i++) {
        cout << i + 1 << "\t" << users[i]->username << "\t\t" << users[i]->multiplicationScore << endl;
    }
    cout << endl;
}

    void displayDivisionLeaderboard() {
    vector<User*> users;
    User* current = head;
    while (current != nullptr) {
        users.push_back(current);
        current = current->next;
    }

    sort(users.begin(), users.end(), [](User* a, User* b) {
        return a->divisionScore > b->divisionScore;
    });

    cout << "====================================\n";
    cout << "=       Division Leaderboard       =\n";
    cout << "====================================\n";
    cout << "Rank\tUsername\tScore\n";
    for (int i = 0; i < min(10, static_cast<int>(users.size())); i++) {
        cout << i + 1 << "\t" << users[i]->username << "\t\t" << users[i]->divisionScore << endl;
    }
    cout << endl;
}

    void displayOverallLeaderboard() {
    vector<User*> users;
    User* current = head;
    while (current != nullptr) {
        users.push_back(current);
        current = current->next;
    }

    sort(users.begin(), users.end(), [](User* a, User* b) {
        double averageScoreA = (a->additionScore + a->subtractionScore + a->multiplicationScore + a->divisionScore) / 4.0;
        double averageScoreB = (b->additionScore + b->subtractionScore + b->multiplicationScore + b->divisionScore) / 4.0;
        return averageScoreA > averageScoreB;
    });

    cout << "===================================\n";
    cout << "=       Overall Leaderboard       =\n";
    cout << "===================================\n";
    cout << "Rank\tUsername\tAverage Score\n";
    for (int i = 0; i < min(10, static_cast<int>(users.size())); i++) {
        double averageScore = (users[i]->additionScore + users[i]->subtractionScore +
                               users[i]->multiplicationScore + users[i]->divisionScore) / 4.0;
        cout << i + 1 << "\t" << users[i]->username << "\t\t" << averageScore << endl;
    }
    cout << endl;
}
};

class Game {
public:
    virtual void play(User* user) = 0;
};

class AdditionGame : public Game {
public:
    void play(User* user) {
        cout << "====================================================================\n";
        cout << "= Welcome to the Addition Game, " << user->username << "!\n";
        cout << "= Let's test your addition skills. Answer the following questions: =\n";
        cout << "====================================================================\n";

        srand(static_cast<unsigned int>(time(nullptr)));

        int score = 0;

        while (true) {
            int num1 = rand() % 10;
            int num2 = rand() % 10;

            int correctAnswer = num1 + num2;

            cout << "\nQuestion: ";
            cout << num1 << " + " << num2 << " = ";

            int userAnswer;
            cin >> userAnswer;

            if (userAnswer == correctAnswer) {
                cout << "Correct!\n";
                score++;
            } else {
                cout << "\nIncorrect! The correct answer is " << correctAnswer << ".\n";
                break;
            }
        }
        if (score > user->additionScore && dynamic_cast<AdditionGame*>(this) != nullptr) {
        user->additionScore = score;
        }
        cout << "====================================================================\n";
        cout << "= Game Over! You answered " << score << " questions correctly.\n";
        cout << "====================================================================\n";
        system("pause");
    }
};

class SubtractionGame : public Game {
public:
    void play(User* user) {
        cout << "=======================================================================\n";
        cout << "= Welcome to the Subtraction Game, " << user->username << "!\n";
        cout << "= Let's test your subtraction skills. Answer the following questions: =\n";
        cout << "=======================================================================\n";

        srand(static_cast<unsigned int>(time(nullptr)));

        int score = 0;

        while (true) {
            int num1 = rand() % 10;
            int num2 = rand() % 10;

            if (num2 > num1) {
                int temp = num1;
                num1 = num2;
                num2 = temp;
            }

            int correctAnswer = num1 - num2;

            cout << "\nQuestion: ";
            cout << num1 << " - " << num2 << " = ";

            int userAnswer;
            cin >> userAnswer;

            if (userAnswer == correctAnswer) {
                cout << "Correct!\n";
                score++;
            } else {
                cout << "\nIncorrect! The correct answer is " << correctAnswer << ".\n";
                break;
            }
        }
        if (score > user->subtractionScore && dynamic_cast<SubtractionGame*>(this) != nullptr) {
        user->subtractionScore = score;
    }
        cout << "====================================================================\n";
        cout << "= Game Over! You answered " << score << " questions correctly.\n";
        cout << "====================================================================\n";
        system("pause");
    }
};

class MultiplicationGame : public Game {
public:
    void play(User* user) {
        cout << "==========================================================================\n";
        cout << "= Welcome to the Multiplication Game, " << user->username << "!\n";
        cout << "= Let's test your multiplication skills. Answer the following questions: =\n";
        cout << "==========================================================================\n";

        srand(static_cast<unsigned int>(time(nullptr)));

        int score = 0;

        while (true) {
            int num1 = rand() % 10;
            int num2 = rand() % 10;

            int correctAnswer = num1 * num2;

            cout << "\nQuestion: ";
            cout << num1 << " * " << num2 << " = ";

            int userAnswer;
            cin >> userAnswer;

            if (userAnswer == correctAnswer) {
                cout << "Correct!\n";
                score++;
            } else {
                cout << "\nIncorrect! The correct answer is " << correctAnswer << ".\n";
                break;
            }
        }
        if (score > user->multiplicationScore && dynamic_cast<MultiplicationGame*>(this) != nullptr) {
        user->multiplicationScore = score;
    }
        cout << "====================================================================\n";
        cout << "= Game Over! You answered " << score << " questions correctly.\n";
        cout << "====================================================================\n";
        system("pause");
    }
};

class DivisionGame : public Game {
public:
    void play(User* user) {
        cout << "====================================================================\n";
        cout << "= Welcome to the Division Game, " << user->username << "!\n";
        cout << "= Let's test your division skills. Answer the following questions: =\n";
        cout << "====================================================================\n";

        srand(static_cast<unsigned int>(time(nullptr)));

        int score = 0;

        while (true) {
            int divisor = rand() % 9 + 1;
            int quotient = rand() % 10;
            int dividend = divisor * quotient;

            cout << "\nQuestion: ";
            cout << dividend << " / " << divisor << " = ";

            int userAnswer;
            cin >> userAnswer;

            if (userAnswer == quotient) {
                cout << "Correct!\n";
                score++;
            } else {
                cout << "\nIncorrect! The correct answer is " << quotient << ".\n";
                break;
            }
        }

        if (score > user->divisionScore && dynamic_cast<DivisionGame*>(this) != nullptr) {
            user->divisionScore = score;
        }

        cout << "====================================================================\n";
        cout << "= Game Over! You answered " << score << " questions correctly.\n";
        cout << "====================================================================\n";
        system("pause");
    }
};

void displayGameMenu(User* user) {
    system("cls");
    cout << "========================================\n";
    cout << "=              Game Menu:              =\n";
    cout << "========================================\n";
    cout << "= Welcome, " << user->username << "!\t\t       =\n";
    cout << "= 1. Addition Game                     =\n";
    cout << "= 2. Subtraction Game                  =\n";
    cout << "= 3. Multiplication Game               =\n";
    cout << "= 4. Division Game                     =\n";
    cout << "= 5. Leaderboard Menu                  =\n";
    cout << "= 6. Save & Logout                     =\n";
    cout << "========================================\n";
    cout << "= Enter your choice: ";
}

void displayLeaderboardMenu(UserDatabase& database) {
    system("cls");
    cout << "========================================\n";
    cout << "=           Leaderboard Menu:          =\n";
    cout << "========================================\n";
    cout << "= 1. Addition Leaderboard              =\n";
    cout << "= 2. Subtraction Leaderboard           =\n";
    cout << "= 3. Multiplication Leaderboard        =\n";
    cout << "= 4. Division Leaderboard              =\n";
    cout << "= 5. Overall Leaderboard               =\n";
    cout << "= 6. Go back to Game Menu              =\n";
    cout << "========================================\n";
    cout << "= Enter your choice: ";
}

void processGameMenuSelection(int selection, User* user, UserDatabase& database) {
    switch (selection) {
        case 1: {
            system("cls");
            AdditionGame additionGame;
            additionGame.play(user);
            break;
        }
        case 2: {
            system("cls");
            SubtractionGame subtractionGame;
            subtractionGame.play(user);
            break;
        }
        case 3: {
            system("cls");
            MultiplicationGame multiplicationGame;
            multiplicationGame.play(user);
            break;
        }
        case 4: {
            system("cls");
            DivisionGame divisionGame;
            divisionGame.play(user);
            break;
        }
        case 5:
            system("cls");
            displayLeaderboardMenu(database);
            break;
        case 6:
            user->loggedIn = false;
            database.saveToFile();
            break;
        default:
            cout << "========================================\n";
            cout << "= Invalid selection. Please try again. =\n";
            cout << "========================================\n";
            system("pause");
    }
}

void processLeaderboardMenuSelection(int lbselection, UserDatabase& database) {
    switch (lbselection) {
        case 1:
            system("cls");
            database.displayAdditionLeaderboard();
            system("pause");
            break;
        case 2:
            system("cls");
            database.displaySubtractionLeaderboard();
            system("pause");
            break;
        case 3:
            system("cls");
            database.displayMultiplicationLeaderboard();
            system("pause");
            break;
        case 4:
            system("cls");
            database.displayDivisionLeaderboard();
            system("pause");
            break;
        case 5:
            system("cls");
            database.displayOverallLeaderboard();
            system("pause");
            break;
        case 6:
            break; 
        default:
            cout << "========================================\n";
            cout << "= Invalid selection. Please try again. =\n";
            cout << "========================================\n";
            system("pause");
    }
}

int main() {
    UserDatabase database;
    database.loadFromFile();

    int choice;

    while (true) {
        system("cls");
        cout << "\nCreated by: Glenn R. Galbadores I";
        cout << "\n****************************************************";
        cout << "\n*            Welcome to Arithmetic Game            *";
        cout << "\n****************************************************\n";
        cout << "* 1. Register                                      *\n";
        cout << "* 2. Login                                         *\n";
        cout << "* 3. Quit                                          *\n";
        cout << "****************************************************\n";
        cout << "* Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            system("cls");
            string username, password;
            cout << "=================================\n";
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            database.addUser(username, password);
        } else if (choice == 2) {
            system("cls");
            string username, password;
            cout << "=================================\n";
            cout << "= Enter username: ";
            cin >> username;
            cout << "= Enter password: ";
            cin >> password;
            cout << "=================================" << endl;
            cout << "= Logging on in ";
            cout.flush();
            countdown(3);
            User* user = database.getUser(username, password);
            if (user == nullptr) {
                cout << "Invalid username or password. Please try again or register first.\n";
                system("pause");
                continue;
            }
            user->loggedIn = true;
            while (user->loggedIn) {
                displayGameMenu(user);
                int gameChoice;
                cin >> gameChoice;
                if (gameChoice == 5) {
                    while (true) {
                        displayLeaderboardMenu(database);
                        int lbChoice;
                        cin >> lbChoice;
                        processLeaderboardMenuSelection(lbChoice, database);
                        if (lbChoice == 6) {
                            break;
                        }
                    }
                } else if (gameChoice == 6) {
                    cout << "========================================" << endl;
                    cout << "= Logging out in ";
                    cout.flush();
                    countdown(3);
                    user->loggedIn = false;
                    database.saveToFile();
                } else {
                    processGameMenuSelection(gameChoice, user, database);
                }
            }
        } else if (choice == 3) {
            cout << "****************************************************" << endl;
            cout << "* Quitting in ";
            cout.flush();
            countdown(3);
            database.saveToFile();
            break;
        } else {
            cout << "****************************************************\n";
            cout << "* Invalid selection. Please try again.             *\n";
            cout << "****************************************************\n";
            system("pause");
        }
    }

    return 0;
}