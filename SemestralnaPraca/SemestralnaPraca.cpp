
#include "libds/amt/explicit_sequence.h"
#include "libds/amt/explicit_hierarchy.h"
#include "libds/amt/implicit_hierarchy.h"
#include <Windows.h>
#include "UzemnyCelok.h"

#include <iostream>
#include <fstream>
#include <string>




using namespace std;
using namespace ds;

//vector<TableItem> tabulkaKrajov;
//vector<TableItem> tabulkaOkresov;
//vector<TableItem> tabulkaObci;


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
        if (p_path.find("kraje"))
            type = KRAJ;
        else if (p_path.find("okresy"))
            type = OKRES;
        else
            type = OBEC;

    	UzemnyCelok uzemny_celok = UzemnyCelok(sortNumber,obecString.at(1),obecString.at(2),obecString.at(3),obecString.at(4),obecString.at(5),type);
    	UzemneCelky.push_back(uzemny_celok);
    }
	return UzemneCelky;
}




//
//void ulozUzemneCelkyDoHierarchie(HierarchiMultiWay *hierarchi , vector<UzemnyCelok> loadKraj , vector<UzemnyCelok> loadOkres, vector<UzemnyCelok> loadObce)
//{
//    
//    cout << "==============================" << endl;
//
//    for (int i = 0; i < loadKraj.size(); i++)
//    {
//        PrvokHierarchie child = PrvokHierarchie();
//        child.setData(loadKraj.at(i));
//        child.addParent(hierarchi->getRoot());
//        hierarchi->getRoot()->addChild(child);
//
//        TableItem ti(i, child);
//        tabulkaKrajov.push_back(ti);
//    }
//
//    for (int i = 0; i < loadKraj.size(); i++)
//    {
//        for (int j = 0; j < loadOkres.size(); j++)
//        {
//            string kkt = hierarchi->getRoot()->getChild()->at(i).getData().getNote().substr(5, 5);
//            string kkt1 = loadOkres.at(j).getCode().substr(0, 5);
//            if (kkt == kkt1)
//            {
//                PrvokHierarchie child = PrvokHierarchie();
//                child.setData(loadOkres.at(j));
//                child.addParent(&hierarchi->getRoot()->getChild()->at(i));
//                hierarchi->getRoot()->getChild()->at(i).addChild(child);
//
//                TableItem ti(i, child);
//                tabulkaOkresov.push_back(ti);
//            }
//        }
//    }
//
//    PrvokHierarchie* root = hierarchi->getRoot();
//    vector<PrvokHierarchie>* kraje = root->getChild();
//    for (int i = 0; i < kraje->size(); i++)
//	{
//        vector<PrvokHierarchie>* okresy = kraje->at(i).getChild();
//		for (int j = 0; j < okresy->size(); j++)
//		{
//            for (int k = 0; k < loadObce.size(); k++)
//            {
//                PrvokHierarchie child = PrvokHierarchie();
//                string kkt2 = hierarchi->getRoot()->getChild()->at(i).getChild()->at(j).getData().getCode();
//                string kkt3 = loadObce.at(k).getCode().substr(0, 6);
//                if (kkt2 == kkt3)
//                {
//                    child.setData(loadObce.at(k));
//                    child.addParent(&hierarchi->getRoot()->getChild()->at(i));
//                    hierarchi->getRoot()->getChild()->at(i).getChild()->at(j).addChild(child);
//
//                    TableItem ti(i, child);
//                    tabulkaObci.push_back(ti);
//                }
//            }
//		}
//	}
//}
//
//void VypisUzemneCelky(vector<PrvokHierarchie> p_uzemneCelky)
//{
//    for (int i = 0 ; i < p_uzemneCelky.size() ; i++)
//    {
//        cout << i << " :" << p_uzemneCelky.at(i).getData().getTitle() << endl;
//    }
//}


