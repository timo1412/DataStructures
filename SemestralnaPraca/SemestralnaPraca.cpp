
#include "libds/amt/explicit_sequence.h"
#include "libds/amt/implicit_sequence.h"
#include "libds/amt/explicit_hierarchy.h"
#include "libds/adt/sorts.h"
#include "libds/adt/table.h"
#include "libds/adt/list.h"
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

ds::amt::ImplicitSequence<UzemnyCelok> NacitajUzemnyCelok(string p_path)
{
    ifstream file_stream;
    file_stream.open(p_path);
	ds:amt::ImplicitSequence<UzemnyCelok> uzemne_celky_seq;

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

    	auto uzemny_celok = UzemnyCelok(sortNumber,obecString.at(1),obecString.at(2),obecString.at(3),obecString.at(4),obecString.at(5),type);
    	
        uzemne_celky_seq.insertLast();
        uzemne_celky_seq.accessLast()->data_ = uzemny_celok;
    }
	return uzemne_celky_seq;
}



ds::amt::MultiWayExplicitHierarchy<UzemnyCelok> NaplnHierarchiu(ds::amt::ImplicitSequence<UzemnyCelok> p_kraje_seq, ds::amt::ImplicitSequence<UzemnyCelok> p_okresy_seq, ds::amt::ImplicitSequence<UzemnyCelok> p_obce_seq)
{
	ds::amt::MultiWayExplicitHierarchy<UzemnyCelok> p_m_hierar;

   p_m_hierar.emplaceRoot().data_ = UzemnyCelok(1,"","Slovenska republika","","","",KRAJINA);
   auto& root = *p_m_hierar.accessRoot();

   for (int i = 0 ; i < p_kraje_seq.size() ; i++)
   {
       auto& kraj = p_m_hierar.emplaceSon(root, i);
       kraj.data_ = p_kraje_seq.access(i)->data_;
       
   	 p_m_hierar.emplaceSon(*p_m_hierar.accessRoot(), i).data_ = p_kraje_seq.access(i)->data_;
       for (int j = 0 ; j < p_okresy_seq.size();j++)
       {
           int index_ukladania_hierarchie_okresu = 0;
           if (p_m_hierar.accessSon(*p_m_hierar.accessRoot(), i)->data_.getNote().substr(5, 5) == p_okresy_seq.access(j)->data_.getCode().substr(0,5))
           {
               p_m_hierar.emplaceSon(*p_m_hierar.accessSon(*p_m_hierar.accessRoot(), i), index_ukladania_hierarchie_okresu).data_ = p_okresy_seq.access(j)->data_;
               p_m_hierar.accessSon(*p_m_hierar.accessRoot(), 1)->sons_;
               for (int l = 0 ; l < p_obce_seq.size(); l++)
               {
                   if (p_m_hierar.accessSon(*p_m_hierar.accessSon(*p_m_hierar.accessRoot(), i),index_ukladania_hierarchie_okresu)->data_.getCode() == p_obce_seq.access(l)->data_.getCode().substr(0,6))
                   {
                       int index_ukladania_hierarchie_obce = 0;
                       p_m_hierar.emplaceSon(*p_m_hierar.accessSon(*p_m_hierar.accessSon(*p_m_hierar.accessRoot(), i), index_ukladania_hierarchie_okresu), index_ukladania_hierarchie_obce).data_ = p_obce_seq.access(l)->data_;
                       index_ukladania_hierarchie_obce++;
                   }
               }
               index_ukladania_hierarchie_okresu++;
           }
       }
   }

   return p_m_hierar;
}



void ZoradSynovHieraarchie( ds::amt::MultiWayExplicitHierarchyBlock<UzemnyCelok>* node)
{
    ds::adt::BubbleSort<amt::MultiWayExplicitHierarchyBlock<UzemnyCelok>*> sort;
    auto compareVowelsCount = [](ds::amt::MultiWayExplicitHierarchyBlock<UzemnyCelok>* node_a, ds::amt::MultiWayExplicitHierarchyBlock<UzemnyCelok>* node_b)
    {
        int cout_a = 0;
        int cout_b = 0;

        const string samohlasky = "aeiouAEIOUáéíóú";
        
        for (int i = 0; i < node_a->data_.getTitle().size(); i++)
        {
            char ch = node_a->data_.getTitle()[i];
            if (i - 1 != node_a->data_.getTitle().size() - 1)
            {
                char dvoj = node_a->data_.getTitle()[i+1];
                if (ch == 'i' && (dvoj == 'a' || dvoj == 'u' || dvoj == 'e'))
                {
                    i++;
                    continue;
                }
            }

            if (samohlasky.find(ch) != string::npos)
                cout_a++;
        }

        for (int i = 0; i < node_b->data_.getTitle().size(); i++)
        {
            char ch = node_b->data_.getTitle()[i];
            if (i - 1 != node_b->data_.getTitle().size() - 1)
            {
                char dvoj = node_b->data_.getTitle()[i + 1];
                if (ch == 'i' && (dvoj == 'a' || dvoj == 'u' || dvoj == 'e'))
                {
                    i++;
                    continue;
                }
            }

            if (samohlasky.find(ch) != string::npos)
                cout_b++;
        }

        return cout_a < cout_b;
    };

    sort.sort(*node->sons_, compareVowelsCount);
}

