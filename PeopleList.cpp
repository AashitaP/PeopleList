//  project 3 cs32
//
//  Created by Aashita on 21/7/17.
//  Copyright © 2017 cs32. All rights reserved.
//

#include "PeopleList.h"
#include <iostream>

PeopleList::Node::Node() //default constructor does nothing, for dummy node
{}

PeopleList::Node::Node(std::string firstName, std::string lastName, InfoType value): first_name(firstName), last_name(lastName), m_value(value) //non default constructor
{}

PeopleList::PeopleList()
{
    head = new Node;
    head->next = head;
    head -> prev = head;
    m_size = 0;
}// Create an empty In (i.e., one with no InfoType values)

PeopleList::~PeopleList()
{
    Node* n = head;
    for (int i =0; i != m_size; i++)
    {
        Node* temp = n;
        n = n->next;
        delete temp; //delete everything but last node
    }
    delete n; //delete last node
    
}//destructor

PeopleList::PeopleList(const PeopleList& other)
{
    head = new Node;
    head->next = head;
    head -> prev = head;
    m_size = 0;
    Node* n = head;
    Node* prevnode = head;
    Node* copy = other.head -> next;
    for (int i = 0; i < other.size(); i++) //loop through other
    {
        Node* newNode = new Node(copy -> first_name, copy -> last_name, copy->m_value); //copy nodes
        n->next = newNode;
        n->prev = prevnode; //set next and prev pointers
        newNode -> next = head;
        newNode -> prev = n;
        copy = copy -> next;
        prevnode = n;
        n = n->next;
        m_size++;
    }
}//copy constructor

PeopleList& PeopleList:: operator=(const PeopleList& other)
{
    if (this == &other) //if assigning to self, return
        return *this;
    
    PeopleList copylist(other);
    swap(copylist);
    return *this;
}//assignment operator

bool PeopleList::empty() const
{
   if (m_size == 0)
       return true;
    return false;
}// Return true if the list is empty, otherwise false.

int PeopleList::size() const
{
    return m_size;
}// Return the number of elements in the linked list.

bool PeopleList::add(const std::string& firstName, const std::string& lastName, const InfoType& value)
{
    Node* n = head -> next;
    for (; n!=head; n = n-> next) //loop through
    {
        if (firstName == n-> first_name && lastName == n -> last_name) //if already exists, return
            return false;
        else if (lastName == n->last_name) //is last name is same sort according to first name
        {
            if (firstName < n->first_name)
            break;
        }
        else if (lastName < n->last_name) //sort according to last name
            break;
    }
    
    Node* newNode = new Node(firstName, lastName, value);
    newNode -> next = n;
    newNode -> prev = n-> prev;
    n -> prev -> next = newNode;
    n -> prev = newNode;
    m_size++;
    
    return true;
}
// If the full name (both the first and last name) is not equal to any full name currently
// in the list then add it and return true. Elements should be added according to
// their last name. Elements with the same last name should be added according to
// their first names. Otherwise, make no change to the list and return false
// (indicating that the name is already in the list).

bool PeopleList::change(const std::string& firstName, const std::string& lastName, const InfoType& value)
{
    Node* n = head -> next;
    for (; n!=head; n = n-> next)
    {
        if (firstName == n-> first_name && lastName == n -> last_name) //if name exists, change value
        {
            n->m_value = value;
            return true;
        }
    }
    return false;
}
// If the full name is equal to a full name currently in the list, then make that full
// name no longer map to the value it currently maps to, but instead map to
// the value of the third parameter; return true in this case.
// Otherwise, make no change to the list and return false.

bool PeopleList::addOrChange(const std::string& firstName, const std::string& lastName, const InfoType& value)
{
   if(change(firstName, lastName, value)) //if change returns true (i.e. name exists), change
       change(firstName, lastName, value);
   else
       add(firstName, lastName, value); //else add that name and value

    return true;
}
// If full name is equal to a name currently in the list, then make that full name no
// longer map to the value it currently maps to, but instead map to
// the value of the third parameter; return true in this case.
// If the full name is not equal to any full name currently in the list then add it
// and return true. In fact this function always returns true.

bool PeopleList::remove(const std::string& firstName, const std::string& lastName)
{
    for (Node* n = head -> next; n!=head; n = n-> next) //loop through
        if (firstName == n-> first_name && lastName == n -> last_name) //search for name and delete it if it exists
        {
            Node* temp = n;
            n -> prev -> next = n-> next;
            n->next->prev = n->prev;
            delete temp;
            m_size--;
            return true;
        }
    return false;
}
// If the full name is equal to a full name currently in the list, remove the
// full name and value from the list and return true.  Otherwise, make
// no change to the list and return false.

