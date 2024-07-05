#pragma once
#include"common_use.h"
#include"search.h"
#include"count.h"

// ʹ�������Ϊ����Զ����¼�����һ���µ�����
wxDECLARE_EVENT(wxEVT_COMMAND_MY_UPDATE_PROGRESS, wxThreadEvent);

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

//����
enum wxKinds
{
    ID_LoadFile = 1,
    ID_Search_author_to_article = 2,
    ID_Search_article = 3,
    ID_Search_coauthor = 4,
    ID_Search_keywords = 5,
    ID_Count_authors = 6,
    ID_Count_keywords = 7,
    ID_Count_graphs = 8,
    ID_Show_graphs = 9,
    ID_Show_years = 10
};

class MyFrame : public wxFrame
{
public:
    ~MyFrame() 
    {
        // ���ñ�־���ù����߳�֪��Ӧ�ó������ڹر�
        delete progressBar;
    }
    MyFrame();
    void OnShow_graphs(wxCommandEvent& event);
private:
    //atomic<bool> isRunning{ true };
    wxGauge* progressBar;
    // �����¼�����������
    void OnLoadFile(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnSearch_author_to_article(wxCommandEvent& event);
    void OnSearch_article(wxCommandEvent& event);
    void OnSearch_coauthors(wxCommandEvent& event);
    void OnSearch_keywords(wxCommandEvent& event);
    void OnCount_authors(wxCommandEvent& event);
    void OnShow_years(wxCommandEvent& event);
    void OnCount_keywords(wxCommandEvent& event);
    void OnCount_graphs(wxCommandEvent& event);
    void PopulateAuthors(wxListCtrl* authorListCtrl, wxGauge* progressBar);
    void OnUpdateProgress(wxThreadEvent& event);
};
