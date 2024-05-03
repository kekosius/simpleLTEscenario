#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int skipLine(ifstream *fin)
{
    string word = "";
    if (!getline(*fin, word)) {return 0;}
    return 1;
}

double findSimulationTime()
{

    ifstream fin;
    fin.open("UlMacStats.txt");

    if (!fin.is_open()){
        cout << "File name UlMacStats.txt doesn't exist in this folder.\n";
        return 0;
    }

    if (!skipLine(&fin)) {
        cout << "File UlMacStats.txt doesn't contain any data.\n";
        return 0;
    }

    double time;
    while (!fin.eof()) {
        fin >> time;
        if (!skipLine(&fin)) {break;}
    }

    fin.close();
    return time;
}

struct UeThroughput
{
    int firstUeBytesSum;
    int secondUeBytesSum;
};

UeThroughput findUEstats(string filename)
{
    ifstream fin;
    fin.open(filename);

    if (!fin.is_open()){
        cout << "File name " << filename << " doesn't exist in this folder.\n";
        return {0};
    }

    if (!skipLine(&fin)) {
        cout << "File " << filename << " doesn't contain any data.\n";
        return {0};
    }

    int firstUeBytesSum = 0;
    int secondUeBytesSum = 0;

    double trashVar;
    int IMSI;
    int TxBytes;
    int RxBytes;

    while (!fin.eof()) {
        fin >> trashVar >> trashVar >> trashVar >> IMSI >> trashVar;
        fin >> trashVar >> trashVar >> TxBytes >> trashVar >> RxBytes;
        if (!skipLine(&fin)) {break;}
        if (IMSI == 1) {firstUeBytesSum += TxBytes + RxBytes;}
        else {secondUeBytesSum += TxBytes + RxBytes;}
    }

    UeThroughput anw;
    anw.firstUeBytesSum = firstUeBytesSum;
    anw.secondUeBytesSum = secondUeBytesSum;
    return anw;
}

int main()
{
    double time = findSimulationTime();

    UeThroughput DlStats = findUEstats("DlRlcStats.txt");
    UeThroughput UlStats = findUEstats("UlRlcStats.txt");

    cout << "First UE (IMSI = 1): \n";
    cout << "DL: " << DlStats.firstUeBytesSum*8/(1000*1000*time) << " Mbit/s \n";
    cout << "UL: " << UlStats.firstUeBytesSum*8/(1000*1000*time) << " Mbit/s \n";

    cout << "Second UE (IMSI = 2): \n";
    cout << "DL: " << DlStats.secondUeBytesSum*8/(1000*1000*time) << " Mbit/s \n";
    cout << "UL: " << UlStats.secondUeBytesSum*8/(1000*1000*time) << " Mbit/s \n";

    return 0;
}