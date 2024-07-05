#include"Data_initialize.h"

//����ӳ���ϵ
//���⵽���ߵ�ӳ��
unordered_map<string, vector<string>>article_authors;
//���ߵ������ӳ��
unordered_multimap<string, string>author_article;
//��ݵ������ӳ��
unordered_multimap<string, string>year_article;

//���弯��
//�������߼���
unordered_set<string> authors;
//�洢������ݵļ���
unordered_set<string> years;

//��������ȷ���ܹ�ͬʱ��������ӳ���ϵ
mutex mapMutex;
mutex mapMutex1;

//�ָ�ӳ���ļ����ַ���
int split(string str)
{
    int len = str.length(), i = 0;
    for (; i < len; i++)
    {
        if (str[i] == '@')break;
    }
    return i;
}

//�������߱���ӳ���ϵ
void load_map(string str)
{
    lock_guard<mutex> lock(mapMutex);
    string filename = str + ".txt";
    //fstream inFile(filename, ios::in);
    if (str == "article_authors")
    {
        fstream inFile(filename, ios::in);
        while (!inFile.eof())
        {
            string str, title, author;
            getline(inFile, str);

            int index = split(str);
            if (index)
            {
                title = str.substr(0, index);
                author = str.substr(index + 1);
                auto it = article_authors.find(title);
                if (it == article_authors.end())
                {
                    vector<string>authors;
                    authors.push_back(author);
                    article_authors.emplace(title, authors);
                }
                else
                {
                    it->second.push_back(author);
                }
            }
        }
        inFile.close();
    }
    else if (str == "author_article")
    {
        fstream inFile(filename, ios::in);
        while (!inFile.eof())
        {
            string str, title, author;
            getline(inFile, str);
            int index = split(str);
            if (index)
            {
                author = str.substr(0, index);
                title = str.substr(index + 1);
                author_article.emplace(author, title);
            }
        }    
        inFile.close();
    }
}

//�������������ӳ���ϵ
void load_yearmap()
{
    lock_guard<mutex> lock(mapMutex1);
    string filename = "year_article.txt";
    fstream inFile(filename, ios::in);
    while (!inFile.eof())
    {
        string str, title, year;
        getline(inFile, str);
        if (str[0] != '@' && str.length() > 5)
        {
            year = str.substr(0, 4);
            title = str.substr(5);
            year_article.emplace(year, title);
        }
    }
    inFile.close();
}

//�������߼���
void load_authors()
{
    for (auto it = author_article.begin(); it != author_article.end(); ++it)
    {
        authors.insert(it->first);
    }
}

//������ݼ���
void load_years()
{
    for (auto it = year_article.begin(); it != year_article.end(); ++it)
    {
        years.insert(it->first);
    }
}

//�����ж�
wxString judge_load()
{
    if (article_authors.size() == 0)
        return "ӳ���ļ�δ���أ�";
    else return "";
}