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
HashTable<EngWord>* func1(void);
HashTable<EngWord>* func2(int count,const EngWord* arrayPtr)const;
void func3(HashTable<EngWord>* origin);
void func4(HashTable<EngWord>* origin);
void func5(HashTable<EngWord>* origin);

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
    ptr = func1();
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
                func3(ptr);
                break;
            case'2':
                func4(ptr);
                break;
            case'3':
                func5(ptr);
                break;
            case'4':
                cout<<"Exiting"<<endl;
                break;
        }
    }while(menu[0]=='4');
    return 0;
}


HashTable<EngWord>* func1(void)
{
    //o Orden läses från fil
    string tmp;
    int count=0;
    EngWord *ptrArray;
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

        ptrArray = new EngWord[count];
        myfile.clear();
        myfile.seekg(0, ios::beg);
        while ( getline (myfile,tmp) )
        {
            int i=0;
            ptrArray[i] = EngWord(tmp);
            i++;
        }

        myfile.close();
    }
    else
        cout << "Unable to open file";
    return func2(count, ptrArray);
}
HashTable<EngWord>* func2(int count,EngWord* arrayPtr)const
{
    HashTable<EngWord> *array;
    HashTable<EngWord> obj(count*2);
    array=&obj;
    for (int i = 0; i < count ; ++i)
    {
        array->insert(EngWord(arrayPtr[i]));
    }
    cout<<"Load factor: "<<array->loadFactor()<<endl;
    return array;
}
void func3(HashTable<EngWord>* origin)
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
            if(-1 == origin->contains(EngWord(word[i])))
            {
                cout<<"word "<< word[i]<<" does not exist in table!"<<endl;
            }
    }
}
void func4(HashTable<EngWord>* origin)
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
void func5(HashTable<EngWord>* origin)
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

