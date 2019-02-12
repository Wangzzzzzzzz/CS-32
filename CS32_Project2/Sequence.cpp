//
//  Sequence.cpp
//  CS32_Project_2
//
//  Created by 王正 on 2018/4/20.
//  Copyright © 2018年 David Wang. All rights reserved.
//

#include "Sequence.h"

/*Member functions*/
////////////////////////////////////////////////////////////////////////////////
Sequence::Sequence(){
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}


Sequence::~Sequence(){
    Node* temp = m_head;
    for(;temp != nullptr; temp = m_head){
        m_head = temp->m_next;
        delete temp;
    }
}

Sequence::Sequence(const Sequence& another_seq){
    if(another_seq.empty()){
        this->m_size = 0;
        this->m_head = nullptr;
        this->m_tail = nullptr;
    }
	else {
		this->m_size = another_seq.m_size;
		this->m_head = new Node;
		this->m_head->m_before = nullptr;
		this->m_head->m_position = 0;
		this->m_head->m_value = another_seq.m_head->m_value;
		Node* temp = this->m_head;
		for (Node* ano_temp = another_seq.m_head->m_next;
			ano_temp != nullptr;
			temp = temp->m_next, ano_temp = ano_temp->m_next) {
			temp->m_next = new Node;
			temp->m_next->m_before = temp;
			temp->m_next->m_position = (temp->m_position + 1);
			temp->m_next->m_value = ano_temp->m_value;
		}
		temp->m_next = nullptr;
		this->m_tail = temp;
	}
}

Sequence& Sequence::operator= (const Sequence& another_seq){
    if (this != &another_seq){
        Sequence temp(another_seq);
        swap(temp);
    }
    return (*this);
}

bool Sequence::empty() const{
    return (m_size == 0);
}

int Sequence::size() const{
    return m_size;
}

bool Sequence::insert(int pos, const ItemType& value){
    if(pos < 0 || pos > m_size)
        return false;

	//for empty Sequence
    if(this->empty()){
        m_head = new Node;
        m_head->m_before = nullptr;
        m_head->m_next = nullptr;
        m_head->m_position = 0;
        m_head->m_value = value;
        m_tail = m_head;
        m_size++;
        return true;
    }

	//for non-empty Sequence
	else {
		Node* temp;
		if (pos == 0) {
			temp = m_head;

			//create a new Node
			m_head = new Node;

			//initialize new element 0
			m_head->m_next = temp;
			m_head->m_before = nullptr;
			m_head->m_position = 0;
			m_head->m_value = value;

			//modify original elements
			temp->m_before = m_head;
			for (; temp != nullptr; temp = temp->m_next)
				(temp->m_position)++;

			m_size++;
			return true;
		}

		for (temp = m_head; temp->m_next != nullptr && (temp->m_position + 1) != pos; temp = temp->m_next);

		// if not inserting at the last position.
		if (temp->m_next != nullptr) {
			Node *temp2 = temp->m_next;
			temp2->m_before = new Node;
			temp2->m_before->m_before = temp;
			temp2->m_before->m_next = temp2;
			temp2->m_before->m_value = value;
			temp->m_next = temp2->m_before;
			temp->m_next->m_position = (temp->m_position + 1);
			for (; temp2 != nullptr; temp2 = temp2->m_next)
				(temp2->m_position)++;
			m_size++;
			return true;
		}

		// insert at the last position
		temp->m_next = new Node;
		temp->m_next->m_before = temp;
		temp->m_next->m_value = value;
		temp->m_next->m_position = (temp->m_position + 1);
		temp->m_next->m_next = nullptr;
		m_tail = temp->m_next;
		m_size++;
		return true;
	}
}

int Sequence::insert(const ItemType& value){
    Node * temp = m_head;
    int i = 0;

    //find the position should be inserted
    while(i < m_size && temp->m_value < value){
        temp = temp->m_next;
        i++;
    }
    this->insert(i, value);
    return i;
}

bool Sequence::erase(int pos){
    if(pos < 0 || pos >= m_size)
        return false;
    
    // if there is only one element
    if(m_size == 1){
        delete m_head;
        m_head = nullptr;
        m_tail = nullptr;
        m_size--;
        return true;
    }
    
    //if there are more than one element
    
    Node* temp;
    //remove the first element
    if(pos == 0){
        temp = m_head;
        m_head = temp->m_next;
        m_head->m_before = nullptr;
		temp->m_before = nullptr;
		temp->m_next = nullptr;

        delete temp;
        m_size--;
        
        //update the position of each element
        for(temp = m_head; temp != nullptr; temp = temp->m_next)
            (temp->m_position)--;
        return true;
    }
    
    //remove element at the end
    if(pos == m_size - 1){
        temp = m_tail;
        m_tail = temp->m_before;
        m_tail->m_next = nullptr;
        delete temp;
        m_size--;
        return true;
    }
    
    //remove element from middle
	temp = m_head;
    for(; temp->m_position != pos; temp = temp->m_next);
    temp->m_next->m_before = temp->m_before;
    temp->m_before->m_next = temp->m_next;
    Node* temp2 = temp->m_next;
    delete temp;
    m_size--;
    
    //update the position of each element
    for(; temp2 != nullptr; temp2 = temp2->m_next)
        (temp2->m_position)--;
    return true;
}