void NaplnHierarchiu(ds::amt::MultiWayExplicitHierarchy<UzemnyCelok> *p_m_hierar, vector<UzemnyCelok> p_kraje, vector<UzemnyCelok> p_okresy, vector<UzemnyCelok> p_obce)
{
    cout << "==============================" << endl;

    for (int i = 0 ; i < p_kraje.size() ; i++)
    {
        p_m_hierar->emplaceSon(*p_m_hierar->accessRoot(), i).data_ = p_kraje.at(i);
        for (int j = 0 ; j < p_okresy.size();j++)
        {
            int index_ukladania_hierarchie_okresu = 0;
            //cout << p_m_hierar->accessSon(*p_m_hierar->accessRoot(), i)->data_.getTitle() << endl;
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

//void ulozUzemneCelkyDoHierarchie(HierarchiMultiWay *hierarchi , vector<UzemnyCelok> loadKraj , vector<UzemnyCelok> loadOkres, vector<UzemnyCelok> loadObce)
//{
//    
//    cout << "==============================" << endl;
//
//    for (int i = 0; i < loadKraj.size(); i++)
//    {
//        PrvokHierarchie child = PrvokHierarchie();
//        child.setData(loadKraj.at(i));
//        child.addParent(hierarchi->getRoot());
//        hierarchi->getRoot()->addChild(child);
//
//        TableItem ti(i, child);
//        tabulkaKrajov.push_back(ti);
//    }
//
//    for (int i = 0; i < loadKraj.size(); i++)
//    {
//        for (int j = 0; j < loadOkres.size(); j++)
//        {
//            string kkt = hierarchi->getRoot()->getChild()->at(i).getData().getNote().substr(5, 5);
//            string kkt1 = loadOkres.at(j).getCode().substr(0, 5);
//            if (kkt == kkt1)
//            {
//                PrvokHierarchie child = PrvokHierarchie();
//                child.setData(loadOkres.at(j));
//                child.addParent(&hierarchi->getRoot()->getChild()->at(i));
//                hierarchi->getRoot()->getChild()->at(i).addChild(child);
//
//                TableItem ti(i, child);
//                tabulkaOkresov.push_back(ti);
//            }
//        }
//    }
//
//    PrvokHierarchie* root = hierarchi->getRoot();
//    vector<PrvokHierarchie>* kraje = root->getChild();
//    for (int i = 0; i < kraje->size(); i++)
//	{
//        vector<PrvokHierarchie>* okresy = kraje->at(i).getChild();
//		for (int j = 0; j < okresy->size(); j++)
//		{
//            for (int k = 0; k < loadObce.size(); k++)
//            {
//                PrvokHierarchie child = PrvokHierarchie();
//                string kkt2 = hierarchi->getRoot()->getChild()->at(i).getChild()->at(j).getData().getCode();
//                string kkt3 = loadObce.at(k).getCode().substr(0, 6);
//                if (kkt2 == kkt3)
//                {
//                    child.setData(loadObce.at(k));
//                    child.addParent(&hierarchi->getRoot()->getChild()->at(i));
//                    hierarchi->getRoot()->getChild()->at(i).getChild()->at(j).addChild(child);
//
//                    TableItem ti(i, child);
//                    tabulkaObci.push_back(ti);
//                }
//            }
//		}
//	}
//}

int main()
{
    initHeapMonitor();
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);
    
    ds::amt::MultiWayExplicitHierarchy<UzemnyCelok> m_hierarchzy;

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
    //UzemnyCelok kraj = UzemnyCelok(0, "00", "Kraj", "Kraj", "Kraj", "svk", KRAJINA);

    m_hierarchzy.emplaceRoot().data_ = main_root;

    NaplnHierarchiu(&m_hierarchzy, loadKraje, loadOkresy, loadObce);
    
    cout << "==============================" << endl;

    m_hierarchzy.processLevelOrder(m_hierarchzy.accessRoot(), [&](ds::amt::MultiWayExplicitHierarchyBlock<UzemnyCelok>* block)
        {
            cout<< block->data_.getTitle()<<endl;
        });


 //   UzemnyCelok krajina = UzemnyCelok(0, "Slovensko", "Slovensko", "Slovensko", "Slovensko", "Slovensko", 0, KRAJINA);
 //   PrvokHierarchie krajinaRoot = PrvokHierarchie();
 //   krajinaRoot.setData(krajina);

	//UzemnyCelok krajina1 = UzemnyCelok(0, "Slovensko1", "Slovensko1", "Slovensko1", "Slovensko", "Slovensko", 0, KRAJ);
 //   PrvokHierarchie krajinaRoot1 = PrvokHierarchie();
 //   krajinaRoot1.setData(krajina1);

 //   

 //   UzemnyCelok krajina2 = UzemnyCelok(0, "Slovensko2", "Slovensko2", "Slovensko", "Slovensko", "Slovensko", 0, KRAJ);
 //   PrvokHierarchie krajinaRoot2 = PrvokHierarchie();
 //   krajinaRoot2.setData(krajina2);
 //   UzemnyCelok krajina3 = UzemnyCelok(0, "Slovenska Republika", "Obec3", "Slovensko", "Slovensko", "Slovensko", 0, OKRES);
 //   PrvokHierarchie krajinaRoot3 = PrvokHierarchie();
 //   krajinaRoot.setData(krajina3);

	//HierarchiMultiWay hierarchi = HierarchiMultiWay(&krajinaRoot);
	//
 //   ulozUzemneCelkyDoHierarchie(&hierarchi, loadKraje, loadOkresy, loadObce);
 //   PrvokHierarchie* current;
 //   current = hierarchi.getRoot();
 //   VypisUzemneCelky(*current->getChild());  

 //   while (true)
 //   {
 //       int x;
 //       cin >> x;
 //       if (x >= 0)
 //       {
 //           current = &current->getChild()->at(x);

 //       } else
 //       {
 //           *current = current->getParetn();
 //       }

 //       vector<PrvokHierarchie>* currentVector = current->getChild();
 //       cout << "Napis cislo uzemneho celku ktory chces vypisat." << endl;
 //       VypisUzemneCelky(*currentVector);

 //       cin.get();
 //   }
    //_CrtDumpMemoryLeaks();
}

















//for (int i = 0; i < loadKraj.size(); i++)
//{
//    PrvokHierarchie child = PrvokHierarchie();
//    child.setData(loadKraj.at(i));
//    child.addParent(*hierarchi->getRoot());
//    hierarchi->getRoot()->addChild(child);
//
//    for (int j = 0; j < loadOkres.size(); j++)
//    {
//        string kkt = hierarchi->getRoot()->getChild()->at(i).getData().getNote().substr(5, 5);
//        string kkt1 = loadOkres.at(j).getCode().substr(0, 5);
//        if (kkt == kkt1)
//        {
//            child.setData(loadOkres.at(j));
//            child.addParent(hierarchi->getRoot()->getChild()->at(i));
//            hierarchi->getRoot()->getChild()->at(i).addChild(child);
//
//            for (int k = 0; k < loadObce.size(); k++)
//            {
//                cout << "kraj:" << hierarchi->getRoot()->getChild()->at(i).getData().getTitle() << endl;
//                cout << "okres:" << hierarchi->getRoot()->getChild()->at(i).getChild()->at(j).getData().getTitle() << endl;
//                cout << "Obce" << loadObce.at(k).getTitle() << endl;
//                string kkt2 = hierarchi->getRoot()->getChild()->at(i).getChild()->at(j).getData().getNote().substr(0, 3);
//                string kkt3 = loadObce.at(k).getCode().substr(3, 3);
//                if (kkt2 == kkt3)
//                {
//                    child.setData(loadObce.at(k));
//                    child.addParent(hierarchi->getRoot()->getChild()->at(i).getChild()->at(j));
//                    hierarchi->getRoot()->getChild()->at(i).getChild()->at(j).addChild(child);
//                }
//            }
//        }
//    }
//}