/*
 *  A task or process read one integer at a time from a socket. The incomming
 *  numbers are in random order. Upon reading a data from socket, it will print
 *  median of numbers so far it read from the socket.
 */

#include <bits/stdc++.h>
#include "../../library/TestInputUtil.h"

using namespace std;

class MedianComputer
{
    private:

        // Data in left partition are in Max Heap
        priority_queue<int> m_Left;

        // Data in Right Partiition are in Min heap
        priority_queue<int, vector<int>, std::greater<int>> m_Right;

        // The following vector is to test code
        vector<int> m_Nums;

    public:
        double getMedianForValidation();
        double getMedian(int num_);
};

double MedianComputer::getMedianForValidation()
{
    /*
     * Complexity: O(NlogN), N = total number of elements
     */
    sort(m_Nums.begin(), m_Nums.end());
    
    //PrintVector<int>(m_Nums);
    //PrintVector(m_Nums);
    if (m_Nums.size() == 1)
    {
         return m_Nums[0];
    }
    int idx = m_Nums.size()/2;

    if (m_Nums.size() % 2 == 0)
        return ((m_Nums[idx-1] + m_Nums[idx])/2.0);
    else
        return m_Nums[idx];
}

double MedianComputer::getMedian(int num_)
{
    /*
     * Complexity: N/2log(N/2) = N/2logN
     */
    m_Nums.push_back(num_);

    int left_sz = m_Left.size();
    int right_sz = m_Right.size();

    if (left_sz > right_sz)
    {
        if (m_Left.top() <= num_)
        {
            m_Right.push(num_);
        }
        else
        {
            int lt = m_Left.top();
            m_Left.pop();
            m_Right.push(lt);
            m_Left.push(num_);
        }
    }
    else if (right_sz > left_sz)
    {
        if (m_Right.top() >= num_)
        {
            m_Left.push(num_);
        }
        else
        {
            int rt = m_Right.top();
            m_Right.pop();
            m_Right.push(num_);
            m_Left.push(rt);
        }
    }
    else // left_sz == right_sz
    {
        if (left_sz == 0)
        {
            // num_ is the 1st number
            m_Left.push(num_);
        }
        else if (num_ > m_Left.top())
        {
            m_Right.push(num_);
        }
        else
        {
            m_Left.push(num_);
        }
    }

    left_sz = m_Left.size();
    right_sz = m_Right.size();

    if (abs(left_sz - right_sz) > 1)
    {
        cerr<<"DEBUG: Bug in code, Fix it..., LeftSz="<<left_sz<<", RightSz="<<right_sz<<endl;
    }
    if (left_sz > right_sz)
        return m_Left.top();
    else if (right_sz > left_sz)
        return m_Right.top();
    else
        return ((m_Left.top() + m_Right.top())/2.0);
}

int main()
{
    int T = 0;

    cout<< "Enter Number of Test: ";
    cin >> T;
    cin.ignore(numeric_limits<int>::max(), '\n');

    while(T--)
    {
        int TotalNum = 0;
        cout<<"Enter total number to be generated: ";
        cin >> TotalNum;
        cin.ignore(numeric_limits<int>::max(), '\n');

        srand(time(NULL));
        MedianComputer mc;

        for (int i = 0; i < TotalNum; ++i)
        {
            int num = rand() %(TotalNum + 1);

            double m1 = mc.getMedian(num);
            double m2 = mc.getMedianForValidation();

            if (m1 != m2)
            {
                cout<<"Failed: Computed Median ="<<m1
                    <<", Expected Median="<<m2<<endl;
            }
            else
            {
                //cout<<"Passed: Median = "<<m1<<endl;
            }
        }
    }
}
