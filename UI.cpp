#include"UI.h"

wxIMPLEMENT_APP(MyApp);


// ����ͬ��ͷ�ļ���Դ�ļ��У�ʹ������궨�������������¼�����
wxDEFINE_EVENT(wxEVT_COMMAND_MY_UPDATE_PROGRESS, wxThreadEvent);

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(): wxFrame(NULL, wxID_ANY, "�������׹���ϵͳ")
{
    //file��ť
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_LoadFile, "&����ӳ���ļ�\tCtrl-H", "��txt�м������������±���Ļ���ӳ���ϵ");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    //search��ť
    wxMenu* menuSearch = new wxMenu;
    menuSearch->Append(ID_Search_author_to_article,"&�������߶�Ӧ��������Ϣ","��ӳ���ϵ���ҵ����߶�Ӧ�����±���");
    menuSearch->Append(ID_Search_article, "&��ʾĿ�����ĵ�������Ϣ","��ԭ�ļ��в��Ҹ����Ķ�Ӧ��������Ϣ");
    menuSearch->Append(ID_Search_coauthor, "&����Ŀ�����ߵ����к�������","ͨ������ӳ���ҵ����к�����");
    menuSearch->Append(ID_Search_keywords, "&���ҹؼ��ʶ�Ӧ������Ϣ","������Ŀ�а����ùؼ��ֵ�������Ϣ");

    //count��ť
    wxMenu*menuCount = new wxMenu;
    menuCount->Append(ID_Count_authors, "&ͳ������������ǰ100������","ͳ��������ǰ100������");
    menuCount->Append(ID_Count_keywords, "&ͳ��Ƶ��ǰ10�Ĺؼ���","ͳ��Ƶ��ǰ10�Ĺؼ���");
    menuCount->Append(ID_Count_graphs, "&ͳ�Ƹ�����ȫ��ͼ����","ͳ�ƾ��ŷ����и�����ȫ��ͼ����");

    //show��ť
    wxMenu* menuShow = new wxMenu;
    menuShow->Append(ID_Show_years, "&��ʾ�����·�����������", "��ʾ�����·�����������");
    menuShow->Append(ID_Show_graphs, "&��ʾ����֮�������ϵͼ�������������Ϣ","��ʾ����֮�������ϵͼ�������������Ϣ");

    //help��ť
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    //��ť�˵�
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&�ļ�");
    menuBar->Append(menuSearch,"&����");
    menuBar->Append(menuCount,"&ͳ��");
    menuBar->Append(menuShow,"&��ʾ");
    menuBar->Append(menuHelp, "&����");
    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("��ӭʹ��!");

    //����ť�뺯����ϵ����
    Bind(wxEVT_MENU, &MyFrame::OnLoadFile, this, ID_LoadFile);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnSearch_author_to_article, this,ID_Search_author_to_article);
    Bind(wxEVT_MENU,&MyFrame::OnSearch_article,this,ID_Search_article);
    Bind(wxEVT_MENU,&MyFrame::OnSearch_coauthors,this,ID_Search_coauthor);
    Bind(wxEVT_MENU, &MyFrame::OnSearch_keywords, this, ID_Search_keywords);
    Bind(wxEVT_MENU,&MyFrame::OnCount_authors,this,ID_Count_authors);
    Bind(wxEVT_MENU,&MyFrame::OnCount_graphs,this,ID_Count_graphs);
    Bind(wxEVT_MENU,&MyFrame::OnCount_keywords,this,ID_Count_keywords);
    Bind(wxEVT_MENU, &MyFrame::OnShow_years, this, ID_Show_years);
    Bind(wxEVT_MENU, &MyFrame::OnShow_graphs, this, ID_Show_graphs);
    Bind(wxEVT_COMMAND_MY_UPDATE_PROGRESS, &MyFrame::OnUpdateProgress, this);
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxString wxstr = "����һ���������׹���ϵͳ�����ӣ��ܹ�ʵ�ֵĹ������£�\n";
    wxstr += wxString::Format("- %s\n", "F1. �����������ܡ���������������չʾ�����߷��������������Ϣ��\n�������������ĵ���Ŀ����չʾ�����ĵ����������Ϣ");
    wxstr+= wxString::Format("- %s\n", "F2. �����������������������չʾ�ڸ������к�����ϵ�������������ߡ�");
    wxstr+=wxString::Format("- %s\n","F3. ����ͳ�ƹ��ܡ����д��������ǰ100�����ߡ�");
    wxstr+=wxString::Format("- %s\n","F4. �ȵ�������ܡ�����ÿһ�귢��������У���Ŀ�������ĵ����У�����Ƶ������ǰ10�Ĺؼ��ʡ�");
    wxstr+=wxString::Format("- %s\n","F5. ����ƥ���������ܡ��������ɸ��ؼ��֣��ܿ�����������Ŀ�а����ùؼ��ֵ�������Ϣ");
    wxstr+=wxString::Format("- %s\n","F6. ���ŷ���������֮��ĺ�����ϵ���Կ�����һ��ͼ����ͳ������ͼ�и�����ȫ��ͼ�ĸ�����");
    wxstr+=wxString::Format("- %s\n","F7. ���ӻ���ʾ��ͨ��ͼ�λ����棬չʾ����֮�������ϵͼ�������������Ϣ��");
    wxMessageBox(wxstr, "���ڿ������׹���ϵͳ", wxOK | wxICON_INFORMATION);
}

