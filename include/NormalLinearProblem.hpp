#pragma once

#include<iostream>
#include<vector>
#include<map>
#include<memory>

using namespace std;

template<typename DataType>
class NormalLinearProblem
{
    vector<shared_ptr<DataType>> m_xs;
    vector<shared_ptr<DataType>> m_As;
    vector<shared_ptr<DataType>> m_bs;

    map< shared_ptr<DataType> ,map< shared_ptr<DataType>, int>> m_AIndex;
protected:

public:
    void addxandb(shared_ptr<DataType> x,shared_ptr<DataType> b)
    {
        m_xs.push_back(x);
        m_bs.push_back(b);
    }

    void addA(shared_ptr<DataType> x1 ,shared_ptr<DataType> x2 ,shared_ptr<DataType> A)
    {
        m_AIndex[x1][x2] = m_As.size();
        m_As.push_back(A);
    }

    void setb(shared_ptr<DataType> x, shared_ptr<DataType> b)
    {
    }
    void setA(shared_ptr<DataType> x1, shared_ptr<DataType> x2, shared_ptr<DataType> A)
    {
    }
    void replacex(shared_ptr<DataType> xBefore, shared_ptr<DataType> xAfter)
    {
    }


};