int Sequence::remove(const ItemType& value){
    int pos = this->find(value);
    if(pos == -1)
        return 0;
    
    int count = 0;
    while (pos != -1) {
        this->erase(pos);
        pos = this->find(value);
        count++;
    }
    return count;
}

bool Sequence::get(int pos, ItemType& value) const{
    if(pos < 0 || pos >= m_size)
        return false;
    Node* temp = m_head;
    for(; temp->m_position != pos; temp = temp->m_next);
    value = temp->m_value;
    return true;
}

bool Sequence::set(int pos, const ItemType& value){
    if(pos < 0 || pos >= m_size)
        return false;
    Node* temp = m_head;
    for(; temp->m_position != pos; temp = temp->m_next);
    temp->m_value = value;
    return true;
}

int Sequence::find(const ItemType& value) const{
    Node* temp = m_head;
    for(; temp != nullptr && temp->m_value != value; temp = temp->m_next);
    if(temp == nullptr)
        return -1;
    return (temp->m_position);
}

void Sequence::swap(Sequence& other){
    //switch the size
    int temp_size = this->m_size;
    this->m_size = other.m_size;
    other.m_size = temp_size;
    
    //exchange head
    Node* temp_head = this->m_head;
    this->m_head = other.m_head;
    other.m_head = temp_head;
    
    //exchange tail
    Node* temp_tail = this->m_tail;
    this->m_tail = other.m_tail;
    other.m_tail = temp_tail;
}

////////////////////////////////////////////////////////////////////////////////////////////
/*End of member function*/


/*Non-member Functions*/
////////////////////////////////////////////////////////////////////////////////////////////
int subsequence(const Sequence& seq1, const Sequence& seq2) {
	bool equal = true;
	ItemType temp;
	ItemType temp2;
	seq2.get(0, temp2);
	if (seq2.empty() || seq1.size() < seq2.size())
		return -1;
	for (int i = 0; i < (seq1.size() - seq2.size() + 1); i++) {
		seq1.get(i, temp);
		//first item equal
		if (temp == temp2) {
			equal = true;
			for (int j = 1; j < seq2.size() && equal; j++) {
				seq1.get(i + j, temp);
				seq2.get(j, temp2);
				equal = (temp == temp2);
			}
			if (equal)
				return i;
			seq2.get(0, temp2);
		}
	}
	return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
	int minSize = (seq1.size() < seq2.size() ? seq1.size() : seq2.size());
	ItemType temp;
	int count = 0;

	//seq1 and seq2 are not result
	if (&result != &seq1 && &result != &seq2) {
		if (!result.empty())
		{
			int size = result.size();
			for (int i = 0; i < size; i++)
				result.erase(0);
		}

		//intersect the overlap part
		for (int i = 0; i < minSize; i++) {
			seq1.get(i, temp);
			result.insert(count, temp);
			count++;
			seq2.get(i, temp);
			result.insert(count, temp);
			count++;
		}

		if (seq1.size() > minSize) {
			const int size = seq1.size();
			for (int i = 0; i < (size - minSize); i++) {
				seq1.get((minSize + i), temp);
				result.insert(count, temp);
				count++;
			}
		}

		else if (seq2.size() > minSize) {
			const int size = seq2.size();
			for (int i = 0; i < (size - minSize); i++) {
				seq2.get((minSize + i), temp);
				result.insert(count, temp);
				count++;
			}
		}
	}

	//either one of seq1 and seq2 is result itself
	else {
		Sequence temp1(seq1);
		Sequence temp2(seq2);

		if (!result.empty())
		{
			int size = result.size();
			for (int i = 0; i < size; i++)
				result.erase(0);
		}

		//intersect the overlap part
		for (int i = 0; i < minSize; i++) {
			temp1.get(i, temp);
			result.insert(count, temp);
			count++;
			temp2.get(i, temp);
			result.insert(count, temp);
			count++;
		}

		if (temp1.size() > minSize) {
			const int size = temp1.size();
			for (int i = 0; i < (size - minSize); i++) {
				temp1.get((minSize + i), temp);
				result.insert(count, temp);
				count++;
			}
		}

		else if (temp2.size() > minSize) {
			const int size = temp2.size();
			for (int i = 0; i < (size - minSize); i++) {
				temp2.get((minSize + i), temp);
				result.insert(count, temp);
				count++;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
/*End of Non-member functions*/