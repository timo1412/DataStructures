
#include "libds/amt/explicit_sequence.h"
#include "libds/amt/explicit_hierarchy.h"
#include "libds/adt/table.h"
#include <Windows.h>
#include "UzemnyCelok.h"

#include <iostream>
#include <fstream>
#include <string>




using namespace std;
using namespace ds;


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

vector<UzemnyCelok> NacitajUzemnyCelok(string p_path)
{
    ifstream file_stream;
    file_stream.open(p_path);
    vector<UzemnyCelok> UzemneCelky;
	//ds:amt::ExplicitSequence<UzemnyCelok> uzemne_celky_seq;

    if (file_stream.fail())
        printf("Cannot open file");

    string line = "";
    while (!file_stream.eof())
    {
        getline(file_stream, line);
        vector<string> obecString = SplitStr(line);
        if (line == "")
            break;

        if (obecString.at(0) == "sortNumber")
            continue;

        int sortNumber = stoi(obecString.at(0));

        Type type;
        if (0 == p_path.find("kraje"))
            type = KRAJ;
        else if (0 == p_path.find("okresy"))
            type = OKRES;
        else
            type = OBEC;

    	UzemnyCelok uzemny_celok = UzemnyCelok(sortNumber,obecString.at(1),obecString.at(2),obecString.at(3),obecString.at(4),obecString.at(5),type);
    	UzemneCelky.push_back(uzemny_celok);
    }
	return UzemneCelky;
}

void NaplnHierarchiu(ds::amt::MultiWayExplicitHierarchy<UzemnyCelok> *p_m_hierar, vector<UzemnyCelok> p_kraje, vector<UzemnyCelok> p_okresy, vector<UzemnyCelok> p_obce)
{
    cout << "==============================" << endl;

    for (int i = 0 ; i < p_kraje.size() ; i++)
    {
        p_m_hierar->emplaceSon(*p_m_hierar->accessRoot(), i).data_ = p_kraje.at(i);
        for (int j = 0 ; j < p_okresy.size();j++)
        {
            int index_ukladania_hierarchie_okresu = 0;
            if (p_m_hierar->accessSon(*p_m_hierar->accessRoot(), i)->data_.getNote().substr(5, 5) == p_okresy.at(j).getCode().substr(0,5))
	        {
            	p_m_hierar->emplaceSon(*p_m_hierar->accessSon(*p_m_hierar->accessRoot(), i), index_ukladania_hierarchie_okresu).data_ = p_okresy.at(j);
                
                for (int l = 0 ; l < p_obce.size(); l++)
                {
	                if (p_m_hierar->accessSon(*p_m_hierar->accessSon(*p_m_hierar->accessRoot(), i),index_ukladania_hierarchie_okresu)->data_.getCode() == p_obce.at(l).getCode().substr(0,6))
	                {
                        int index_ukladania_hierarchie_obce = 0;
                        p_m_hierar->emplaceSon(*p_m_hierar->accessSon(*p_m_hierar->accessSon(*p_m_hierar->accessRoot(), i), index_ukladania_hierarchie_okresu), index_ukladania_hierarchie_obce).data_ = p_obce.at(l);
                        index_ukladania_hierarchie_obce++;
	                }
                }
                index_ukladania_hierarchie_okresu++;
	        }
        }
    }
}


void PrechadzajHierarchiu(ds::amt::MultiWayExplicitHierarchy<UzemnyCelok>* p_m_hierar)
{
    string vstup = "";
    string ukoncovaci_znak = "X";
    auto current = p_m_hierar->accessRoot();
    int index = 0;
    while (vstup != ukoncovaci_znak)
    {
        cout << "Prave si na " << current->data_.getTitle() << endl;
        cout << "Chces vy pisat synov stlac 1 " << endl;
        cout << "Chces prejst na vyssi uzemny celok stlac 2 " << endl;
        cout << "Chces prejst na syna stlac 3 " << endl;
        cout << "Chces ukoncit aplikaciu stlac 4 "  << endl;
        cout << "Zadajte predikat na vyhladavanie " << endl;
        cin >> vstup;
        index = stoi(vstup);

        switch (index)
        {
        case 1:
	        {
		        for (auto son : *current->sons_)
		        {
                    cout << son->data_.getTitle() << endl;
		        }
	        }
        case 2:
	        {
		        if (p_m_hierar->accessParent(*current) != nullptr)
                    current = p_m_hierar->accessParent(*current);
                break;
	        }
        case 3:
	        {
	            for (auto son : *current->sons_)
	            {
	                cout << son->data_.getTitle() << endl;
	            }
                cout << "Zadaj index syna " << endl;
                cin >> vstup;
                index = stoi(vstup);
	            if (p_m_hierar->accessSon(*current, index) != nullptr)
	            {
                    current = p_m_hierar->accessSon(*current, index);
	            }
                break;
	        }
        case 4:
	        {
            vstup = ukoncovaci_znak;
            break;
	        }
        default:
	        {
		        
	        }
        }
    }
}

int main()
{
    initHeapMonitor();
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);
    
    ds::amt::MultiWayExplicitHierarchy<UzemnyCelok> m_hierarchzy;

	//ds:amt::ExplicitSequence<UzemnyCelok> kraje_seq;
	//ds:amt::ExplicitSequence<UzemnyCelok> okresy_seq;
	//ds:amt::ExplicitSequence<UzemnyCelok> obce_seq;

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

    loadKraje = NacitajUzemnyCelok(path_kraje);
    loadOkresy = NacitajUzemnyCelok( path_okresy);
    loadObce = NacitajUzemnyCelok( path_obce);

    UzemnyCelok main_root = UzemnyCelok(0, "00", "Slovenska republika", "slovensko", "sk", "svk", KRAJINA);

    m_hierarchzy.emplaceRoot().data_ = main_root;

    NaplnHierarchiu(&m_hierarchzy, loadKraje, loadOkresy, loadObce);
    
    cout << "==============================" << endl;

    PrechadzajHierarchiu(&m_hierarchzy);

    ds::adt::SequenceTable<int, UzemnyCelok> table;

}














