/*
 Description: Program reads in a dictionary and finds 
                misspelled words and offers suggestions using 
                unordered has map
 Input: Text file
 Output: misspelled words and suggestions
*/
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>


using namespace std;
vector<string> replaceLetter(std::string obj)
{
    std::vector<string> result; 
    //get misspelled word and change each letter in it 
    string obj2 = obj;
    //lower case, to compare to dictionary 
    transform(obj2.begin(),obj2.end(),obj2.begin(),::tolower);
   
    int start = 97; //ascii a 
    int end = 122; //ascii z 
    char insert; 
    //go through the lenght of the object 
    for(int i =0; i<=obj.length()-1; ++i)
    {
        start = 97; //reset to a, after one round on one index
        //start with a and go to z 
        for(;start <= end; ++start) 
        {
                //erase said index and insert letter into index
                obj = obj2; 
                obj.erase(obj.begin()+i);
                insert = start;
                obj.insert(obj.begin()+i, 1, insert);
                result.push_back(obj); 
        }
    }
    //start adding letter in between each letter 
    for(auto i = obj.begin(); i<=obj.end(); ++i){
        obj=obj2;
        start =97;
        for(;start <= end; ++start) 
        {
                //erase said index and insert letter into index and push to vecotr
                obj.insert(i,start);
                result.push_back(obj); 
                obj.erase(i);
        }
    }
    //return said vector 
    return result; 
}
bool contains(std::string str1, std::unordered_map<std::string, bool>& dictionary)
{
    if(dictionary.find(str1) == dictionary.end())
        return false; 

    return true; 
}
//contains the suggested words and prints them
vector<string> suggestWords(vector<string> obj, unordered_map<std::string, bool>& dictionary)
{
    
       //holds the valid words 
       vector<string> validStrings;
        //look thoright using an itterator to push back all the valid words
        
        for (auto it=obj.begin(); it<= obj.end();it++)
            if(contains(*it, dictionary)) 
            {
                validStrings.push_back(*it); 
            }
            
        //sort those vailid words into alpa order 
        sort(validStrings.begin(), validStrings.end());

        //if no match then, not in the dictionary
        if(validStrings.empty()){
            cout << "No suggestions\n";
        }
        else
        //found some words to suggest, ittorate through and print them 
        cout <<"Suggested words"<<endl;
        for (auto it=validStrings.begin(); it< validStrings.end();it++){
            //deallocate and assign to new string to print to convert to upper  
            string it2=*it;
            for(int i=0; i<=it2.length()-1; i++){
                it2[i]=toupper(it2[i]);
            }
            
            cout<< it2 << endl;
        }
        cout<< endl;

    return validStrings;    
}
void readDictionary(unordered_map<string, bool>& dictionary, ifstream& inFile)
{
    
    string sourceFile; 
    //read dictinoary 
    inFile.open(("usa.txt")); 
    //load words into has map 
    while(!inFile.eof())
    {
        inFile>>sourceFile; 
        dictionary.insert({sourceFile, true}); 
    }
    inFile.close(); 
}
void userFile(unordered_map<string, bool>& dictionary, vector<string>& errors ,ifstream& inFile)
{
    string fileName;
    string word; 
     //ask user for txt file 
    cout<<"Enter filename: "; 
    cin >> fileName; 
    inFile.open(fileName); 
    //make sure it the correct txt file 
    if(!inFile.is_open())
    {  
        cin.clear();  
        cout<<"Enter filename: "; 
        cin >> fileName; 
        inFile.open(fileName);     
    } 
    //ittorate through entry and compare them to the dictionary, change to lower to compare 
    while (!inFile.eof())
    {
        inFile >> word;
        transform(word.begin(),word.end(),word.begin(),::tolower);
        if(dictionary.find(word) == dictionary.end())
        {
            //change to upper and save into vector to find suggest words
            transform(word.begin(),word.end(),word.begin(),::toupper);
            errors.push_back(word); 
        } 
    }
}
//check each error and see if there is a suggested word by modifying each character after
void duplicateHandling(vector<string>& errors)
{
    //run through so there are no dublicates
    for (auto Iti = errors.begin(); Iti < errors.end(); Iti++)
    {
        string work = *Iti;
        for (auto itj = Iti+1; itj<errors.end(); itj++) 
        {
                if (work == *itj)
                {
                    errors.erase(itj);
                }
        }
    }
}
void print(vector<string>& errors, unordered_map<string, bool>& dictionary)
{
    
    duplicateHandling(errors);   
    for(auto& obj : errors)
    {
        cout<<obj<<" is misspelled\n"<<endl; 
        vector<string> valid_words;
        //call replace letter and suggested words, and save into valid_words vector
        valid_words=suggestWords(replaceLetter(obj), dictionary);   
       
    }
}
int main()
{   
    ifstream inFile; 
    std::unordered_map<string, bool> dictionary; 
    string fileName;
    //vector to store misspelled words 
    vector<string> errors; 
    readDictionary(dictionary, inFile);
    userFile(dictionary, errors, inFile);
    print(errors, dictionary); 
    
    return 0; 
}
