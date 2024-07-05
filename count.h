#pragma once
#include"common_use.h"
#include"search.h"

//����������������
struct author_articleNum
{
    string str = "";
    int n = 0;
    author_articleNum(string s, int num)
    {
        str = s; n = num;
    }
};

//����������ͳ��
wxString article_count();

//��ʾ�����·�����������
wxString show_years();

//�ؼ���Ƶ��ͳ��
wxString  keywords_count(wxString year);

//������ȫ��ͼͳ��
wxString graph_count();
//�����ڽӾ���
vector<vector<int>> find_all_graph(unordered_set<string>coauthors);
//ʹ��Bron-Kerbosch�㷨Ѱ����ȫ��ͼ
void BronKerboschIterative(const vector<vector<int>>& graph, map<int, int>& completeSubgraphCounts);
//�洢���ֶ���
struct BronKerboschState
{
    vector<int> R;
    vector<int> P;
    vector<int> X;
};