#pragma once
#include"common_use.h"
#include"xml_abstract.h"
#include"Data_initialize.h"

//�������߲���������Ϣ
wxString find_by_author(wxString authorName);

//�����ض�������Ϣ�����
wxString find_specific_article(wxString articleName);

//������Ŀ�����ߵĺ����߲����
unordered_set<string> find_coauthors(string authorName);
wxString output_coauthors(wxString authorName);

//���Ұ����ؼ��ʵ����²����
wxString find_by_keywords(wxString keywords);