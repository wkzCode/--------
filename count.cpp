#include"count.h"

//������
mutex mtx; 

//����������ͳ��
wxString article_count()
{
    wxString result;
    result = "д��������ǰ100������Ϊ: \n";
    vector<author_articleNum>counts;
    int size = 0;

    for (auto it = authors.begin(); it != authors.end(); ++it)
    {
        int n = author_article.count(*it);
        if (n > 1)
        {
            int len = counts.size();
            author_articleNum new_element(*it, n);
            if (counts.size() == 0)
                counts.push_back(new_element);
            //��С��Ϊ100����������
            else if (len < 100)
            {
                bool result = false;
                for (int i = 0; i < len; i++)
                {
                    if (counts[i].n < n)
                    {
                        counts.insert(counts.begin() + i, new_element);
                        result = true;
                        break;
                    }
                }
                if (!result)
                    counts.push_back(new_element);
            }
            //Ԫ�س���100�󣬶Դ��ڵ�100��Ԫ�ص�ֵ��������
            else
            {
                if (n > counts[99].n)
                {
                    for (int i = 0; i < 100; i++)
                    {
                        if (counts[i].n < n)
                        {
                            counts.insert(counts.begin() + i, new_element);
                            break;
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < 100; i++)
        result += wxString::Format("- %s\n", counts[i].str + ": " + to_string(counts[i].n) + "ƪ");

    return result;
}

//��ʾ�����·�����������
wxString show_years()
{
    wxString result;
    result = "�����·�������������: \n";
    for (auto it = years.begin(); it != years.end(); it++)
    {
        result += wxString::Format("- %s\n", *it);
    }
    return result;
}

//�ؼ���Ƶ��ͳ��
wxString keywords_count(wxString year)
{
    wxString result;
    result = "�������±����г���Ƶ������ǰ10�Ĺؼ���Ϊ: \n";
    vector<string>articles;
    auto range = year_article.equal_range(year.ToStdString());
    if (range.first != year_article.end())
    {
        unordered_map<string, int>word_sequence;
        // �����ƪ���µ����
        for (auto it = range.first; it != range.second; ++it)
        {
            string sentence = it->second.substr(0, it->second.length() - 2);
            stringstream ss(sentence);
            string word;
            vector<string> words;

            // �Կո�Ϊ�ָ�����ȡ����
            while (ss >> word) 
            {
                if (word != "of" && word != "A"&& word != "a"&& word != "to"&& word != "the"&& word != "is"
                    && word != "how"&& word != "Why"&& word != "and"&&word != "on"&& word != "for"&&
                    word != "in"&& word != "The"&& word != "with"&& word != "an"&& word != "by"&&
                    word != "On"&& word != "An"&& word != "-"&& word != "With"&& word != "using"&& word != "Using")
                    words.push_back(word);
            }
            for(int i=0; i<words.size(); i++)
            {
                auto it2 = word_sequence.find(words[i]);
                if(it2!=word_sequence.end())
                    it2->second++;
                else
                    word_sequence.emplace(words[i], 1);
            }
        }

        vector<pair<string, int>>maxwords;
        for (auto it = word_sequence.begin(); it != word_sequence.end(); ++it)
        {
            int len = maxwords.size();
            if (len == 0)
            {
                maxwords.push_back(*it);
            }
            else if(len<10)
            {
                bool result = false;

                for (int i = 0; i < len; i++)
                {
                    if (maxwords[i].second < it->second)
                    {
                        maxwords.insert(maxwords.begin() + i, *it);
                        result = true;
                        break;
                    }
                }
                if (!result)maxwords.push_back(*it);
            }
            else
            {
                if (it->second > maxwords[9].second)
                {
                    for (int i = 0; i < 10; i++)
                    {
                        if (maxwords[i].second < it->second)
                        {
                            maxwords.insert(maxwords.begin() + i, *it); break;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < 10; i++)
            result += wxString::Format("- %s\n", maxwords[i].first + ": " + to_string(maxwords[i].second) + "��");
    }
    else
        result = wxString::Format("δ�ҵ����귢������� %s��", year);

    return result;
}

//������ȫ��ͼͳ��
wxString graph_count()
{
    mutex mtx; // ������
    wxString result="������ȫ��ͼͳ�����£�\n";
    map<int, int> completeSubgraphCounts; // ���ڴ洢������ȫ��ͼ������
    vector<future<void>> futures;
    unordered_set<string>coauthors;
    int size = 0;

    //�������߲������첽�߳�Ѱ����ȫ��ͼ
    for(auto it =authors.begin(); it !=authors.end();++it)
    {
        if (coauthors.find(*it) == coauthors.end())
        {
            unordered_set<string>this_coauthors = find_coauthors(*it);
            size = this_coauthors.size();
            coauthors.insert(this_coauthors.begin(), this_coauthors.end());
            if (size > 0)
            {
                futures.emplace_back(
                    async(launch::async, [&completeSubgraphCounts, &mtx, this_coauthors]() 
                    {
                        vector<vector<int>> graph = find_all_graph(this_coauthors);
                        BronKerboschIterative(graph, completeSubgraphCounts);
                    }));
            }
        }
    }
    
    // �ȴ������������
    for (auto&& future : futures)
    {
        future.get();
    }

    //չʾ���
    for (auto it=completeSubgraphCounts.begin();it!=completeSubgraphCounts.end();it++) 
    {
        result += wxString::Format("- %s\n", to_string(it->first) + "��: " + to_string(it->second) + "��");
    }
    return result;
}
//�����ڽӾ���
vector<vector<int>> find_all_graph(unordered_set<string>coauthors)
{
    vector<string>v_coauthors(coauthors.begin(),coauthors.end());
    int size=v_coauthors.size();
    vector<vector<int>>graph(size, vector<int>(size));

    for (int i = 0; i < size; i++)
    {
        unordered_set<string>c_coauthors = find_coauthors(v_coauthors[i]);
        vector<string>vc_coauthors(c_coauthors.begin(), c_coauthors.end());

        for(int j=0;j<vc_coauthors.size();j++)
        {
            //���ж��Ƿ����ٽ��б���
            if (coauthors.find(vc_coauthors[j]) != coauthors.end())
            {
                for (int k = 0; k < size; k++)
                {
                    if (vc_coauthors[j] == v_coauthors[k])
                    {
                        graph[i][k] = 1;
                        graph[k][i] = 1;
                        break;
                    }
                }
            }
        }
    }

    return graph;    
}
//ʹ��Bron-Kerbosch�㷨Ѱ����ȫ��ͼ
void BronKerboschIterative(const vector<vector<int>>& graph, map<int, int>& completeSubgraphCounts) 
{
    stack<BronKerboschState> stk;//��ֱֹ��ʹ�õݹ���ݹ���ջ
    BronKerboschState initialState;
    for (int i = 0; i < graph.size(); i++) // ��ʼ��PΪͼ�е����ж���
        initialState.P.push_back(i);
    stk.push(initialState);
    while (!stk.empty()) 
    {
        BronKerboschState current = stk.top();
        stk.pop();
        if (current.P.empty() && current.X.empty()) 
        {
            int cliqueSize = current.R.size();
            if (cliqueSize > 0) 
            {
                lock_guard<mutex> lock(mtx); // ʹ�û���������������Դ
                completeSubgraphCounts[cliqueSize]++;
            }
        }
        else 
        {
            int pivot = current.P.empty() ? -1 : current.P[0];
            if (pivot != -1) 
            {
                auto it = current.P.begin();
                while (it != current.P.end()) 
                {
                    int v = *it;
                    if (graph[pivot][v] == 1) // �����pivot����������
                    {
                        ++it;continue;
                    }
                    BronKerboschState newState;
                    newState.R = current.R;
                    newState.R.push_back(v); // ��v�����R
                    // ��P�ǵ�ǰP��������v�����Ķ���
                    for (int w : current.P) if (graph[v][w] == 1) newState.P.push_back(w);
                    // ��X�ǵ�ǰX��������v�����Ķ���
                    for (int w : current.X) if (graph[v][w] == 1) newState.X.push_back(w);
                    stk.push(newState);
                    // ��P���Ƴ�v����v��ӵ�X���Ա�������ظ�����
                    it = current.P.erase(it);
                    current.X.push_back(v);
                }
            }
        }
    }
}