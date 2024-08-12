template<class T>
struct ChainNode 
{
    T data;
    ChainNode<T>* link;

    ChainNode(const T& element) : data(element), link(NULL) {}
};

template<class T>
class Chain 
{
public:
    Chain() {first = 0;}
    ~Chain() 
    {
        while (first != NULL) 
        {
            ChainNode<T>* next = first->link;
            delete first;
            first = next;
        }
    }
    
    bool IsEmpty() const {return first == 0;}

    // 插入操作
    void InsertAtHead(const T& element);
    void InsertAtPosition(const T& element, int position);
    void InsertAtTail(const T& element);

    // 刪除操作
    void DeleteHead();
    void DeleteAtPosition(int position);
    void DeleteTail();

private:
    ChainNode<T>* first;
};


// 插入操作實現
template<class T>
void Chain<T>::InsertAtHead(const T& element) 
{
    ChainNode<T>* newNode = new ChainNode<T>(element);
    newNode->link = first;
    first = newNode;
}

template<class T>
void Chain<T>::InsertAtPosition(const T& element, int position) 
{
    if (position <= 0) 
    {
        InsertAtHead(element);
        return;
    }

    ChainNode<T>* current = first;
    for (int i = 1; i < position && current != NULL; i++) 
    {
        current = current->link;
    }

    if (current != NULL) 
    {
        ChainNode<T>* newNode = new ChainNode<T>(element);
        newNode->link = current->link;
        current->link = newNode;
    }
}

template<class T>
void Chain<T>::InsertAtTail(const T& element) 
{
    ChainNode<T>* newNode = new ChainNode<T>(element);
    if (IsEmpty()) 
    {
        first = newNode;
    } 
    else 
    {
        ChainNode<T>* current = first;
        while (current->link != NULL) 
        {
            current = current->link;
        }
        current->link = newNode;
    }
}


// 刪除操作實現
template<class T>
void Chain<T>::DeleteHead() 
{
    if (IsEmpty()) return;

    ChainNode<T>* temp = first;
    first = first->link;
    delete temp;
}

template<class T>
void Chain<T>::DeleteAtPosition(int position) 
{
    if (IsEmpty() || position < 0) return;

    if (position == 0) 
    {
        DeleteHead();
        return;
    }

    ChainNode<T>* current = first;
    for (int i = 1; i < position && current->link != NULL; i++) 
    {
        current = current->link;
    }

    if (current->link != NULL) 
    {
        ChainNode<T>* temp = current->link;
        current->link = temp->link;
        delete temp;
    }
}

template<class T>
void Chain<T>::DeleteTail() 
{
    if (IsEmpty()) return;

    if (first->link == NULL)
    {
        delete first;
        first = NULL;
    }
    else
    {
        ChainNode<T>* current = first;
        while (current->link->link != NULL)
        {
            current = current->link;
        }
        delete current->link;
        current->link = NULL;
    }
}
