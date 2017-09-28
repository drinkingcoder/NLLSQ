#pragma once

#include<iostream>
#include<vector>
#include<map>
#include<memory>

using namespace std;

namespace NLLSQ {

    template<typename DataType>
    /*
     * marginal view - reference from original data
     * marginal sub problem - copy buffer from original marginal view
     *
     * conditional view - reference from original data
     * conditional sub problem - copy buffer from original conditional view
     */

    class NormalLinearProblem {
	    enum AVecStatus {
            ColVec,
            RowVec
        };

		class SubProblem:NormalLinearProblem {
		public:	
			SubProblem(
					const vector<shared_ptr<DataType>>& xs,
				   	const vector<shared_ptr<DataType>>& As,
				   	const vector<shared_ptr<DataType>>& bs,
					const vector<AVecStatus>& AVecStatus,
					const map<shared_ptr<DataType>, map<shared_ptr<DataType>, int>>& AUpperIndex,
					const map<shared_ptr<DataType>, map<shared_ptr<DataType>, int>>& ALowerIndex
					):m_xs(xs),m_As(As),m_AVecStatus(AVecStatus),m_AUpperIndex(AUpperIndex),m_ALowerIndex(ALowerIndex)
			{}

			void marginalize(shared_ptr<DataType> x)
			{
			}

			void condition(shared_ptr<DataType> x)
			{
				for( auto it = m_ALowerIndex[x].begin(); it != m_ALowerIndex[x].end(); it++)
					m_As.erase( it->second );
				for( auto it = m_AUpperIndex[x].begin(); it != m_AUpperIndex[x].end(); it++)
					m_As.erase( it->second );
			}

			shared_ptr<NormalLinearProblem> generateNormalLinearProblem()
			{
			}

		};

		shared_ptr<SubProblem>	m_subProblem;
		/*
		 * Input A is a symmetric matrix, we assume it's a upper triangle
		 */
    protected:
	    vector<shared_ptr<DataType>>    m_xs;
	    vector<int>                     m_xSize;
	    vector<shared_ptr<DataType>>    m_As;				/// A = JTOJ
	    vector<AVecStatus>              m_AVecStatus;
	    vector<shared_ptr<DataType>>    m_bs;

	    map<shared_ptr<DataType>, map<shared_ptr<DataType>, int>> m_AUpperIndex;
	    map<shared_ptr<DataType>, map<shared_ptr<DataType>, int>> m_ALowerIndex;


    public:
        void addxandb(shared_ptr<DataType> x, shared_ptr<DataType> b, int size) {
            m_xs.push_back(x);
            m_bs.push_back(b);
        }

        void addA(shared_ptr<DataType> x1, shared_ptr<DataType> x2, shared_ptr<DataType> A) {
            m_AUpperIndex[x1][x2] = m_As.size();
			m_ALowerIndex[x2][x1] = m_As.size();
            m_As.push_back(A);
//            m_AVecStatus.push_back(AVecStatus::RowVec);
        }

		void constructSubProblem()
		{
			m_subProblem = make_shared<SubProblem>(m_xs,m_As,m_bs,m_AVecStatus,m_AUpperIndex,m_ALowerIndex);
		}

	    void condition(shared_ptr<DataType> x)
	    {
		    m_subProblem->condition(x);
	    }

	    void marginalize(shared_ptr<DataType> x)
	    {
		    m_subProblem->marginalize(x);
	    }

	    shared_ptr<NormalLinearProblem> generateNormalLinearProblem()
	    {
		    return m_subProblem->generateNormalLinearProblem();
	    }

    };
}