bool PeopleList::contains(const std::string& firstName, const std::string& lastName) const
{
    for (Node* n = head -> next; n!=head; n = n-> next)
        if (firstName == n-> first_name && lastName == n -> last_name)
        {
            return true;
        }
    return false;
}
// Return true if the full name is equal to a full name currently in the list, otherwise
// false.

bool PeopleList::lookup(const std::string& firstName, const std::string& lastName, InfoType& value) const
{
    for (Node* n = head -> next; n!=head; n = n-> next) //loop through
        if (firstName == n-> first_name && lastName == n -> last_name)
        {
            value = n-> m_value; //store value
            return true;
        }
    return false;
} 
// If the full name is equal to a full name currently in the list, set value to the
// value in the list that that full name maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.

bool PeopleList::get(int i, std::string& firstName, std::string& lastName, InfoType& value) const
{
    if (i >= size() || i<0) //return false if accessing count out of the list
        return false;
   
    int count = 0;
    for (Node* n = head -> next; n!=head; n = n-> next) //else loop through and store value at that position
    {
        if (i == count)
        {
            firstName = n->first_name;
            lastName = n-> last_name;
            value = n->m_value;
        }
        count++;
    }
    return true;
}
// If 0 <= i < size(), copy into firstName, lastName and value parameters the
// corresponding information of the element at position i in the list and return
// true.  Otherwise, leave the parameters unchanged and return false.
// (See below for details about this function.)

void PeopleList::swap(PeopleList& other)
{
    std::swap(head, other.head); //swap heads of list
    std::swap(m_size, other.m_size); //swap sizes of list
}
// Exchange the contents of this list with the other one.

/*void PeopleList::dump() const
{
    for (Node* p = head -> next; p != head; p = p-> next)
        std::cerr<< p->last_name << p->first_name << p->m_value << std::endl;
}*/

bool combine(const PeopleList& m1, const PeopleList& m2, PeopleList& result)
{
    PeopleList newresult;
    std::string m1first;
    std::string m1last;
    std::string m2first;
    std::string m2last;
    InfoType m1value;
    InfoType m2value;
    bool returnbool = true;
    
    for (int n = 0; n < m2.size(); n++) //loop through people list m2
    {
        m2.get(n, m2first, m2last, m2value); //for each entry in m2
        if (!m1.contains(m2first, m2last)) //if m1 does not contain the same name
            newresult.add(m2first, m2last, m2value); //add to result
    }
    
    for (int n = 0; n < m1.size(); n++) //loop through people list m1
    {
        m1.get(n, m1first, m1last, m1value); //for each entry in m1
        if (!m2.contains(m1first, m1last)) //if m2 does not contain the same name
            newresult.add(m1first, m1last, m1value); //add to result
        else if (m2.contains(m1first, m1last)) //if it does contain
        {
            m2.lookup(m1first, m1last, m2value); //store value corresponding to that name in m2value
            if(m2value != m1value) //if the names are same but values different
            {
                returnbool = false; //set returning boolean to false
            }
            else if (m2value == m1value) //else if the values are the same
            {
                newresult.add(m1first, m1last, m1value); //add the name
            }
        }
    }
    
    result.swap(newresult); //store the final list in the list passed into result parameter
    return returnbool;
}
void psearch (const std::string& fsearch, const std::string& lsearch, const PeopleList& p1, PeopleList& result)
{
    PeopleList newresult;
    std::string p1first;
    std::string p1last;
    InfoType p1value;
    if (fsearch == "*" && lsearch == "*") //if both fsearch and lsearch are "*"
        newresult = p1; //copy all the entries
    else if (fsearch == "*") //else if only fsearch
    {
        for (int n = 0; n < p1.size(); n++) //loop through list
        {
            p1.get(n, p1first, p1last, p1value); //for each entry in p1
            if (lsearch == p1last) //if last name corresponds
                newresult.add(p1first, p1last, p1value); //add to result
        }
    }
    
    else if (lsearch == "*") //else if only lsearch
    {
        for (int n = 0; n < p1.size(); n++) //loop through list
        {
            p1.get(n, p1first, p1last, p1value);//for each entry in p1
            if (fsearch == p1first) //if first name corresponds
                newresult.add(p1first, p1last, p1value); //add to result
        }
    }
    
    else //if neither are "*"
    {
        for (int n = 0; n < p1.size(); n++) //loop through list
        {
            p1.get(n, p1first, p1last, p1value); //for each entry in p1
            if (lsearch == p1last && fsearch == p1first) //check if both first and last names correspond
                newresult.add(p1first, p1last, p1value); //then add to result
        }
    }
    result.swap(newresult); //store the final list in the list passed into result parameter
}



