//
// Created by root on 2016-04-28.
//
#include "HashTable.h"
#include "EngWord.h"
#include <iostream>
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
void func1(void);
HashTable<EngWord>& func2(int count,const EngWord* arrayPtr)const;
void func3(HashTable<EngWord>& origin);
void func4(void);
void func5(void);

int main(void)
{
    /*
     * ska göras här:
     o Orden läses från fil
     func1();
     o Orden placeras i hashtabellen
     func2();
     o   En meny presenteras där användaren kan välja att
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
    string insert="myWorld";
    EngWord mao(insert);
    HashTable<EngWord> testZone(10);
    testZone.insert(mao);
    cout <<"at Index nr: "<<testZone.contains(mao)<<endl;
    return 0;
}


void func1(void)
{
    //o Orden läses från fil
    string tmp;
    int count=0;
    //for Windows users   I use Linux so... a little bit to test right now. :-(
    //ifstream myfile ("C:\\temp\\engWords.txt");
    ifstream myfile ("./engWords.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,tmp) )
        {
            count++;
        }
        //double the array size

        EngWord *ptrArray = new EngWord[count];
        myfile.clear();
        myfile.seekg(0, ios::beg);
        while ( getline (myfile,tmp) )
        {
            int i=0;
            ptrArray[i] = EngWord(tmp);
            i++;
        }
        func2(count, ptrArray);
        myfile.close();
    }

    else cout << "Unable to open file";
}
HashTable<EngWord>& func2(int count,EngWord* arrayPtr)const
{
    HashTable<EngWord> array(count*2);
    for (int i = 0; i < count ; ++i)
    {
        array.insert(EngWord(arrayPtr[i]));
    }
    cout<<"Load factor: "<<array.loadFactor()<<endl;
    return array;
}
void func3(HashTable<EngWord>& origin)
{
    //En funktion(3) i vilken användaren matar in en engelsk mening vilken avslutas med en
    //punkt (.) och får besked om vilka ord som inte ingick i ordlistan. De ord som inte ingick i
    //ordlistan ska presenteras som en utskrift.
    string *word = new string[1024];
    string sentence;
    cout<<"Enter an english sentence and words in hashtable gets printed. End sentence with.";
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
            if(-1 == origin.contains(EngWord(word[i])))
            {
                cout<<"word "<< word[i]<<" does not exist in table!"<<endl;
            }
    }
}
void func4(void)
{
    //En funktion(4) i vilken användaren matar in engelska ord som läggs in i hashtabellen. Om
    //ett ord redan finna i tabellen ska detta meddelas och ordet läggs inte in i tabellen.
}
void func5(void){}
