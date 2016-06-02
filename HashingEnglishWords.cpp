/*
 * Överst i filen skriver du en kommentar i vilken du motiverar storleken på hashtabellen, dvs
   antalet ingångar (entries) samt hur du definierat hashfunktionen för EngWord. Vidare ska du
   redogöra för det intervall hashfunktionen (genom definitionen av operatorn ()) för EngWord
   omfattar.

   Jag motiverar hashtabellens storlek med att den bör vara antal element faktor två.
   HashTabellen blir ju sämre med hänsyn på komplexitet ju fylld den blir. Jag vill ha tabellen högst 60% fylld.

   Min HashFunktion tar det första ascii värdet i strängen multiplicerat med det andra om det nu finns annars blir det faktor två på den första.

   som lägst ger hashningen ett tiotal * 2. Som max ett hundratal se ASCII tabellen * sig själv. Om vi stödjer UTF8 blir  det ännu större.

   sen kör ju myhash() modolus TableSize så vi hamnar från 0 till 1999.

 */
//
// Created by Roderik Bauhn on 2016-04-28.
//

/* Komplettering Tidsgräns: den 25 maj 2016 13:00
 * FIX
 * Codes            name
 * ---------------------------------------------------------------------------------------------------------------------
 * 0xA0              Ordlista – programmet som använder Hashtabell: kraschar vid körning
 *
 * 0xA1              Hashfunktionen och hashtabellens storlek: hashfunktionen ger dålig spridning och därmed blir det många kollisioner, tabellstorleken är bra men bör vara ett primtal
 *
   Komplettering Tidsgräns: den 3 juni 2016 08:00
 * FIX
 * Codes  1/0 checked?        name
 * ---------------------------------------------------------------------------------------------------------------------
 * 1)                      func2(..) : har ska du genom anväöndande av dynamisk minnesallokering skapa HAshTabellen eftersom den lokalt skapade "avallokeras" när kösningen lämnar funktionen


   2)                     räknaren count blir 1 för mycket när antalet ord som läses räknas, vilket innebär att itertaione i func2 utförs en gång för mycket


   3)                    meny visas inte efter det att menyval hanterats


   4)       1           namngivningen med func2 etc är inte ok, det ska vara namn som anger vad "det handlar om"

   extra stuff..
========================================================================================================================
   case 1:
========================================================================================================================
   WordList using hash table.
    Chose one.
    1.Enter a sentence. Words unrecogniced gets printed to screen.
    2.Add word.
    3.Remove word.
    4.Exit.
    Choice: 2
    Want to enter an english word?(y/n): y

    Write one word followed by enter/newline key: cow
    word: cow
    word: cow got hash:235623
    ==5978==
    ==5978== Process terminating with default action of signal 8 (SIGFPE)
    ==5978==  Integer divide by zero at address 0x802DD0E17
    ==5978==    at 0x404471: HashTable<EngWord>::myHash(EngWord const&) const (HashTable.h:40)
    ==5978==    by 0x403D3A: HashTable<EngWord>::insert(EngWord const&) (HashTable.h:115)
    ==5978==    by 0x40341E: addOneEnglishWord2Dictionary(HashTable<EngWord>*) (HashingEnglishWords.cpp:253)
    ==5978==    by 0x4028DE: main (HashingEnglishWords.cpp:119)
    ==5978==
    ==5978== HEAP SUMMARY:
    ==5978==     in use at exit: 72,744 bytes in 4 blocks
    ==5978==   total heap usage: 8 allocs, 4 frees, 75,896 bytes allocated
    ==5978==
    ==5978== LEAK SUMMARY:
    ==5978==    definitely lost: 8 bytes in 1 blocks
    ==5978==    indirectly lost: 0 bytes in 0 blocks
    ==5978==      possibly lost: 0 bytes in 0 blocks
    ==5978==    still reachable: 72,736 bytes in 3 blocks
    ==5978==         suppressed: 0 bytes in 0 blocks
    ==5978== Rerun with --leak-check=full to see details of leaked memory
    ==5978==
    ==5978== For counts of detected and suppressed errors, rerun with: -v
    ==5978== Use --track-origins=yes to see where uninitialised values come from
    ==5978== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
    Flyttalsfel (minnesutskrift skapad)


========================================================================================================================
   case 2:
========================================================================================================================
   WordList using hash table.
    Chose one.
    1.Enter a sentence. Words unrecogniced gets printed to screen.
    2.Add word.
    3.Remove word.
    4.Exit.
    Choice: 3
    Want to enter an english word?(y/n): y

    Write one word followed by enter/newline key: cow
    word: cow
    word: cow got hash:235623
    ==6088==
    ==6088== Process terminating with default action of signal 8 (SIGFPE)
    ==6088==  Integer divide by zero at address 0x802DD0FF7
    ==6088==    at 0x404471: HashTable<EngWord>::myHash(EngWord const&) const (HashTable.h:40)
    ==6088==    by 0x40400A: HashTable<EngWord>::remove(EngWord const&) (HashTable.h:158)
    ==6088==    by 0x4035F0: rmENGwordFromDictionary(HashTable<EngWord>*) (HashingEnglishWords.cpp:273)
    ==6088==    by 0x4028EC: main (HashingEnglishWords.cpp:122)
    ==6088==
    ==6088== HEAP SUMMARY:
    ==6088==     in use at exit: 72,744 bytes in 4 blocks
    ==6088==   total heap usage: 8 allocs, 4 frees, 75,896 bytes allocated
    ==6088==
    ==6088== LEAK SUMMARY:
    ==6088==    definitely lost: 8 bytes in 1 blocks
    ==6088==    indirectly lost: 0 bytes in 0 blocks
    ==6088==      possibly lost: 0 bytes in 0 blocks
    ==6088==    still reachable: 72,736 bytes in 3 blocks
    ==6088==         suppressed: 0 bytes in 0 blocks
    ==6088== Rerun with --leak-check=full to see details of leaked memory
    ==6088==
    ==6088== For counts of detected and suppressed errors, rerun with: -v
    ==6088== Use --track-origins=yes to see where uninitialised values come from
    ==6088== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
    Flyttalsfel (minnesutskrift skapad)


*/

