template<class T>
struct DblChainNode 
{
    T data;
    DblChainNode<T>* next;//指向鏈表中下一個節點的指針。實現向前遍歷的功能。
    DblChainNode<T>* prev;//指向鏈表中前一個節點的指針。實現向後遍歷的功能。

    //初始化節點。
    DblChainNode(const T& element) : data(element), next(NULL), prev(NULL) {}
};

template<class T>
class DblChain 
{
public:
    DblChain() : head(NULL), tail(NULL) {}//初始化鏈表。head 和 tail 指針都被初始化為 NULL，表示鏈表一開始是空的。
    
    ~DblChain() //解構函數，用於清理資源，防止內存洩漏。
    {
        while (head != NULL) 
        {
            DblChainNode<T>* next = head->next;//當前 head 節點的下一個節點賦值給 next 指針。
            delete head;//刪除當前的 head 節點，釋放它佔用的記憶體。
            head = next;//head 指針更新為 next，指向下一個節點。
        }
    }
    
    bool IsEmpty() const { return head == NULL; }//如果 head 為 NULL，則表示鏈表為空，函數返回 true，否則返回 false。

    // 插入操作
    void InsertAtHead(const T& element);
    void InsertAtPosition(const T& element, int position);
    void InsertAtTail(const T& element);

    // 刪除操作
    void DeleteHead();
    void DeleteAtPosition(int position);
    void DeleteTail();

private:
    DblChainNode<T>* head;//指向鏈表的第一個節點。head 用來管理鏈表的起始位置。
    DblChainNode<T>* tail;//指向鏈表的最後一個節點。tail 用來管理鏈表的結束位置。
};


// 插入操作實現
template<class T>
void DblChain<T>::InsertAtHead(const T& element) 
{
    DblChainNode<T>* newNode = new DblChainNode<T>(element);//這行代碼創建了一個新節點，資料初始化為 element。newNode 是指向這個新節點的指針。
    if (IsEmpty()) //如果鏈表為空
    {
        head = tail = newNode;//將 head 和 tail 都設置為新節點 newNode。同時是頭節點也是尾節點。
    } 
    else 
    {
        newNode->next = head;//新節點的 next 指針設置為當前的 head 節點
        head->prev = newNode;//原來的頭節點的 prev 指針設置為新節點
        head = newNode;//head 指針更新為新節點 newNode
    }
}

template<class T>
void DblChain<T>::InsertAtPosition(const T& element, int position) 
{
    //如果插入位置小於等於 0 或者鏈表為空，則調用 InsertAtHead(element) 。
    if (position <= 0 || IsEmpty()) 
    {
        InsertAtHead(element);
        return;
    }

    DblChainNode<T>* current = head;//初始化 current 指針，指向鏈表的第一個節點
    for (int i = 1; i < position && current->next != NULL; i++) //遍歷鏈表，以找到插入位置的前一個節點
    {
        current = current->next;//current 指針移動到鏈表中的下一個節點
    }

    DblChainNode<T>* newNode = new DblChainNode<T>(element);
    newNode->next = current->next;//新節點的 next 指針設置為 current 節點的下一個節點，這樣新節點的 next 指針指向插入位置的後一個節點。
    newNode->prev = current;//rev 指針設置為 current 節點，這樣新節點的 prev 指針指向插入位置的前一個節點。

    if (current->next != NULL)//如果不是 NULL，表示插入的位置在鏈表中間，則需要更新插入位置後一個節點的 prev 指針
    {
        current->next->prev = newNode;//prev 指針設置為新節點，這樣新節點成為插入位置後一個節點的前一個節點。
    } 
    else //current->next 為 NULL，表示插入的位置在鏈表的尾部
    {
        tail = newNode; // 更新 tail 指針，將其指向新節點，因為新節點現在成為鏈表的最後一個節點。
    }

    current->next = newNode;//current 節點的 next 指針設置為新節點
}

template<class T>
void DblChain<T>::InsertAtTail(const T& element)
{
    DblChainNode<T>* newNode = new DblChainNode<T>(element);
    if (IsEmpty())//如果鏈表為空
    {
        head = tail = newNode;//將 head 和 tail 都設置為新節點 newNode。是頭節點也是尾節點。
    } 
    else
    {
        tail->next = newNode;//尾節點的 next 指針設置為新節點 newNode
        newNode->prev = tail;//prev 指針設置為當前尾節點
        tail = newNode;//tail 指針更新為新節點 newNode
    }
}

// 刪除操作實現
template<class T>
void DblChain<T>::DeleteHead()
{
    if (IsEmpty()) return;//如果鏈表為空，不進行任何操作。

    DblChainNode<T>* temp = head;//將 head 指針的值賦值給 temp，用於保存要刪除的節點。
    head = head->next;//head 指針更新為當前頭節點的下一個節點

    if (head != NULL)//如果 head 不為 NULL
    {
        head->prev = NULL;//prev 指針設置為 NULL，因為新的頭節點已經沒有前一個節點。
    } 
    else//如果 head 為 NULL，表示鏈表中只有一個節點，這個節點被刪除後鏈表變空
    {
        tail = NULL; // tail 指針設置為 NULL，因為鏈表已經沒有尾節點。
    }

    delete temp;//釋放 temp 指針所指向的節點的記憶體
}

template<class T>
void DblChain<T>::DeleteAtPosition(int position) 
{
    if (IsEmpty() || position < 0) return;//如果鏈表為空，或者 position 是一個無效的負數，不進行任何操作。

    if (position == 0) //如果指定的位置是 0，表示要刪除鏈表的頭節點：
    {
        DeleteHead();
        return;
    }

    DblChainNode<T>* current = head;//初始化 current 指針，指向鏈表的第一個節點
    for (int i = 1; i < position && current->next != NULL; i++)//遍歷鏈表，以找到要刪除節點的前一個節點
    {
        current = current->next;//current 指針移動到鏈表中的下一個節點
    }

    if (current->next != NULL) //如果不為 NULL，表示可以進行刪除
    {
        DblChainNode<T>* temp = current->next;//current 的下一個節點賦值給 temp 指針。
        current->next = temp->next;//current 節點的 next 指針更新為 temp 節點的下一個節點

        if (temp->next != NULL) //如果不為 NULL，表示 temp 節點不是尾節點
        {
            temp->next->prev = current;//temp 節點的下一個節點的 prev 指針設置為 current，這樣 current 就成為 temp 節點的下一個節點的前一個節點。
        }
        else//temp 節點是尾節點
        {
            tail = current; // 更新 tail 指針，使其指向 current 節點，因為刪除後 current 節點成為新的尾節點。
        }

        delete temp;//釋放 temp 指針所指向的節點的記憶體
    }
}

template<class T>
void DblChain<T>::DeleteTail()
{
    if (IsEmpty()) return;

    if (tail->prev == NULL)//如果prev 指針為 NULL，表示鏈表中只有一個節點：
    {
        delete tail;//刪除這個唯一的節點，釋放其佔用的記憶體。
        head = tail = NULL;//head 和 tail 指針都設置為 NULL，表示鏈表現在已經變空。
    } 
    else 
    {
        DblChainNode<T>* temp = tail;//tail 指針當前指向的節點賦值給 temp，用於保存要刪除的節點。
        tail = tail->prev;//tail 指針更新為當前尾節點的前一個節點。這樣，新的尾節點就變為原來的尾節點的前一個節點。
        tail->next = NULL;//新的尾節點的 next 指針設置為 NULL
        delete temp;//釋放 temp 指針所指向的節點的記憶體
    }
}
