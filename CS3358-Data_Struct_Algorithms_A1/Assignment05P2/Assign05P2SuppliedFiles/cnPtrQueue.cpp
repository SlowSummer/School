#include "cnPtrQueue.h"
#include <cassert>
using namespace std;

namespace CS3358_SP2023_A5P2
{
   // to be implemented (part of assignment)

    void push(CNode* cnPtr)
    {
        inStack.push(cnPtr);
        numItems++;
    }
    void pop()
    {
        assert(!inStack.empty() || !outStack.empty())
        if (outStack.empty())
           while (!inStack.empty())
               outStack.push(inStack.top())
               inStack.pop()
               outStack.pop()
        return outstack.top();
    }





                item front() :
                assert(!inStack.empty() || !outStack.empty())
                if (outStack.empty())
                    while (!inStack.empty())
                        outStack.push(inStack.top())
                        inStack.pop()
                        return outStack.top()

                        bool empty() :
                        return outStack.empty() && inStack.empty()


}
