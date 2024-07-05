#include"search.h"

//�������߲���������Ϣ
wxString find_by_author(wxString authorName)
{
    wxString result;
    // ���ò��Һ���
    auto range = author_article.equal_range(authorName.ToStdString());
    if (range.first != author_article.end())
    {
        // �����ƪ���µ����
        result = "���� " + authorName + " ��Ӧ�������У�\n";
        for (auto it = range.first; it != range.second; ++it)
        {
            result += wxString::Format("- %s\n", it->second+"\n");
        }
    }
    else
    {
        result = wxString::Format("δ�ҵ����� %s��", authorName);
    }
    return result;
}

//�����ض�������Ϣ�����
wxString find_specific_article(wxString articleName)
{
    wxString wxresult;
    string str=articleName.ToStdString();
    string s = "<title>" + str + "</title>";
    ifstream file;
    file.open("D:/GUI/dblp.xml", ios::in);
    string content;
    string unknown_str;
    xml element;
    bool result = false;
    while (!file.eof())
    {
        getline(file, unknown_str);
        xml_information xml_type = judge_xml_information(unknown_str);

        if (xml_type == article_mdate)
        {
            xml new_element;
            //��ȡ��ǩ��Ϣ
            xml_abstract(unknown_str, article_mdate, &new_element);
            int begin = get_article_mdate(unknown_str);
            new_element.article_mdate = new_element.xml_label.substr(begin, 10);
            new_element.key = get_key(new_element.xml_label.substr(begin));

            getline(file, unknown_str);

            //��ȡ������Ϣ
            while (unknown_str.find("</article>") == string::npos)
            {
                xml_type = judge_xml_information(unknown_str);
                xml_abstract(unknown_str, xml_type, &new_element);
                if (xml_type == title)
                {
                    if (new_element.title != str)break;
                    else result = true;
                }
                getline(file, unknown_str);
            }
            if (result == true)
            {
                element = new_element;
                break;
            }
        }
    }
    if (result == true)
    {
        wxresult = "���� " + articleName + " ��ȫ����Ϣ����: \n";
        wxresult+=wxString::Format("-article mdate : %s\n",element.article_mdate);
        wxresult+=wxString::Format("-key : %s\n",element.key);
        for (int i = 0; i < element.authors.size(); i++)
        {
            wxresult+=wxString::Format("-author : %s\n",element.authors[i]);
        }
        wxresult+=wxString::Format("-title : %s\n",element.title);
        wxresult+=wxString::Format("-journal : %s\n",element.journal);
        wxresult+=wxString::Format("-volume : %s\n",element.volume);
        wxresult+=wxString::Format("-month : %s\n",element.month);
        wxresult+=wxString::Format("-year : %s\n",element.year);
        wxresult+=wxString::Format("-cdrom : %s\n",element.cdrom);
        wxresult+=wxString::Format("-ee : %s\n",element.ee);
    }
    else
    {
        wxString inf = "δ�ҵ�" + articleName + " %s��";
        wxresult = wxString::Format(inf);
    }
    file.close();
    return wxresult;
}

//����Ŀ�����ߵĺ�����
unordered_set<string>find_coauthors(string authorName)
{
    vector<string>articles;
    unordered_set<string> authors;

    //unordered_multimap�ı���
    auto range = author_article.equal_range(authorName);
    for (auto it = range.first; it != range.second; ++it)
    {
        auto it2 = article_authors.find(it->second);
        if (it2 != article_authors.end())
        {
            for (int i = 0; i < it2->second.size(); i++)
            {
                if (it2->second[i] != authorName)
                    authors.insert(it2->second[i]);
            }
        }
    }
    return authors;
}

//����Ŀ�����ߵĺ����߲����
wxString output_coauthors(wxString authorName)
{
    wxString result;
    unordered_set<string> authors=find_coauthors(authorName.ToStdString());

    //���������
    if(authors.size())
    {
        result = "���� " + authorName + " �ĺ������У�\n";
        for (unordered_set<string>::iterator it = authors.begin(); it != authors.end(); ++it)
            result+=wxString::Format("- %s\n", *it);
    }
    else
    {
        result = "δ�ҵ�" + authorName + "�ĺ�����";
    }
    return result;
}

//���Ұ����ؼ��ʵ����²����
wxString find_by_keywords(wxString keywords)
{
    wxString result="�����ؼ��ʵ������У�\n";
    stringstream ss(keywords.ToStdString());
    string word;
    vector<string> words;
    bool b = false;

    // �Կո�Ϊ�ָ�����ȡ����
    while (ss >> word) 
    {
        words.push_back(word);
    }

    for(auto it=article_authors.begin();it!=article_authors.end();++it)
    {
        for(int j=0;j<words.size();j++)
        {
            if(it->first.find(words[j])!=string::npos)
            {
                result += wxString::Format("- %s\n", it->first+"\n");
                b=true;
            }
        }
    }
    if(!b)
        result="û�а��������ؼ��ʵ�����";

    return result;
}