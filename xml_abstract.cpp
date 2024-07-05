#include "xml_abstract.h"

//�ж�xml��Ϣ����
xml_information judge_xml_information(string str)
{
    if (str.find("<article mdate") != string::npos)
        return article_mdate;
    else if (str.find("<author>") != string::npos)
        return author;
    else if (str.find("<title>") != string::npos)
        return title;
    else if (str.find("<journal>") != string::npos)
        return journal;
    else if (str.find("<volume>") != string::npos)
        return volume;
    else if (str.find("<month>") != string::npos)
        return month;
    else if (str.find("<year>") != string::npos)
        return year;
    else if (str.find("<cdrom>") != string::npos)
        return cdrom;
    else if (str.find("<ee>") != string::npos)
        return ee;
}

//��ȡxml��ǩ�ڵ�ֵ����ֵ
void xml_abstract(string str, xml_information type, xml* x)
{
    size_t len = str.length();
    switch (type)
    {
    case 0:
        x->xml_label = str.substr(16); break;
    case 2:
        x->authors.push_back(str.substr(8, len - 17)); break;
    case 3:
        x->title = str.substr(7, len - 15); break;
    case 4:
        x->journal = str.substr(9, len - 19); break;
    case 5:
        x->volume = str.substr(8, len - 17); break;
    case 6:
        x->month = str.substr(7, len - 15); break;
    case 7:
        x->year = str.substr(6, len - 13); break;
    case 8:
        x->cdrom = str.substr(7, len - 15); break;
    case 9:
        x->ee = str.substr(4, len - 9); break;
    default:break;
    }
}

//��ȡarticle_mdateֵ
int get_article_mdate(string str)
{
    int len = str.length(), i = 0;
    for (; i < len; i++)
    {
        if (48 <= str[i] && str[i] <= 57)
            break;
    }
    return i;
}

//��ȡkey��ֵ
string get_key(string str)
{
    int n = 0, i = 0;
    for (; i < str.length(); i++)
    {
        if (str[i] == '\"')
            n++;
        if (n == 3)
            break;
    }
    return str.substr(17, i - 18);
}

//��ȡxml�ļ�
void readfile()
{
    fstream file;
    file.open("e:/���ݽṹ����ҵ/dblp.xml/dblp.xml", ios::in);
    string unknown_str = "";
    int sequence = 0;

    while (!file.eof())
    {
        getline(file, unknown_str);
        xml_information xml_type = judge_xml_information(unknown_str);
        xml new_element;
        //�����µ�������Ϣ����ʼ��xml������ֵ
        if (xml_type == article_mdate)
        {
            new_element.sequence = sequence;

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
                if (xml_type == author || xml_type == title || xml_type == year)
                    xml_abstract(unknown_str, xml_type, &new_element);
                getline(file, unknown_str);
            }

            //��ӳ����Ϣд���ļ�
            save_to_file("article_authors", new_element);
            save_to_file("author_article", new_element);
            save_to_file("year_article", new_element);

            sequence++;
        }
    }
    file.close();
}

//��ӳ����Ϣд���ļ�
void save_to_file(string str, xml element)
{
    string filename = str + ".txt";
    fstream outFile(filename, ios::out | ios::app);
    if (str == "article_authors")
    {
        for (int i = 0; i < element.authors.size(); i++)
        {
            outFile << element.title << "@" << element.authors[i] << endl;//��@�ָ�
        }
    }
    else if (str == "author_article")
    {
        for (int i = 0; i < element.authors.size(); i++)
        {
            outFile << element.authors[i] << "@" << element.title << endl;//��@�ָ�
        }

    }
    else if (str == "year_article")
    {
        outFile << element.year << "@" << element.title << endl;//��@�ָ�
    }
    outFile.close();
}