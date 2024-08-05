1  SparseMatrix SparseMatrix::Transpose()//定義了SparseMatrix類的成員函數
2  { 
3      SparseMatrix b(cols, rows, terms); // 創建一個新的SparseMatrix對象b，其行數和列數與當前矩陣的相反。這個新矩陣的容量（非零元素的數量）與原矩陣相同
4      if (terms > 0)//檢查矩陣是否為非零矩陣
5      { 
6          int currentB = 0;//初始化變量currentB，用於跟踪轉置後矩陣中的當前元素位置。
7          for (int c = 0; c < cols; c++) // 遍歷原矩陣的每一列
8              for (int i = 0; i < terms; i++)//原矩陣的每一個非零元素
9                 
10                 if (smArray[i].col == c)//檢查第i個非零元素是否在第c列。如果是，則執行轉置操作
11                 {
12                     b.smArray[currentB].row = c;//將轉置後矩陣中的當前元素的行設置為c
13                     b.smArray[currentB].col = smArray[i].row;//將轉置後矩陣中的當前元素的列設置為原矩陣中對應元素的行
14                     b.smArray[currentB++].value = smArray[i].value;//將轉置後矩陣中的當前元素的值設置為原矩陣中對應元素的值，並更新currentB
15                 }
16         }
17     return b;
18 }//整體時間複雜度為 O(cols * terms)





//其他

1  SparseMatrix SparseMatrix::FastTranspose()
2  { 
3      SparseMatrix b(cols, rows, terms);
4      if (terms > 0)
5      { 
6          int *rowSize = new int[cols];//分別創建兩個動態數組，rowSize用於存儲轉置後每一行中元素的數量
7          int *rowStart = new int[cols];//rowStart用於存儲轉置後每一行的起始位置。
8          
9          fill(rowSize, rowSize + cols, 0);  //初始化rowSize數組，將所有元素設置為0
10         for (i = 0; i < terms; i++) rowSize[smArray[i].col]++;//遍歷原矩陣的每一個非零元素，計算每一列中元素的數量並更新rowSize數組。
11        
12         rowStart[0] = 0;
13         for (i = 1; i < cols; i++) rowStart[i] = rowStart[i - 1] + rowSize[i - 1];//計算轉置後每一行的起始位置。      
14         for (i = 0; i < terms; i++)//遍歷原矩陣的每一個非零元素，並將其放置在轉置後的矩陣中。
15         { 
16             int j = rowStart[smArray[i].col];//獲取轉置後矩陣中對應位置的索引
17             b.smArray[j].row = smArray[i].col;//將轉置後矩陣中的行設置為原矩陣中的列。
18             b.smArray[j].col = smArray[i].row;//將轉置後矩陣中的列設置為原矩陣中的行。
19             b.smArray[j].value = smArray[i].value;//將轉置後矩陣中的值設置為原矩陣中的值。
20             rowStart[smArray[i].col]++;//數組中對應列的起始位置。
21         } 
22         delete[] rowSize;//釋放動態分配的內存。
23         delete[] rowStart;
24     } 
25     return b;
26 }//整體時間複雜度為 O(terms + cols)
