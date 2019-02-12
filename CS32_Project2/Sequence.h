//
//  Sequence.h
//  CS32_Project_2
//
//  Created by 王正 on 2018/4/20.
//  Copyright © 2018年 David Wang. All rights reserved.
//

#ifndef Sequence_h
#define Sequence_h

#include <string>

typedef std::string ItemType;

class Sequence{
public:
    Sequence();
    ~Sequence();
    Sequence(const Sequence& another_seq);
    Sequence& operator= (const Sequence& another_seq);
    bool empty() const;
    int size() const;
    bool insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
private:
    struct Node{
        Node * m_next;
        Node * m_before;
        ItemType m_value;
        int m_position;
    };
    Node * m_head;
    Node * m_tail;
    int m_size;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif /* Sequence_h */
