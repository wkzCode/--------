#include"common_use.h"

//����ӳ���ϵ
//���⵽���ߵ�ӳ��
extern unordered_map<string, vector<string>>article_authors;
//���ߵ������ӳ��
extern unordered_multimap<string, string>author_article;
//��ݵ������ӳ��
extern unordered_multimap<string, string>year_article;

//���弯��
//�������߼���
extern unordered_set<string> authors;
//�洢������ݵļ���
extern unordered_set<string> years;

//�ָ�ӳ���ļ����ַ���
int split(string str);

//�������߱���ӳ���ϵ
void load_map(string str);

//�������������ӳ���ļ�
void load_yearmap();

//�������߼���
void load_authors();

//������ݼ���
void load_years();

//�����ж�
wxString judge_load();