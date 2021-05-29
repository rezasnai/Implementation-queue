#include <iostream>
#include <vector>
#include <regex>
#include<string>
using namespace std;
//create template for generalize the QUEUE
template<class T> class Queue;
template<class T> class Priority_queue;

///class node
template<class T>
class Node
{
    friend class Queue<T>; // this means queue class can acsess to private peraperties
    friend class Priority_queue<T>; // this means queue class can acsess to private peraperties
private:
    T data;
    Node *next;
    int priority;
    Node(T d,Node *n,int p=0);
};

template <class T>
Node<T>::Node(T d,Node *n,int p)
{
    data=d;
    next=n;
    priority=p;
}

///queue class
///this class has two peraperties
/// frist is pointer to first node in queue
/// rear is pointer to lastest node in queue
template<class T>
class Queue
{
protected:
    Node<T> *first;
    Node<T> *rear;
public:
    ///construtore
    Queue();
    ///add value to queue
    bool inQueue(T x);
    ///delete value from queue
    void deQueue();
    //display queue
    void Display() const;
    ///check is empty
    bool is_empty();
    ///search is queue
    int search_in_queue(const T key) const;
    ///merge two queue
    Queue<T> merge_two_queue(const Queue<T> &two) const;

    //overload = operator
    Queue<T> & operator=(const Queue<T> &two);

    void delete_queue();
    ~Queue();
};

template<class T>
Queue<T>::Queue()
{
    first=nullptr;
    rear=nullptr;
}
template<class T>
bool Queue<T>::inQueue(T x)
{
    Node<T> *new_node=new Node<T>(x,nullptr);
    if(!new_node)
        return false;
    if(first==nullptr)
        first=rear=new_node;
    else {
        rear->next=new_node;  /// el1(first) -> el2 -> el3(rear)
        rear=new_node;       ///  el1(first) -> el2 -> el3(rear) -> new el
                            ///   el1(first) -> el2 -> el3 -> new el(rear)
    }
    return true;
}//O(1) constant
template<class T>
void Queue<T>::deQueue()
{
    if(!is_empty())
    {
        Node<T> *p=first;
        first=first->next;
        if(first==nullptr)
            rear=nullptr;
        delete p;
    }
}//O(1) constant
template<class T>
void Queue<T>::Display() const
{
    cout<<endl<<
          "=================================="<<endl<<"[";
    Node<T> *curr=first;
    while (curr!=nullptr) {
        cout<<curr->data;
        if(curr->next!=nullptr)
            cout<<"  <-  ";
        curr=curr->next;
    }
    cout<<']'<<endl<<"=================================="<<endl;
}//O(n)
template<class T>
Queue<T>::~Queue()
{
    this->delete_queue();
}

template<class T>
void Queue<T>::delete_queue(){
    Node <T> *p;
    while (first!=nullptr) {
        p=first;
        first=first->next;
        delete p;
        p=nullptr;
    }
    first=rear=nullptr;
}///O(n)

///check is empty
template<class T>
bool Queue<T>::is_empty(){
    return first==nullptr;
}

///search is queue
template<class T>
int Queue<T>::search_in_queue(const T key) const{
    Node<T> *curr=first;
    int index;
    for(index=1 ;  curr!=nullptr ; index++) // if zero base => index brgin from 0
    {
        if(curr->data==key)
            return index;
        curr=curr->next;
    }
    return '\0';
}///O(n)

///merge two queue
template<class T>
Queue<T> Queue<T>::merge_two_queue(const Queue<T> &two) const {
    Queue<T> result;
    Node<T> *curr=this->first;
    while (curr!=nullptr) {
        result.inQueue(curr->data);
        curr=curr->next;
    }
    curr=two.first;
    while (curr!=nullptr) {
        result.inQueue(curr->data);
        curr=curr->next;
    }


    return result;
}///O(n+m) ==> O(n)


//overload = operator
template <class T>
Queue<T> & Queue<T>::operator=(const Queue<T> &two){
    if(this!=&two){
        this->delete_queue();
        Node<T> *curr=two.first;
        while (curr!=nullptr) {
            this->inQueue(curr->data);
            curr=curr->next;
        }
    }
    return *this;
}///O(n)

///end of class Queue

template<class T>
class Priority_queue : public Queue<T>{
public:
    ///construtore
    Priority_queue();
    ///add value to queue
    bool inQueue(T x, int priority);
    //display queue
    void Display() const;
    ///merge two queue
    Priority_queue<T> merge_two_priority_queue(const Priority_queue<T> &two) const;
    //overload = operator
    Priority_queue<T> & operator=(const Priority_queue<T> &two);
    ~Priority_queue();
};

template<class T>
Priority_queue<T>::Priority_queue()
    :Queue<T>(){}

template<class T>
Priority_queue<T>::~Priority_queue(){
    this->delete_queue();
}