#include <iostream>
#include "EngWord.h"
#include "HashTable.h"
#include <fstream>
#include <sstream>
using namespace std;
/* Detta ska göras här;
 o En funktion(1) vilken läser de engelska orden från fil och skapar/fyller en array med objekt
   av typen EngWord för de ord som lästs. Filens namn är engWords.txt och sökvägen till
   filen ska vara C:/temp/.

 o En funktion(2) som placerar alla EngWord-objekt i en hashtabell. Funktionen ska dessutom
   presentera belastningsgrad (load factor) som en utskrift.

 o En funktion(3) i vilken användaren matar in en engelsk mening vilken avslutas med en
   punkt (.) och får besked om vilka ord som inte ingick i ordlistan. De ord som inte ingick i
   ordlistan ska presenteras som en utskrift.

  o En funktion(4) i vilken användaren matar in engelska ord som läggs in i hashtabellen. Om
    ett ord redan finna i tabellen ska detta meddelas och ordet läggs inte in i tabellen.

 o En funktion(5) i vilken användaren matar in engelska ord som ska tas bort från
   hashtabellen. Om ett ord inte finns i hashtabellen meddelas detta.
 * */
HashTable<EngWord>* ReadData(void);
HashTable<EngWord>* addWords2Dictionary(int count, EngWord *arrayPtr);
void englishSentenceAnalysis(HashTable<EngWord> *origin);
void addOneEnglishWord2Dictionary(HashTable<EngWord> *origin);
void rmENGwordFromDictionary(HashTable<EngWord> *origin);

int main(void)
{
    /*
     * ska göras här:
     o Orden läses från fil
     func1();
     o Orden placeras i hashtabellen
     func2();
     o En meny presenteras där användaren kan välja att:
        o mata in en mening för att få besked om vilka av orden i meningen som inte finns i
          ordlistan (hashtabellen)
        o lägg in nya ord
        o ta bort ord
        o avsluta
     */
/*
    EngWord testSub("ape");
    EngWord testSub2("fish");
    bool result = testSub == testSub2; //true(1) if equal false(0) if diff.
    cout <<"ape == donkey: "<<result<<endl;
    result = testSub != testSub2; //True(1) if diff. False(0) if equal.
    cout <<"ape != donkey: "<<result<<endl;
    Hash<EngWord>testSubHash, testSub2Hash;
    cout <<"hash for word: " << testSubHash(testSub)<<endl;
    cout <<"hash for word: " << testSub2Hash(testSub2)<<endl;
    */
    HashTable<EngWord> *ptr;
    string menu;
    ptr = ReadData();
    bool menuFlag=true;
    //3) meny visas inte efter det att menyaval hanterats
    do
    {
        //clean terminal
        //linux
        system("clear");
        //windows
        system("cls");
        cout<<"WordList using hash table.\nChose one.\n1.Enter a sentence. Words unrecogniced gets printed to screen.\n2.Add word.\n3.Remove word.\n4.Exit.\nChoice: ";
        getline(cin, menu);
        switch(menu[0])
        {
            case'1':
                englishSentenceAnalysis(ptr);
                break;
            case'2':
                addOneEnglishWord2Dictionary(ptr);
                break;
            case'3':
                rmENGwordFromDictionary(ptr);
                break;
            case'4':
                cout<<"Exiting"<<endl;
                menuFlag =false;
                break;
        }
    }while(menuFlag);
    delete ptr;
    return 0;
}