//����ӳ���ϵ�����߼���
void MyFrame::OnLoadFile(wxCommandEvent& event)
{
    wxString result = judge_load();
    if (result == "")
    {
        wxMessageBox("�Ѽ����ļ�", "��ʾ", wxOK | wxICON_INFORMATION);
    }
    else
    {
        wxMessageBox("��ʼ����ӳ���ļ�", "��ʾ", wxOK | wxICON_INFORMATION);

        // �����첽����Ĳ���
        vector<string> messages = { "article_authors", "author_article" };

        // �洢�첽����� vector<future>
        vector<future<void>> asyncTasks;

        // ��������û�з���ֵ���첽���񣬲����ݲ���
        for (const auto& message : messages)
        {
            asyncTasks.push_back(async(launch::async, load_map, message));
        }

        asyncTasks.push_back(async(launch::async, load_yearmap));

        // �ڵȴ������첽������ɵ�ͬʱ�����������߳���ִ����������
        while (any_of(asyncTasks.begin(), asyncTasks.end(), [](const future<void>& task)
            {
                return task.wait_for(chrono::milliseconds(100)) != future_status::ready;
            }))
        {
            // �ڵȴ��Ĺ����п���ִ����������
            wxYield();
        }

        load_authors();
        load_years();

        wxMessageBox("ӳ���ļ������߼��ϼ������", "��ʾ", wxOK | wxICON_INFORMATION);
    }
}

// ͨ�����߲���������
void MyFrame::OnSearch_author_to_article(wxCommandEvent& event)
{
    wxString result = judge_load();
    if (result != "")
    {
        wxMessageBox(result, "��ʾ", wxOK | wxICON_INFORMATION);
    }
    else
    {
        wxString defaultText = "";
        wxString prompt = "��������������:";
        wxString caption = "���Ҹ����߷����ȫ�����µı�����";

        // �����Ի�����
        wxTextEntryDialog dialog(this, prompt, caption, defaultText, wxOK | wxCANCEL);

        // ���������Ϣ����ò��Һ���
        if (dialog.ShowModal() == wxID_OK)
        {
            wxString authorName = dialog.GetValue();
            result = find_by_author(authorName);

            // ��GUI����ʾ���
            wxMessageBox(result, "���ҽ��", wxOK | wxICON_INFORMATION);
        }
    }
}

//ͨ����������������ȫ����Ϣ
void MyFrame::OnSearch_article(wxCommandEvent& event)
{
    wxString defaultText = "";
    wxString prompt = "���������������±���:";
    wxString caption = "���Ҹ�����ȫ����Ϣ";

    //�����Ի�����
    wxTextEntryDialog dialog(this, prompt, caption, defaultText, wxOK | wxCANCEL);

    //���������Ϣ����ò��Һ���
    if (dialog.ShowModal() == wxID_OK)
    {
        wxString articleName = dialog.GetValue();
        //wxString result=find_specific_article(articleName);

        // ʹ�� async �����첽����
        auto task = async(launch::async, [&]() {return find_specific_article(articleName); });

        // �ڵȴ��첽������ɵ�ͬʱ�����������߳���ִ����������
        while (task.wait_for(chrono::milliseconds(100)) != future_status::ready)
        {
            // �ڵȴ��Ĺ����п���ִ����������
            wxYield();
        }

        // ��ȡ�첽����ķ���ֵ
        wxString result = task.get();

        // ��GUI����ʾ���
        wxMessageBox(result, "���ҽ��", wxOK | wxICON_INFORMATION);
    }
}

//���Һ�����
void MyFrame::OnSearch_coauthors(wxCommandEvent& event)
{
    wxString result = judge_load();
    if (result != "")
    {
        wxMessageBox(result, "��ʾ", wxOK | wxICON_INFORMATION);
    }
    else
    {
        wxString defaultText = "";
        wxString prompt = "��������������:";
        wxString caption = "���Ҹ����ߵĺ�����";

        //�����Ի�����
        wxTextEntryDialog dialog(this, prompt, caption, defaultText, wxOK | wxCANCEL);

        //���������Ϣ����ò��Һ���
        if (dialog.ShowModal() == wxID_OK)
        {
            wxString authorName = dialog.GetValue();
            result = output_coauthors(authorName);

            // ��GUI����ʾ���
            wxMessageBox(result, "���ҽ��", wxOK | wxICON_INFORMATION);
        }
    }
}