///add value to queue
template<class T>
bool Priority_queue<T>::inQueue(T x,int priority){
    Node<T> *new_node=new Node<T>(x,nullptr,priority);
    if(!new_node)
        return false;
    //special case : the head of list is null
    if(Queue<T>::first==nullptr)
    {
        Queue<T>::first=Queue<T>::rear=new_node;
        return true;
    }
    // Special Case: The head of list has
    // lesser priority than new node. So
    // insert newnode before head node
    // and change head node.
    if (Queue<T>::first -> priority < priority)
    {

        // Insert New Node before head
        new_node->next = Queue<T>::first;
        Queue<T>::first = new_node;
    }
    else
    {

        // Traverse the list and find a
        // position to insert new node
        Node<T> *curr=Queue<T>::first;
        while (curr->next != NULL &&
            curr->next->priority > priority)
        {
            curr = curr->next;
        }

        // Either at the ends of the list
        // or at required position
        //el1(rear) <- el2 <- el4(first)
        //el3
        new_node->next = curr->next;
        curr->next = new_node;
        //el1(rear) <- el2 <- el3 <- el4(first)
    }
    return true;
}//O(n)

//display queue
template<class T>
void Priority_queue<T>::Display() const{
    cout<<endl<<
          "=================================="<<endl<<"[";
    Node<T> *curr=Queue<T>::first;
    while (curr!=nullptr) {
        cout<<curr->data<<" , priority : "<<curr->priority;
        if(curr->next!=nullptr)
            cout<<"  <-  ";
        curr=curr->next;
    }
    cout<<']'<<endl<<"=================================="<<endl;
}//O(n)

///merge two queue
template<class T>
Priority_queue<T> Priority_queue<T>::merge_two_priority_queue(const Priority_queue<T> &two) const
{
    Priority_queue<T> result;
    Node<T> *curr=this->first;
    while (curr!=nullptr) {
        result.inQueue(curr->data,curr->priority);
        curr=curr->next;
    }
    curr=two.first;
    while (curr!=nullptr) {
        result.inQueue(curr->data,curr->priority);
        curr=curr->next;
    }
    return result;
}//O(n+m) == O(n)

template<class T>
Priority_queue<T>& Priority_queue<T>::operator=(const Priority_queue<T> &two){
    if(this!=&two){
        this->delete_queue();
        Node<T> *curr=two.first;
        while (curr!=nullptr) {
            this->inQueue(curr->data,curr->priority);
            curr=curr->next;
        }
    }
    return *this;
}//O(n)


void intro(){
    cout<<"========================================="<<endl;
    cout<<"*     COPY RIGHT BY REZA ZANGANE SANI   *"<<endl<<
          "*      Group members                    *"<<endl<<
          "*      1.Mostafa Binesh                 *"<<endl<<
          "*      2.Seyed Saeid Heidari            *"<<endl<<
          "*      3.Omid Rahimi                    *"<<endl<<
          "*      4.Ali Afroozi                    *"<<endl<<
          "*      Queue implementation Project     *"<<endl;
    cout<<"========================================="<<endl;
}

int main()
{
    ///test program
    //normal queue
    //string type
    Queue<string> Q1,Q2,Merge;
    Q1.inQueue("Farvardin");
    Q1.inQueue("Ordibehasht");
    Q1.inQueue("Khordad");
    cout<<"Queue Q1";
    Q1.Display();

    cout<<endl<<"index of Khordad in Q1 : "<<Q1.search_in_queue("Khordad")<<endl;


    cout<<endl<<"deQueue From Q1";
    Q1.deQueue();
    Q1.Display();

    Q2.inQueue("Tir");
    Q2.inQueue("Mordad");
    Q2.inQueue("Sharivar");
    cout<<endl<<"Queue Q2";
    Q2.Display();

    Merge=Q1.merge_two_queue(Q2);

    cout<<endl<<"Merge";
    Merge.Display();

    //priority queue
    Priority_queue<int> Q3,Q4,merge;
    Q3.inQueue(10,0);
    Q3.inQueue(8,2);
    Q3.inQueue(9,1);
    cout<<endl<<"Priority Queue Q3";
    Q3.Display();

    cout<<endl<<"index of 9 in Q3 : "<<Q3.search_in_queue(9)<<endl;


    cout<<endl<<"deQueue From Q3";
    Q3.deQueue();
    Q3.Display();


    Q4.inQueue(8,2);
    Q4.inQueue(7,3);
    Q4.inQueue(6,4);
    Q4.inQueue(5,5);
    cout<<endl<<"Priority Queue Q4";
    Q4.Display();

    merge=Q3.merge_two_priority_queue(Q4);

    cout<<endl<<"merge";
    merge.Display();


    cout<<endl<<endl;
    intro();

//    int *p;
//    cout<<sizeof (p);

    // n el ==> n*(node.size) ==> O(n)
    return 0;
}