void PrechadzajHierarchiu(ds::amt::MultiWayExplicitHierarchy<UzemnyCelok>* p_m_hierar)
{
    string vstup = "";
    string ukoncovaci_znak = "X";
   // cout<< p_m_hierar->accessRoot()->data_.getTitle()<<endl;
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
                //ZoradSynovHieraarchie( current);
		        for (auto son : *current->sons_)
		        {
                    cout << son->data_.getTitle() << endl;
		        }
                break;
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

void NacitajDoTabulky(ds::adt::HashTable<string, UzemnyCelok> *p_table, ds::amt::ImplicitSequence<UzemnyCelok> p_kraje)
{
	for(int i = 0 ; i < p_kraje.size();i++)
	{
        p_table->insert(p_kraje.access(i)->data_.getTitle() ,p_kraje.access(i)->data_);
	}
}

void Vypis_podla_stringu(string str, ds::adt::HashTable<string, UzemnyCelok>* p_table)
{
    vector<UzemnyCelok> duplicity;
    UzemnyCelok* uzeemna_jednotka = nullptr;
    for (auto iterator = p_table->begin(); iterator != p_table->end(); ++iterator)
    {
	    if ((*iterator).key_ == "Višòové")
	    {
            cout << (*iterator).data_.getCode() << (*iterator).data_.getTitle() << endl;
	    }
    }
}



int main()
{
    initHeapMonitor();
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);

    string path_kraje = "kraje.csv";
	string path_okresy = "okresy.csv";
    string path_obce = "obce.csv";

    string delimiter = ";";

	ifstream kraje;
    ifstream okresy;
    ifstream obce;

    auto loadKraje = NacitajUzemnyCelok(path_kraje);
    auto loadOkresy =NacitajUzemnyCelok(path_okresy);
    auto loadObce = NacitajUzemnyCelok(path_obce);

    auto m_hierarchzy = NaplnHierarchiu(loadKraje, loadOkresy, loadObce);

    m_hierarchzy.processLevelOrder(m_hierarchzy.accessRoot(), [&](ds::amt::MultiWayExplicitHierarchyBlock<UzemnyCelok> * block)
        {
            cout << block->data_.getTitle()<<endl;
        });

    //PrechadzajHierarchiu(&m_hierarchzy);

    auto hashFunction = [](const std::string& key)
    {
        size_t hash = 0;
        for (char ch : key) {
            hash = hash * 37 + ch;
        }
        return hash;
    };
    ds::adt::HashTable<string, UzemnyCelok> table(hashFunction,loadObce.size());

    NacitajDoTabulky(&table, loadObce);
    
    cout << "htovo" << endl;

    Vypis_podla_stringu("Prievidza", &table);

    cout << "htovo" << endl;

    //pocet_samohlasok_string();

}




















//int currentKrajIterator = 0;
//int currentOkresIteratot = 0;
//int currentObecIterator = 0;
//int insertOkresIterator = 0;
//int insertObecIterator = 0;
//ds::amt::MultiWayExplicitHierarchy<UzemnyCelok> hierarchy;

//hierarchy.emplaceRoot().data_ = UzemnyCelok(1, "", "Slovensko", "", "", "", KRAJINA);


//auto& root = *hierarchy.accessRoot();

//for (int krajeIterator = 0; krajeIterator < kraje.size(); krajeIterator++)
//{
//    auto& kraj = hierarchy.emplaceSon(root, krajeIterator);
//    kraj.data_ = kraje.access(krajeIterator)->data_;

//    for (int okresyIterator = 0; okresyIterator < okresy.size(); okresyIterator++)
//    {
//        if (kraj.data_.getCode() == okresy.access(okresyIterator)->data_.getNote().substr(0, 1))
//        {
//            auto& okres = hierarchy.emplaceSon(kraj, insertOkresIterator);
//            okres.data_ = okresy.access(okresyIterator)->data_;

//            for (int obceIterator = 0; obceIterator < obce.size(); obceIterator++)
//            {
//                if (okres.data_.getCode() == obce.access(obceIterator)->data_.getCode().substr(0, 6))
//                {
//                    auto& obec = hierarchy.emplaceSon(okres, insertObecIterator);
//                    obec.data_ = obce.access(obceIterator)->data_;
//                }
//                else insertObecIterator = 0;
//            }
//        }
//        else insertOkresIterator = 0;
//    }
//}
//return hierarchy;