//���ҹؼ��ʶ�Ӧ������Ϣ
void MyFrame::OnSearch_keywords(wxCommandEvent& event)
{
    wxString result = judge_load();
    if (result != "")
    {
        wxMessageBox(result, "��ʾ", wxOK | wxICON_INFORMATION);
    }
    else
    {
        wxString defaultText = "����ؼ����ж�����ÿո����";
        wxString prompt = "������ؼ���:";
        wxString caption = "���ҹؼ��ֶ�Ӧ������Ϣ";

        //�����Ի�����
        wxTextEntryDialog dialog(this, prompt, caption, defaultText, wxOK | wxCANCEL);

        //���������Ϣ����ò��Һ���
        if (dialog.ShowModal() == wxID_OK)
        {
            wxString keywords = dialog.GetValue();
            // �����첽�߳�
            future<wxString> resultFuture = async(launch::async, find_by_keywords, keywords);

            // �ڵȴ��첽������ɵ�ͬʱ�����������߳���ִ����������
            while (resultFuture.wait_for(chrono::milliseconds(100)) != future_status::ready)
            {
                // �ڵȴ��Ĺ����п���ִ����������
                wxYield();
            }

            // ��ȡ�첽����ķ���ֵ
            result = resultFuture.get();

            // ��GUI����ʾ���
            wxMessageBox(result, "���ҽ��", wxOK | wxICON_INFORMATION);
        }
    }
}

//ͳ������������ǰ100������
void MyFrame::OnCount_authors(wxCommandEvent&event)
{
    wxString result = judge_load();
    if (result != "")
    {
        wxMessageBox(result, "��ʾ", wxOK | wxICON_INFORMATION);
    }
    else
    {
        // �����첽�߳�
        future<wxString> resultFuture = async(launch::async, article_count);

        // �ڵȴ��첽������ɵ�ͬʱ�����������߳���ִ����������
        while (resultFuture.wait_for(chrono::milliseconds(100)) != future_status::ready)
        {
            // �ڵȴ��Ĺ����п���ִ����������
            wxYield();
        }

        // ��ȡ�첽����ķ���ֵ
        result = resultFuture.get();
        // ��GUI����ʾ���
        wxMessageBox(result, "ͳ�ƽ��", wxOK | wxICON_INFORMATION);
    }
}

//��ʾ�����·�����������
void MyFrame::OnShow_years(wxCommandEvent& event)
{
    wxString result = judge_load();
    if (result != "")
    {
        wxMessageBox(result, "��ʾ", wxOK | wxICON_INFORMATION);
    }
    else
    {
        // �����첽�߳�
        future<wxString> resultFuture = async(launch::async, show_years);

        // �ڵȴ��첽������ɵ�ͬʱ�����������߳���ִ����������
        while (resultFuture.wait_for(chrono::milliseconds(100)) != future_status::ready)
        {
            // �ڵȴ��Ĺ����п���ִ����������
            wxYield();
        }

        // ��ȡ�첽����ķ���ֵ
        result = resultFuture.get();

        // ��GUI����ʾ���
        wxMessageBox(result, "ͳ�ƽ��", wxOK | wxICON_INFORMATION);
    }
}

//ͳ��Ƶ��ǰ10�Ĺؼ���
void MyFrame::OnCount_keywords(wxCommandEvent& event)
{
    wxString result = judge_load();
    if (result != "")
    {
        wxMessageBox(result, "��ʾ", wxOK | wxICON_INFORMATION);
    }
    else
    {
        wxString defaultText = "";
        wxString prompt = "���������:";
        wxString caption = "ͳ�Ƹ���ݱ����г���Ƶ��ǰ10�ĵ���";

        // �����Ի�����
        wxTextEntryDialog dialog(this, prompt, caption, defaultText, wxOK | wxCANCEL);

        // ���������Ϣ����ò��Һ���
        if (dialog.ShowModal() == wxID_OK)
        {
            wxString year = dialog.GetValue();
            result = keywords_count(year);

            // ��GUI����ʾ���
            wxMessageBox(result, "���ҽ��", wxOK | wxICON_INFORMATION);
        }
    }
}

