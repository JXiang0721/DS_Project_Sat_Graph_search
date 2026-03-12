# Satellite Graph Search System (衛星圖形搜索系統)

這是一個基於 **C 語言** 開發的資料結構專題專案，旨在模擬並分析衛星網路的動態拓撲。系統透過讀取衛星軌道數據，建立鄰接鏈表（Adjacency List），並提供包含深度優先搜索（DFS）與最短路徑搜尋等多項分析功能。

---

##  系統功能

程式啟動時會隨機選擇一個當下時間（如 `2024-01-01 16:04:00`），並根據該時刻各衛星的空間位置自動建立鄰接鏈表。

# Satellite Graph Search System (衛星圖形搜索系統)

本專案為資料結構課程專題，實作一個動態衛星通訊網路模擬系統。透過 C 語言從底層建構圖形（Graph）結構，模擬衛星在特定時間點的空間分佈，並計算其連通性與最短傳輸路徑。

---

##  系統架構與流程 (System Architecture)

程式運行邏輯如下：
1. **初始化**：讀取衛星軌道數據，隨機選定模擬時間點。
2. **座標轉換**：將軌道參數轉換為三維空間座標 $(x, y, z)$。
3. **建構圖形**：計算兩兩衛星間的距離，若小於通訊閾值（Threshold），則建立邊（Edge）。
4. **互動模式**：提供使用者 5 種模式進行網路分析與搜尋。



---

##  資料結構定義 (Data Structures)

本專案核心使用 **鄰接鏈表 (Adjacency List)**，定義如下：

```c
// 節點結構：儲存鄰近衛星資訊
typedef struct node {
    int id;                 // 衛星編號
    double distance;        // 與主節點的距離
    struct node *next;      // 指向下一鄰居的指標
} Node;

// 圖形結構：管理所有衛星及其連線
typedef struct graph {
    int num_vertices;       // 總衛星數量
    Node **adj_lists;       // 鄰接鏈表陣列 (Array of Node pointers)
    int *visited;           // 用於走訪演算法的標記陣列
} Graph;
```
### 核心模式說明：

1. **Mode 1：全節點相對距離輸出** - 計算並列出網路中所有節點對之間的相對距離。
2. **Mode 2：鄰接鏈表可視化** - 以圖形化呈現鄰接鏈表的結構，展示各衛星節點的連接狀況。
3. **Mode 3：單一節點與其他節點距離** - 選取一節點，系統會顯示其與其相聯節點的距離。
4. **Mode 4：深度優先搜索 (DFS)** - 執行走訪路徑，展示網路的連通性。
5. **Mode 5：最短路徑搜尋** - 計算起始至目標節點間的最短路徑與總距離。

---

##  核心函式說明 (Function Details)

為了實現上述功能，本專案實作了以下核心函式：

### 1. 數據處理與初始化
* `load_sat_data()`: 負責從 `sat_data/` 目錄讀取衛星座標數據，並解析 CSV 或純文字檔。
* `calculate_distance()`: 輸入兩組 (x, y, z) 空間座標，利用歐幾里得距離公式計算衛星間的物理距離。

### 2. 圖形結構管理 (Graph Management)
* `create_node()`: 配置記憶體並初始化一個新的鄰接節點。
* `add_edge()`: 在鄰接鏈表中建立邊。若兩衛星距離小於通訊閾值，則判定為連通並加入鏈表。
* `print_adj_list()`: 遍歷整個 Adjacency List 陣列，將各節點及其鄰居以 `Node -> Neighbor` 的格式視覺化輸出。

### 3. 搜尋演算法
* `DFS_traversal()`: 
    * 使用遞迴或堆疊（Stack）實作。
    * 透過 `visited[]` 陣列記錄走訪狀態，避免無窮迴圈，用於檢查網路連通分量。
* `find_shortest_path()`: 
    * 實作 **Dijkstra 演算法**（未完成，使用 BFS 尋找路徑）。
    * 記錄路徑的前驅節點，最後透過回溯輸出完整的移動路徑與總成本。

---

##  執行畫面預覽

### 主選單與初始化
![Mode Selection](images/mode.png)
### 節點相對距離 (Mode 1)
![relative distance](images/relative_distance.png)
### 鄰接鏈表結構 (Mode 2)
![DFS](images/DFS.png)
### 鄰接鏈表結構 (Mode 4)
![Adjacency List](images/adj_list.png)
### 最短路徑搜尋結果 (Mode 5)
![Shortest Path Result](images/result.png)

---

##  技術要點

* **資料結構**：使用 **Adjacency List (鄰接鏈表)**，空間複雜度為 O(V+E)
* **動態記憶體管理**：嚴格控管 `malloc` 與 `free`，確保圖形動態更新時無記憶體洩漏（Memory Leak）。

---

##  如何編譯與執行

1. **編譯程式**：
   ```bash
   make
