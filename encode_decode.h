#ifndef ENCODE_H
#define ENCODE_H

#include <memory>
#include <queue>
#include <vector>

namespace encode_decode
{
    struct huffnode;
    using nodePtr = std::shared_ptr<huffnode>;
    using structNodePtr = std::shared_ptr<struct huffnode>;

    struct huffnode
    {
        unsigned char ch;
        size_t freq;
        bool node;
        nodePtr left, right;
        huffnode(unsigned char ch_, size_t freq_)
        {
            left = right = nullptr;
            this->ch = ch_;
            this->node = false;
            this->freq = freq_;
        }
        huffnode(size_t freq_)
        {
            left = right = nullptr;
            this->node = true;
            this->freq = freq_;
        }
    };

    struct compare
    {
        bool operator()(nodePtr left, nodePtr right)
        {
            return(left->freq > right->freq );
        }
    };

    void makeBitCode(structNodePtr root, std::string str)
    {
        if (root == nullptr)
        {
            return;
        }
        if (root->node == false)
        {
            inoutput::bitcode[root->ch] = str;
        }

        makeBitCode(root->left, str + "0");
        makeBitCode(root->right, str + "1");
    }

    template <class T>
    void printQue(T t)
    {
        while(!t.empty())
        {
            auto tt = t.top();
            std::cout << std::bitset<8>(tt->ch) << " " << std::dec << tt->freq<< "\n";
            t.pop();
        }
        std::cout << "\n";
    }

    void makeHuffTree()
    {
        structNodePtr left, right, top;
        std::priority_queue<nodePtr, std::vector<nodePtr>, compare> q;

        for(auto i = inoutput::freq.begin(); i != inoutput::freq.end(); ++i)
        {
            nodePtr tmp = std::make_shared<huffnode>(i->first, i->second);
            q.push(tmp);
        }
        //printQue(q);

        while (q.size() != 1)
        {
            left = q.top();
            std::cout << "left (" << left->node << ") " << std::bitset<8>(left->ch) << " " << std::dec << left->freq<< "\n";
            q.pop();
            right = q.top();
            std::cout << "right (" << right->node << ") " << std::bitset<8>(right->ch) << " " << std::dec << right->freq<< "\n";
            q.pop();
            top = std::make_shared<huffnode>(left->freq + right->freq);
            top->left = left;
            top->right = right;
            std::cout << "top (" << top->node << ") " << std::bitset<8>(top->ch) << " " << std::dec << top->freq<< "\n";
            q.push(top);
            printQue(q);
        }
        makeBitCode(q.top(), "");
    }
}

#endif // ENCODE_H
