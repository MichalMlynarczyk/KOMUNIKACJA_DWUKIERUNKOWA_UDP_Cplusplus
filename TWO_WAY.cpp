#include "RECEIVER/RECEIVER_TEMPLATE.cpp"
#include "SENDER/SENDER_TEMPLATE.cpp"
#include <thread>

using namespace std;

HANDLE hConsole;
string position;

void clearScreen() {
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}

int main(){

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    clearScreen();

    // Pobierz  NR PORTU
    string PORT;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    cout << "Podaj numer portu na ktorym bedziemy nasluchiwac: ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    getline(cin, PORT);

    RECEIVER receiver;
    thread receiverThread(&RECEIVER::_receiveData, &receiver, stoi(PORT));

    // Wykonuj dalej kod 
    receiverThread.detach();

    // Pobierz  IP
    string IP;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    cout << "Podaj numer IP, gdzie bedziemy wysylac dane: ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    getline(cin, IP);
    // Pobierz  NR PORTU
    string PORT_;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    cout << "Podaj numer portu, gdzie bedziemy wysylac dane: ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    getline(cin, PORT_);

    SENDER_TEMP send;
    send._startupWinsock();
    send._createHintStructure(stoi(PORT_), IP);

    while (true){
        string input;
        cout << ">: ";
        getline(std::cin, input);
        send._send(input);
    }

    send._shutdown();

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}