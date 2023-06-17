#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
using namespace std;

class details {
public:
    string password;
    bool active;
    string color;
};
void displayMainMenu();
unordered_map<string, details> users;
const string credentialsFile = "credentials.txt";

void loadCredentialsFromFile() {
    ifstream file(credentialsFile);
    if (file.is_open()) {
        string username, password;
        int active;
        string color;
        while (file >> username >> password >> active >> color) {
            details user;
            user.password = password;
            user.active = (active == 1);
            user.color = color;
            users[username] = user;
        }
        file.close();
    }
}

void saveCredentialsToFile() {
    ofstream file(credentialsFile);
    if (file.is_open()) {
        for (const pair<string,details>& entry : users) {
            file << entry.first << " " << entry.second.password << " "
                 << entry.second.active << " " << entry.second.color << endl;
        }
        file.close();
    }
}

void write_blog(const details& user, const string& username) {
    string filename = username + "_blogs.txt";
    ofstream file(filename, ios::out);
    if (file.is_open()) {
        cout << "Enter your blog content:\n";
        string content;
        cin.ignore();
        getline(cin, content);
        file << content << "\n";
        file.close();
        cout << "Blog entry written successfully.\n";
    } else {
        cout << "Unable to write blog entry.\n";
    }
}

void view_blog(const details& user, const string& username) {
    string filename = username + "_blogs.txt";
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << "\n";
        }
        file.close();
    } else {
        cout << "Unable to open blog file.\n";
    }
}

void delete_blog(const details& user, const string& username) {
    string filename = username + "_blogs.txt";
    vector<string> blogs;
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        string line;
        int index = 0;
        while (getline(inputFile, line)) {
            blogs.push_back(line);
            cout << "[" << index << "] " << line << "\n";
            index++;
        }
        inputFile.close();

        if (blogs.empty()) {
            cout << "No blogs found.\n";
            return;
        }

        cout << "Enter the index of the blog you want to delete: ";
        int entryIndex;
        cin >> entryIndex;

        if (entryIndex >= 0 && entryIndex < blogs.size()) {
            blogs.erase(blogs.begin() + entryIndex);
            ofstream outputFile(filename, ios::out);
            if (outputFile.is_open()) {
                for (const string& blog : blogs) {
                    outputFile << blog << "\n";
                }
                outputFile.close();
                cout << "Blog entry deleted successfully.\n";
            } else {
                cout << "Unable to delete blog entry.\n";
            }
        } else {
            cout << "Invalid blog entry index.\n";
        }
    } else {
        cout << "Unable to open blog file.\n";
    }
}
void login() {
    string name;
    cout << "Enter your name: ";
    getline(cin, name);

    string pass;
    cout << "Enter your password: ";
    getline(cin, pass);

    if (users.find(name) != users.end() && users[name].password == pass) {
        cout << "Login successful" << endl;
        cout << "Press 1: Write a blog" << endl;
        cout << "Press 2: View all blogs" << endl;
        cout << "Press 3: Delete a blog" << endl;
        cout << "Press 4: Exit" << endl;

        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                write_blog(users[name], name);
                break;
            case 2:
                view_blog(users[name], name);
                break;
            case 3:
                delete_blog(users[name], name);
                break;
            case 4:
                exit(0);
            default:
                cout << "Invalid choice" << endl;
                break;
        }
    } else {
        cout << "Login failed" << endl;
    }
    
    
    displayMainMenu();
}


void Register() {
    string name;
    string pass;
    string color;
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your password: ";
    getline(cin, pass);
    cout << "Enter your favorite color as a security question for account backup: ";
    getline(cin, color);
    details u;
    u.password = pass;
    u.active = true;
    u.color = color;
    users[name] = u;
    saveCredentialsToFile();
    cout << "Registration successful" << endl;
    
   
    displayMainMenu();
   
}

void forgot() {
    string name;
    cout << "Enter your username: ";
    getline(cin, name);
    if (users.find(name) != users.end()) {
        string color;
        cout << "Enter your security answer: What is your favorite color? ";
        getline(cin, color);
        if (users[name].color == color) {
            cout << "Your password is " << users[name].password << endl;
        } else {
            cout << "Incorrect security answer" << endl;
            int val = 0;
            cout << "Do you want to try again? (1:yes,0:no) ";
            cin >> val;
            cin.ignore();
            if (val == 1) {
                forgot();
            } else {
                exit(0);
            }
        }
    } else {
        cout << "User not found" << endl;
        int val = 0;
        cout << "Do you want to try again? (1:yes,0:no) ";
        cin >> val;
        cin.ignore();
        if (val == 1) {
            forgot();
        } else {
            exit(0);
        }
    }
}
void displayMainMenu() {
    
    cout << "----- Press 1: LOG IN" << endl;
    cout << "----- Press 2: REGISTER" << endl;
    cout << "----- Press 3: FORGOT PASSWORD" << endl;
    cout << "----- Press 4: EXIT" << endl;
     int choice;
    cin >> choice;
    cin.ignore();
    while (choice < 5) {
        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                Register();
                break;
            case 3:
                forgot();
                break;
            case 4:
                exit(0);
                break;
            default:
                cout << "Invalid input" << endl;
                break;
        }
    }
    
}
int main() {
    loadCredentialsFromFile();
    displayMainMenu();
   
    return 0;
}