HashTable<EngWord>* ReadData(void)
{
    //o Orden läses från fil
    string tmp;
    int count=0;
    int i=0;
    EngWord *ptrArray;
    //I use Linux so.. :-(
    ifstream myfile ("C:\\temp\\engWords.txt");
    if(!myfile.is_open())
    {
        myfile.close();
        myfile.open("/root/IDEstorage/DV1490/labbar/DV1490_lab3_inlamning/engWords.txt");
    }
    if (myfile.is_open())
    {
        while ( getline(myfile,tmp) )
        {
            count++;

        }
        //double the array size

        ptrArray = new EngWord[count];
        myfile.clear();
        myfile.seekg(0, ios::beg); //start att beginning.
        count=0;
        while ( getline(myfile,tmp) )
        {
            //debug
            //cout<<count<<' '<<tmp<<'\n';
            ptrArray[i] = EngWord(tmp);
            i++; count++;
        }

        myfile.close();
    }
    else
        cout << "Unable to open file";

    //HashTable<EngWord>* func2(int count,const EngWord* arrayPtr);
    return addWords2Dictionary(count, ptrArray);
}


//kanske fixad? 1) func2(..) : har ska du genom användande av dynamisk minnesallokering skapa HAshTabellen eftersom den lokalt skapade "avallokeras" när lösningen lämnar funktionen

HashTable<EngWord>* addWords2Dictionary(int count, EngWord *arrayPtr)
{
    HashTable<EngWord> *array;
    array= new HashTable<EngWord>(count*2);

    for (int i = 0; i < count ; ++i)
    {
        array->insert(EngWord(arrayPtr[i]));
    }
    delete[] arrayPtr;
    cout<<"Load factor: "<<array->loadFactor()<<endl;
    return array;
}





void englishSentenceAnalysis(HashTable<EngWord> *origin)
{
    //En funktion(3) i vilken användaren matar in en engelsk mening vilken avslutas med en
    //punkt (.) och får besked om vilka ord som inte ingick i ordlistan. De ord som inte ingick i
    //ordlistan ska presenteras som en utskrift.
    string *word = new string[1024];
    string sentence;
    cout<<"Enter an english sentence and words in hashtable gets printed. End sentence with '.' ";
    getline(cin,sentence );
    stringstream ss;
    int number =0;
    int wordCount=0;

    do
    {
        if(sentence[number] != ' ')
        {
            ss << sentence[number];
            number++;

        }
        else
        {
            word[wordCount] = ss.str();
            ss.clear();

            ss.str(string(""));
            wordCount++;
            number++;
        }
    }while(sentence[number] != '.');

    word[wordCount] = ss.str();
    wordCount++;
    for (int i = 0; i < wordCount ; ++i)
    {
            if(-1 == origin->contains(EngWord(word[i])))
            {
                cout<<"word "<< word[i]<<" does not exist in table!"<<endl;
            }
    }
}
void addOneEnglishWord2Dictionary(HashTable<EngWord> *origin)
{
    //En funktion(4) i vilken användaren matar in engelska ord som läggs in i hashtabellen. Om
    //ett ord redan finns i tabellen ska detta meddelas och ordet läggs inte in i tabellen.
    string choice, word;
    do
    {
        cout << "Want to enter an english word?(y/n): ";
        getline(cin,choice );
        if(tolower(choice[0])=='y')
        {
            cout << "\nWrite one word followed by enter/newline key: ";
            getline(cin, word);
            if(origin->insert(word) == false)
            {
                cout << "\n sorry word already exist\n";
            }
        }
    }while(tolower(choice[0]) != 'n');
}
void rmENGwordFromDictionary(HashTable<EngWord> *origin)
{
    //En funktion(5) i vilken användaren matar in engelska ord som ska tas bort från
    //hashtabellen. Om ett ord inte finns i hashtabellen meddelas detta.
    string choice, word2rm;
    do
    {
        cout << "Want to enter an english word?(y/n): ";
        getline(cin,choice );
        if(tolower(choice[0])=='y')
        {
            cout << "\nWrite one word followed by enter/newline key: ";
            getline(cin, word2rm);
            if(origin->remove(EngWord(word2rm)) == false)
            {
                cout << "\n sorry word doese not exist henche cannot be removed\n";
            }
        }
    }while(tolower(choice[0]) != 'n');
}

