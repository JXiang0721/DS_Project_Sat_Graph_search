#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graph.h"
#include <limits.h>


Graph* creategraph(int node_site)
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->graph_id = node_site;

    graph->visited = (int*)malloc(node_site * sizeof(int));
    graph->distance = (int*)malloc(node_site * sizeof(int));
    
    graph->adjList = (Node**)malloc(node_site * sizeof(Node*));
    for (int i = 0; i < node_site; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
        graph->distance[i] = infinity;
    }

    return graph;
}

void read_txt(const char* filename, Node* node, int txt_line, int i)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Can't open %s!!\n", filename);    //檔案無法打開
        return;
    }

    /*跳過第前面的行數*/
    char skipLine[256];
    for(int line_num = 1 ; line_num < txt_line ; ++line_num)
    {
            if (fgets(skipLine, sizeof(skipLine), file) == NULL){
                fclose(file);
                return;
            }
    }
    
    /*存入節點*/
    while (fgets(skipLine, sizeof(skipLine), file) != NULL){
        if (sscanf(skipLine, "%2s %3s %4s %13s %lf %lf %lf", node->dd, node->MM, 
                    node->yy, node->date, &node->x, &node->y, &node->z) != 7){
            printf("Error data number!! %s\n", filename);   //資料數量不一致
            fclose(file);
            return;
        }
        node->node_site = i;
        fclose(file);
        break;
    }
    
}

void create_adjlist(Graph* graph, Node* node_head)
{   
    Node *currentN, *prev, *other_node;
    currentN = node_head->next;
    
    while (currentN != node_head) {
        other_node = node_head->next;

        while(other_node != node_head){
            if (other_node->node_site != currentN->node_site) {  // 不要和自己比較
                double distance = sqrt(pow(currentN->x - other_node->x, 2) +
                                       pow(currentN->y - other_node->y, 2) +
                                       pow(currentN->z - other_node->z, 2));

                if (distance <= EDGE_DISTANCE) {
                    // 創建開始節點到結束節點的邊
                    Node* startNode = (Node*)malloc(sizeof(Node));
                    startNode->node_site = other_node->node_site;
                    startNode->next = graph->adjList[currentN->node_site];
                    graph->adjList[currentN->node_site] = startNode;
                }
            }
            other_node = other_node->next;
        }
        currentN = currentN->next;
    }
}

void printAdjList(Graph* graph)
{
     for (int i = 0; i < graph->graph_id; i++) {
        printf("Sat%d's Adjlist: \n", i+1);

        Node* current = graph->adjList[i];
        while (current != NULL) {
            printf("Sat%d -> ", current->node_site);
            current = current->next;
        }

        printf("NULL\n\n");
    }
    
}

void sat_distance(Graph* graph, Node* node_head)
{   
    Node *currentN, *prev, *other_node;
    currentN = node_head->next;
    
    while (currentN != node_head) {
        other_node = node_head->next;

        while(other_node != node_head){
            if (other_node->node_site != currentN->node_site) {  // 不要和自己比較
                double distance = sqrt(pow(currentN->x - other_node->x, 2) +
                                       pow(currentN->y - other_node->y, 2) +
                                       pow(currentN->z - other_node->z, 2));
                printf("Sat%03d -> Sat%03d   %13lf km\n",currentN->node_site, other_node->node_site, distance);

            }
            other_node = other_node->next;
        }
        currentN = currentN->next;
    }
}

void Selected_sat_distance(Graph* graph, Node* node_head, int selected_Sat)
{   
    
    Node *currentN, *prev, *other_node;
    double distance;
    // 移動到第 selected_Sat 個節點
    currentN = node_head->next;
    for (int i = 0; i < selected_Sat-1 && currentN != node_head; ++i) {
        currentN = currentN->next;
    }

    other_node = node_head->next;
    while(other_node != node_head){
        if (other_node->node_site != currentN->node_site) {  // 不要和自己比較
            distance = sqrt(pow(currentN->x - other_node->x, 2) +
                                pow(currentN->y - other_node->y, 2) +
                                pow(currentN->z - other_node->z, 2));
            if( distance<EDGE_DISTANCE)
                printf("Sat%03d -> Sat%03d   %13lf km\n",currentN->node_site,other_node->node_site, distance);

        }
        other_node = other_node->next;
    }
   
}

