#include <bits/stdc++.h>
using namespace std;

//create a trie of 26 childs

struct TrieNode{
    TrieNode* child[26];
    bool isend;
    TrieNode()
    {
        for(int i=0;i<26;i++)
        {
            this->child[i]=NULL;

        }
        isend=false;
    }
};

//insert the words in trie

void insertword(TrieNode *root,string word)
{
    int wordSize = word.length();

    for(int i=0;i<wordSize;i++)
    {
        if(root->child[word[i]-'a']==NULL)
        {
            root->child[word[i]-'a']= new TrieNode();

        }
        root=root->child[word[i]-'a'];
    }
    root->isend=true;
}

//check if the word present in a trie

bool checkword(TrieNode *root,string word)
{
    int wordSize = word.length();

    for(int i=0;i<wordSize;i++)
    {
        if(root->child[word[i]-'a']==NULL)
        {
            return false;

        }
        root=root->child[word[i]-'a'];
    }

    return root->isend;
}

//suggestion for wrong word when single character is missing

void suggestion1(TrieNode *root,string input)
{
    string characters ="abcdefghijklmnopqrstuvwxyz";

    for(int i=0;i<26;i++)
    {
       int size=input.length();
       for(int j=0;j<size;j++)
       {
           string word = input.substr(0,j) + characters[i] + input.substr(j);
            if(checkword(root,word))
           {
            cout<<word<<"\n";
           }
       }

    }

}

//suggestion for wrong word when single character gets extra

void suggestion2(TrieNode *root,string input)
{
       int size=input.length();
       for(int j=0;j<size;j++)
       {
           string word = input.substr(0,j) + input.substr(j+1);
            if(checkword(root,word))
           {
            cout<<word<<"\n";
           }
       }



}

//suggestion for wrong word when single character swap


void suggestion3(TrieNode *root,string input)
{
    string characters ="abcdefghijklmnopqrstuvwxyz";

    for(int i=0;i<26;i++)
    {
       int size=input.length();
       for(int j=0;j<size;j++)
       {
            char ch=input[j];
            input[j]=characters[i];
            if(checkword(root,input))
           {
             cout<<input<<"\n";
           }
           input[j]=ch;
       }

    }

}

//suggestion for wrong word if 1 character gets extra and 1 character get miss

void suggestion4(TrieNode *root,string input)
{
       int size=input.length();
       for(int j=0;j<size;j++)
       {
           string word = input.substr(0,j) + input.substr(j+1);
           suggestion1(root,word);
       }



}

//main function

int main()
{
    TrieNode *root= new TrieNode();
    string input;
    cout<<"Enter the spelling:";
    cin>>input;
    fstream file;
    file.open("file.txt",ios::in);
    if (file.is_open()){
      string word;
      while(getline(file, word)){
        insertword(root,word);
      }
      file.close();

      if(checkword(root,input))
      {
          cout<<"Given input is a valid word\n";
      }
      else{

         cout<<"Given input is not a valid word\n";
         cout<<"here is some suggestion for corrects word\n";
         suggestion1(root,input);  //call for 1st suggestion
         suggestion2(root,input);  //call for 2nd suggestion
         suggestion3(root,input);  //call for 3rd suggestion
         suggestion4(root,input);  //call for 4th suggestion


      }


      }
    cout<<"Thank You..!";
    return 0;
}
