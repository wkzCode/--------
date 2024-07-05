#pragma once
#include"common_use.h"

//ö��xml�ļ���Ϣ����
enum xml_information
{
    article_mdate, key, author, title, journal, volume, month, year, cdrom, ee
};

//xml�ṹ��
struct xml
{
    int sequence=0;
    string xml_label, article_mdate, key, title, journal, volume, month, year, cdrom, ee;
    vector<string>authors;
};

//�ж�xml��Ϣ����
xml_information judge_xml_information(string str);

//��ȡxml��ǩ�ڵ�ֵ����ֵ
void xml_abstract(string str, xml_information type, xml* x);

//��ȡarticle_mdateֵ
int get_article_mdate(string str);

//��ȡkey��ֵ
string get_key(string str);

//��ȡxml�ļ�
void readfile();

//��ӳ����Ϣд���ļ�
void save_to_file(string str, xml element);