void init(Graph* graph) {
    for (int i = 0; i < graph->graph_id; i++) { // 初始化 visited 陣列
        graph->visited[i] = 0;
        graph->distance[i] = infinity;  
    }
}

void DFS(Graph* graph, int vertex) {
    Node* adjList = graph->adjList[vertex];
    Node* temp = adjList;

    graph->visited[vertex] = 1;
    printf("Visited %d \n", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->node_site;

        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        
        temp = temp->next;
    }
}

void dijkstra(double edge[SAT_NUM+1][SAT_NUM+1], int start,int end) {
    int cost[MAX+1][MAX+1], distance[MAX+1], pred[MAX+1];
    int visited[MAX+1], count, mindistance, nextnode, i, j;
    int pathNodes[MAX + 1];
    int pathDistance[MAX + 1];

    for (i = 1; i < MAX+1; i++){// 先篩選，若兩點間距離大於極限，則設為0
        for (j = 1; j < MAX+1; j++){
            if (edge[i][j] > EDGE_DISTANCE){
                edge[i][j]=0;
            }
        }
    }
    
    // 成本矩陣
    for (i = 0; i < MAX+1; i++){
        for (j = 0; j < MAX+1; j++){
            if (edge[i][j] == 0){//若距離為0，則代表兩點不可能相通，距離設為無限
                cost[i][j] = infinity;
            }
            else{
                cost[i][j] = edge[i][j];
        }
        }

    }

    //初始化
    for (i = 1; i < MAX+1; i++) {
        distance[i] = cost[start][i];//起點到該節點的距離
        pred[i] = start;
        visited[i] = 0;
        pathNodes[i]=-1;
        pathDistance[i]=-1;
    }
    distance[start] = 0;
    visited[start] = 1;
    

   
    //上面進行初始化，以下為演算法
    for(int time=0; time<MAX+1;time++) {
        int mindistance = infinity;
       
        for (i = 1; i < MAX+1; i++) //找最短
        if (distance[i] < mindistance && !visited[i]) {
            mindistance = distance[i];
            nextnode = i;
        }//此時 mindistance為最近的"未探訪過"節點的距離，而nextnode為其所引

        visited[nextnode] = 1;
        for (i = 1; i < MAX+1; i++)
        if (!visited[i])//更新到i點的最短距離
            if (mindistance + cost[nextnode][i] < distance[i]) {
                distance[i] = mindistance + cost[nextnode][i];
                pred[i] = nextnode;//若成功更新則記錄該點  
            }
    }
    

    //印出
    for (i = 1; i < MAX + 1; i++) {
        if (i == end && distance[i] < INFINITY) {
            printf("\nShortest Distance from %d to %d: %d", start, end, distance[i]);

            // 從終點回溯找出經過節點
            int node = end;
            int count = 0;

            while (node != start) {
                pathNodes[count] = node;
                pathDistance[count]=distance[node]-distance[pred[node]];
                node = pred[node];
                count++;
            }

            // 输出最短路径上的節點
            printf("\nShortest Path: %d -> ",start);
            for (int j = count - 1; j >= 0; j--) {
                printf("%d", pathNodes[j]);
                if (j > 0) {
                    printf(" -> ");
                }
            }printf("\n");
            
            // 输出最短路径上節點間的距離
            printf("\ndistance: ");
            for (int j = count - 1; j >= 0; j--) {
                printf("%d", pathDistance[j]);
                if (j > 0) {
                    printf(" -> ");
                }
            }printf("\n");
        }
    }
    
}

void Create_Edge(Graph* graph, Node* node_head, double edge[SAT_NUM+1][SAT_NUM+1])
{   

    Node *currentN, *prev, *other_node;
    currentN = node_head->next;


    while (currentN != node_head) {
        other_node = node_head->next;

        while(other_node != node_head){
            if (other_node->node_site != currentN->node_site) {  // 不要和自己比較
                double distance = sqrt(pow(currentN->x - other_node->x, 2) +
                                       pow(currentN->y - other_node->y, 2) +
                                       pow(currentN->z - other_node->z, 2));
                edge[currentN->node_site][other_node->node_site] = distance;
                //printf("Sat%03d -> Sat%03d   %13lf km\n",currentN->node_site, other_node->node_site, edge[currentN->node_site][other_node->node_site]);
            }
            other_node = other_node->next;
        }
        currentN = currentN->next;
    }

}