//ͳ�Ƹ�����ȫ��ͼ����
void MyFrame::OnCount_graphs(wxCommandEvent& event)
{
    wxString result = judge_load();
    if (result != "")
    {
        wxMessageBox(result, "��ʾ", wxOK | wxICON_INFORMATION);
    }
    else
    {
        // �����첽�߳�
        future<wxString> resultFuture = async(launch::async, graph_count);

        // �ڵȴ��첽������ɵ�ͬʱ�����������߳���ִ����������
        while (resultFuture.wait_for(chrono::milliseconds(100)) != future_status::ready)
        {
            // �ڵȴ��Ĺ����п���ִ����������
            wxYield();
        }

        // ��ȡ�첽����ķ���ֵ
        result = resultFuture.get();

        // ��GUI����ʾ���
        wxMessageBox(result, "ͳ�ƽ��", wxOK | wxICON_INFORMATION);
    }
}

//��ʾ����֮�������ϵͼ�������������Ϣ
void MyFrame::OnShow_graphs(wxCommandEvent& event) 
{
    wxString result = judge_load();
    if (result != "")
    {
        wxMessageBox(result, "��ʾ", wxOK | wxICON_INFORMATION);
    }
    else
    {
        wxDialog* dialog = new wxDialog(this, wxID_ANY, wxT("���߹�ϵչʾ"), wxDefaultPosition, wxSize(700, 400)); // �����Ի���

        // ����һ��wxListCtrl��չʾ������Ϣ
        wxListCtrl* authorListCtrl = new wxListCtrl(dialog, wxID_ANY, wxDefaultPosition, wxSize(600, 300), wxLC_REPORT);
        authorListCtrl->InsertColumn(0, wxT("Author"), wxLIST_FORMAT_LEFT, 200);
        authorListCtrl->InsertColumn(1, wxT("Co-Authors"), wxLIST_FORMAT_LEFT, 250);
        authorListCtrl->InsertColumn(2, wxT("Common Works"), wxLIST_FORMAT_LEFT, 250);

        // ����һ��������
        wxGauge* progressBar = new wxGauge(dialog, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
        progressBar->SetValue(0); // ��ʼ����������ֵΪ0

        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(authorListCtrl, 1, wxEXPAND | wxALL, 5);
        sizer->Add(progressBar, 0, wxEXPAND | wxALL, 5);

        dialog->SetSizer(sizer); // ʹ��sizer������Ի���Ĳ���

        dialog->Show();
        dialog->Centre();

        // ������������б���߳�
        std::thread populateThread(&MyFrame::PopulateAuthors, this, authorListCtrl, progressBar);
        populateThread.detach(); // �����̷߳��룬��������
    }
}

void MyFrame::PopulateAuthors(wxListCtrl* authorListCtrl, wxGauge* progressBar)
{
    int numAuthors = authors.size();
    int processedAuthors = 0;
    for (const auto& author : authors) 
    {
        processedAuthors++;// ������Ϊ�Ѵ������
        vector<string>works;
        auto range = author_article.equal_range(author);
        if (range.first != author_article.end())
        {            
            for (auto it = range.first; it != range.second; ++it)// �����ƪ���µ����
                works.push_back(it->second);
            int size = works.size();
            unordered_set<string>coauthors = find_coauthors(author);
            for (auto it = coauthors.begin(); it != coauthors.end(); ++it)
            {
                auto range = author_article.equal_range(*it);
                vector<string>coworkers;              
                for (auto it2 = range.first; it2 != range.second; ++it2)// �����ƪ���µ����
                    coworkers.push_back(it2->second);
                wxString result;
                for (int i = 0; i < size; i++)
                    for (int j = 0; j < coworkers.size(); j++)
                        if (works[i] == coworkers[j])
                        {
                            result = result + works[i] + "\n";
                            coworkers.erase(coworkers.begin() + j);
                            break;
                        }
                long itemIndex;
                if (it == coauthors.begin()++)
                    itemIndex = authorListCtrl->InsertItem(authorListCtrl->GetItemCount(), author);
                else
                    itemIndex = authorListCtrl->InsertItem(authorListCtrl->GetItemCount(), "");

                authorListCtrl->SetItem(itemIndex, 1, *it);
                authorListCtrl->SetItem(itemIndex, 2, result);
            }
        }              
        int progress = static_cast<int>((static_cast<float>(processedAuthors) / numAuthors) * 100);// ���ý�������ֵΪ��ǰ����
        progressBar->SetValue(progress);        
        if (processedAuthors % 10 == 0) // Ϊ�����ܿ��ǣ�����ÿ�ε��������� 
            wxQueueEvent(this, new wxThreadEvent(wxEVT_COMMAND_MY_UPDATE_PROGRESS, progress));
    }
}

//��Ӧ����������
void MyFrame::OnUpdateProgress(wxThreadEvent& event)
{
    // ��ȡ�¼��еĽ���ֵ
    int progress = event.GetInt(); 
    // ȷ���������Ѿ������������ý�������ֵ
    if (progressBar)
    { 
        progressBar->SetValue(progress);
    }
}