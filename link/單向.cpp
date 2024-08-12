template<class T>
struct ChainNode //定義了一個結構體
{
    T data;//存儲鏈結點中的數據
    ChainNode<T>* link;//指向鏈表中的下一個結點。如果這個結點是鏈表的最後一個結點，則 link 將為 NULL。

    //初始化結點。它接受一個常量引用 element 作為參數，並將 data 成員初始化為該 element 的值，link 則初始化為 NULL。
    ChainNode(const T& element) : data(element), link(NULL) {}
};

template<class T>
class Chain 
{
public:
    Chain() {first = 0;}//默認構造函數，創建 Chain時，first 指針初始化為 0（即 NULL），表示鏈表開始時是空的。

    //這是解構函數，用於釋放鏈表中的記憶體資源。在這個函數中，有一個 while 迴圈，不斷刪除鏈表中的每個節點，直到所有節點都被刪除
    ~Chain() 
    {
        while (first != NULL) 
        {
            ChainNode<T>* next = first->link;//保存當前 first 節點的下一個節點。
            delete first;//刪除當前 first 節點。
            first = next;//將 first 指針移動到下一個節點
        }
    }
    //檢查鏈表是否為空。當 first 指針為 0（即 NULL）時，表示鏈表為空。
    bool IsEmpty() const {return first == 0;}

    // 插入操作
    void InsertAtHead(const T& element);//開頭插入一個新節點
    void InsertAtPosition(const T& element, int position);//指定位置插入一個新節點，position 表示插入的位置。
    void InsertAtTail(const T& element);//末尾插入一個新節點

    // 刪除操作
    void DeleteHead();//刪除鏈表的開頭節點。
    void DeleteAtPosition(int position);//刪除鏈表中指定位置的節點
    void DeleteTail();//刪除鏈表的末尾節點

private:
    ChainNode<T>* first;//指向鏈表中第一個節點的指針。鏈表的操作都以這個指針為起點進行。
};


// 插入操作實現
template<class T>
void Chain<T>::InsertAtHead(const T& element) 
{
    ChainNode<T>* newNode = new ChainNode<T>(element);//創建了一個新的 ChainNode 節點
    newNode->link = first;//新創建的節點的 link 指針指向當前鏈表的第一個節點
    first = newNode;//更新 first 指針，使其指向新的節點
}

template<class T>
void Chain<T>::InsertAtPosition(const T& element, int position) 
{
    if (position <= 0) //如果插入位置 position 小於或等於 0，這表示插入位置無效或是鏈表的開頭
    {
        InsertAtHead(element);
        return;
    }

    ChainNode<T>* current = first;//初始化 current 指針，指向鏈表的第一個節點
    for (int i = 1; i < position && current != NULL; i++) //遍歷鏈表，以找到插入位置的前一個節點。或者 current 指針變為 NULL（即鏈表末尾）。
    {
        current = current->link;//將 current 指針移動到鏈表中的下一個節點。
    }

    if (current != NULL) //果不是 NULL，則表示找到了插入位置的前一個節點，接下來可以進行插入操作。
    {
        ChainNode<T>* newNode = new ChainNode<T>(element);
        newNode->link = current->link;//新節點的 link 指針指向 current 節點的下一個節點。
        current->link = newNode;//將 current 節點的 link 指針更新為新節點
    }
}

template<class T>
void Chain<T>::InsertAtTail(const T& element) 
{
    ChainNode<T>* newNode = new ChainNode<T>(element);
    if (IsEmpty()) //如果鏈表為空
    {
        first = newNode;//直接將 first 指針設置為新節點，這樣新節點成為鏈表的唯一節點，也是鏈表的第一個節點和最後一個節點。
    } 
    else 
    {
        ChainNode<T>* current = first;//初始化 current 指針，指向鏈表的第一個節點。
        while (current->link != NULL) //使用 while 迴圈遍歷鏈表，找到鏈表的最後一個節點
        {
            current = current->link;//將 current 指針移動到鏈表中的下一個節點，直到找到最後一個節點。
        }
        current->link = newNode;//link 指針指向新節點，將新節點插入到鏈表的末尾。
    }
}


// 刪除操作實現
template<class T>
void Chain<T>::DeleteHead() 
{
    if (IsEmpty()) return;//如果鏈表為空（即 first 為 NULL），則沒有節點可以刪除，因此直接返回，不執行後續的刪除操作。

    ChainNode<T>* temp = first;//將 first 指針所指向的第一個節點賦值給 temp 指針。這樣 temp 就成為了指向即將被刪除的節點的指針。
    first = first->link;//first 指針更新為指向原來的第一個節點的下一個節點
    delete temp;//刪除 temp 指針所指向的節點，釋放這個節點佔用的記憶體
}

template<class T>
void Chain<T>::DeleteAtPosition(int position) 
{
    if (IsEmpty() || position < 0) return;//如果鏈表為空或位置無效，直接返回而不執行任何操作。

    if (position == 0) //如果要刪除的節點是鏈表的第一個節點（位置為 0），則調用 DeleteHead() 。
    {
        DeleteHead();
        return;
    }

    ChainNode<T>* current = first;
    for (int i = 1; i < position && current->link != NULL; i++) //遍歷鏈表，以找到要刪除位置的前一個節點
    {
        current = current->link;//指針移動到鏈表中的下一個節點。
    }

    if (current->link != NULL) //如果不是 NULL，表示找到了要刪除的節點（即 current->link），可以進行刪除操作。
    {
        ChainNode<T>* temp = current->link;//將 current->link 所指向的節點賦值給 temp 指針。
        current->link = temp->link;//更新 current 節點的 link 指針，使其指向 temp 節點的下一個節點
        delete temp;//釋放這個節點佔用的記憶體。
    }
}

template<class T>
void Chain<T>::DeleteTail() 
{
    if (IsEmpty()) return;

    if (first->link == NULL)//如果 first 節點的 link 為 NULL，表示鏈表中只有一個節點。
    {
        delete first;//刪除 first 節點，釋放它佔用的記憶體。
        first = NULL;//將 first 設為 NULL，表示鏈表現在為空。
    }
    else
    {
        ChainNode<T>* current = first;
        while (current->link->link != NULL)//遍歷鏈表，找到倒數第二個節點。即 current 的下一個節點
        {
            current = current->link;//current 指針移動到鏈表中的下一個節點
        }
        delete current->link;//刪除 current 的 link 指針所指向的節點，即最後一個節點，釋放它佔用的記憶體。
        current->link = NULL;//將倒數第二個節點的 link 指針設為 NULL，這樣它就成為新的尾節點。
    }
}
