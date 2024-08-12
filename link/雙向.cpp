template<class T>
struct DblChainNode 
{
    T data;
    DblChainNode<T>* next;
    DblChainNode<T>* prev;

    DblChainNode(const T& element) : data(element), next(NULL), prev(NULL) {}
};

template<class T>
class DblChain 
{
public:
    DblChain() : head(NULL), tail(NULL) {}
    
    ~DblChain() 
    {
        while (head != NULL) 
        {
            DblChainNode<T>* next = head->next;
            delete head;
            head = next;
        }
    }
    
    bool IsEmpty() const { return head == NULL; }

    // 插入操作
    void InsertAtHead(const T& element);
    void InsertAtPosition(const T& element, int position);
    void InsertAtTail(const T& element);

    // 刪除操作
    void DeleteHead();
    void DeleteAtPosition(int position);
    void DeleteTail();

private:
    DblChainNode<T>* head;
    DblChainNode<T>* tail;
};


// 插入操作實現
template<class T>
void DblChain<T>::InsertAtHead(const T& element) 
{
    DblChainNode<T>* newNode = new DblChainNode<T>(element);
    if (IsEmpty()) 
    {
        head = tail = newNode;
    } 
    else 
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

template<class T>
void DblChain<T>::InsertAtPosition(const T& element, int position) 
{
    if (position <= 0 || IsEmpty()) 
    {
        InsertAtHead(element);
        return;
    }

    DblChainNode<T>* current = head;
    for (int i = 1; i < position && current->next != NULL; i++) 
    {
        current = current->next;
    }

    DblChainNode<T>* newNode = new DblChainNode<T>(element);
    newNode->next = current->next;
    newNode->prev = current;

    if (current->next != NULL)
    {
        current->next->prev = newNode;
    } 
    else 
    {
        tail = newNode; // 如果插入位置在最後，更新尾指針
    }

    current->next = newNode;
}

template<class T>
void DblChain<T>::InsertAtTail(const T& element)
{
    DblChainNode<T>* newNode = new DblChainNode<T>(element);
    if (IsEmpty())
    {
        head = tail = newNode;
    } 
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// 刪除操作實現
template<class T>
void DblChain<T>::DeleteHead()
{
    if (IsEmpty()) return;

    DblChainNode<T>* temp = head;
    head = head->next;

    if (head != NULL)
    {
        head->prev = NULL;
    } 
    else
    {
        tail = NULL; // 如果刪除的是唯一節點，更新尾指針
    }

    delete temp;
}

template<class T>
void DblChain<T>::DeleteAtPosition(int position) 
{
    if (IsEmpty() || position < 0) return;

    if (position == 0) 
    {
        DeleteHead();
        return;
    }

    DblChainNode<T>* current = head;
    for (int i = 1; i < position && current->next != NULL; i++)
    {
        current = current->next;
    }

    if (current->next != NULL) 
    {
        DblChainNode<T>* temp = current->next;
        current->next = temp->next;

        if (temp->next != NULL) 
        {
            temp->next->prev = current;
        }
        else
        {
            tail = current; // 如果刪除位置在最後，更新尾指針
        }

        delete temp;
    }
}

template<class T>
void DblChain<T>::DeleteTail()
{
    if (IsEmpty()) return;

    if (tail->prev == NULL)
    {
        delete tail;
        head = tail = NULL;
    } 
    else 
    {
        DblChainNode<T>* temp = tail;
        tail = tail->prev;
        tail->next = NULL;
        delete temp;
    }
}
