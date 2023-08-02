#include <bits/stdc++.h>
#include <cstring>
#include <iostream>
using namespace std;
struct trie
{
    struct trie *child[26];
    bool endOfWord;
    string description;
};
struct trie *getNode(void)
{
    struct trie *temp = (struct trie *)malloc(sizeof(struct trie));
    temp->endOfWord = false;
    for (int i = 0; i < 26; i++)
        temp->child[i] = NULL;
    return temp;
}
void insert(struct trie *root, string str, string s)
{
    struct trie *temp = root;
    for (int i = 0; i < str.length(); i++)
    {
        int index = (int)(str[i]) - (int)('a');
        if (!temp->child[index])
        {
            temp->child[index] = getNode();
        }
        temp = temp->child[index];
    }
    temp->endOfWord = true;
    temp->description = s;
}
bool lastnode(struct trie *root)
{
    for (int i = 0; i < 26; i++)
        if (root->child[i])
            return 0;
    return 1;
}
void suggest(struct trie *root, string str)
{
    if (root->endOfWord)
        cout << str << "\t\t\t" << root->description << endl;
    for (int i = 0; i < 26; i++)
    {
        if (root->child[i])
        {
            char ch = 'a' + i;
            // root = root->child[i];
            suggest(root->child[i], str + ch);
        }
    }
}
int print(struct trie *root, const string str)
{
    struct trie *temp = root;
    for (int i = 0; i < str.length(); i++)
    {
        int index = int(str[i]) - (int)'a'; //(int)(str[k]) - (int)'a';
        if (!temp->child[index])
        {
            return 0;
        }
        temp = temp->child[index];
    }
    if (lastnode(temp))
    {
        cout << str << "\t\t\t" << temp->description << endl;
        return -1;
    }
    suggest(temp, str);
    return 1;
}
bool isLeafNode(struct trie *root)
{
    return root->endOfWord != false;
}
// function to display the content of Trie
void display(struct trie *root, char str[], int level)
{
    if (isLeafNode(root))
    {
        str[level] = '\0';
        cout << str << "\t\t\t" << root->description << endl;
    }
    for (int i = 0; i < 26; i++)
    {
        if (root->child[i])
        {
            str[level] = i + 'a';
            display(root->child[i], str, level + 1);
        }
    }
}
// Function to count number of words
int count(struct trie *root)
{
    int result = 0;
    if (root->endOfWord)
        result++;
    for (int i = 0; i < 26; i++)
        if (root->child[i])
            result += count(root->child[i]);
    return result;
}
int search(struct trie *root, string s)
{
    if (root == NULL) // if Trie is empty
    {
        printf("Trie is empty\n");
        return 0;
    }
    else
    {
        struct trie *temp = root;
        for (int j = 0; j < s.length(); j++)
        {
            int index = tolower(s[j]) - 'a';
            if (!temp->child[index])
            {
                return 0;
            }
            temp = temp->child[index];
        }
        return temp->endOfWord;
    }
}
int main()
{
    int choice;
    struct trie *head = getNode();
start:
    printf("\n**************MENU**************\n");
    printf("1-->INSERT WORDS TO DICTIONARY\n");
    printf("2-->SEARCH A WORD OR PREFIX OF A WORD\n");
    printf("3-->DISPLAY ALL THE WORDS OF YOUR DICTIONARY\n");
    printf("4-->CHECK WHETHER YOU CAN FORM A SENTENCE USING THE AVAILABLE WORDS IN THE DICTIONARY\n");
    printf("5-->EXIT\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
    {
        string word, description;
        cout << "Enter the word to add" << endl;
        cin >> word;
        cout << "Enter the meaning" << endl;
        fflush(stdin);
        getline(cin,description);
        insert(head, word, description);
        break;
    }
    case 2:
    {
        string str, strmeaning;
        cout << "Enter the word to be searched: " << endl;
        cin >> str;
        cout << "WORD\t\t\tDESCRIPTION" << endl; 
        int x = print(head, str);
        if (x == -1)
        {
            cout << "No other words with this prefix found" << endl;
        }
        else if (x == 0)
            cout << "No words with this prefix found" << endl;
        break;
    }
    case 3:
    {
        int level = 0;
        char str[100];
        // Displaying content of Trie
        cout << "Total number of words in the dictionary are"
             << " " << count(head) << endl;
        cout << "WORD\t\t\tDESCRIPTION" << endl;  
        display(head, str, level);
        break;
    }
    case 4:
    {
        string sentence;
        cout << "Enter the sentence : " << endl;
        fflush(stdin);
        getline(cin, sentence);
        istringstream ss(sentence);
        string word;
        int x = 1;
        while (ss >> word)
        {
            x = search(head, word);
            if (x == 0)
            {
                cout << "invalid sentence" << endl;
                break;
            }
        }
        if (x == 1)
            cout << "valid sentence" << endl;
        break;
    }
    case 5:
        return 0;
    default:
        printf("Invalid choice\n");
        break;
    }
    goto start;
}
