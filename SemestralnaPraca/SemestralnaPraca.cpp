

#include <iostream>
#include <libds/amt/implicit_sequence.h>
#include <fstream>
#include <string>
#include <Windows.h>

#include "Searcher.h"
#include "UzemnyCelok.h"

using namespace std;
//using namespace ds;


vector<string> SplitStr(string str)
{
    int index = 0;
    vector<string> splitStirngs;
    char delim = ';';
    char charInString ;
    string findString = "";
    
    for(int i = 0 ; i < str.size(); i++)
    {
        charInString = str[i];
	    if (charInString != delim)
	    {
            findString.push_back(charInString);
            continue;
	    }
	    else
	    {
            
            splitStirngs.push_back(findString);
            findString = "";
	    }
    }

    splitStirngs.push_back(findString);
	return splitStirngs;
}

vector<UzemnyCelok> NacitajUzemnyCelok(ifstream *p_streamRead, string p_path)
{
    p_streamRead->open(p_path);
    vector<UzemnyCelok> UzemneCelky;
    if (p_streamRead->fail())
        printf("Cannot open file");

    string line = "";
    while (!p_streamRead->eof())
    {
        getline(*p_streamRead, line);
        vector<string> obecString = SplitStr(line);
        if (line == "")
            break;

        if (obecString.at(0) == "sortNumber")
            continue;

        int sortNumber = stoi(obecString.at(0));
        UzemnyCelok kraj = UzemnyCelok(sortNumber, obecString.at(1), obecString.at(2), obecString.at(3), obecString.at(4), obecString.at(5));
        UzemneCelky.push_back(kraj);
    }
    return UzemneCelky;
}

void StartWithString(string p_startString)
{
	
}

int main()
{
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);

    ds::amt::ImplicitSequence<UzemnyCelok*> is;
    string path_kraje = "kraje.csv";
	string path_okresy = "okresy.csv";
    string path_obce = "obce.csv";

    string delimiter = ";";

	ifstream kraje;
    ifstream okresy;
    ifstream obce;

    vector<UzemnyCelok> loadKraje;
    vector<UzemnyCelok> loadOkresy;
    vector<UzemnyCelok> loadObce;

    loadKraje = NacitajUzemnyCelok(&kraje, path_kraje);
    loadOkresy = NacitajUzemnyCelok(&okresy, path_okresy);
    loadObce = NacitajUzemnyCelok(&obce, path_obce);

    Searcher search = Searcher(loadKraje,loadOkresy,loadObce);
    search.startsWithString("Brat");


}