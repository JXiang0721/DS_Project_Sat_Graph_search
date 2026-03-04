/*資料結構 期末專題*/
/*名稱 : 使用圖狀資料結構模擬*/
/*組員 : 太空三 110607508 吳嘉祥 && 太空三 110607513 許柏弘*/
/*執行請輸入 : 
gcc -o main main.c graph.c
.\main

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "graph.h"

int main()
{   
    /*初始化圖*/
    Graph* graph = creategraph(SAT_NUM);

    int txt_line;
    srand(time(NULL));
    txt_line = rand() % SAT_LINE;
   
    Node* node_head = (Node*)malloc(sizeof(Node));
    Node *currentN, *prev;
    prev = node_head;
    node_head->next = node_head;

    /*讀取所有檔案*/
    for (int i = 1; i <= SAT_NUM; i++) {
        char filename[40];
        sprintf(filename, "../sat_data/starlink_distance%03d.txt",i);
        Node* newNode = (Node*)malloc(sizeof(Node));
        
        /*存入節點*/
        read_txt(filename, newNode, txt_line, i);
        newNode->next = prev->next;
        prev->next = newNode;
        prev = newNode;
    }
    printf("\nAll Flies are stored!\n");
    printf("Choise Date : %s %s %s %s\n",prev->MM, prev->dd, prev->yy, prev->date);

    /*建立鄰接鏈表*/
    create_adjlist(graph, node_head);
    double edge[SAT_NUM+1][SAT_NUM+1] = {{0}};
    Create_Edge(graph, node_head, edge);

    static int mode, start,end;
    printf("Choice mode : ");
    while (1)
    {
        printf("\n *******************\n");
        printf("     1. print_sat_distance\n");
        printf("     2. print_AdjList\n");
        printf("     3. Selected_sat_distance\n");
        printf("     4. DFS\n");
        printf("     5. Dijkstra\n");
        printf("     6. Quit\n");
        printf(" *******************\n");
        printf(" Enter your mode(1-6): ");
        scanf("%d",&mode);
        switch(mode)
        {
            case 1:
                sat_distance(graph, node_head);
                break;
            case 2:
                printAdjList(graph);
                //
                break;
            case 3:
                printf("Select one Sat: ");
                scanf("%d",&mode);
                Selected_sat_distance(graph,node_head,mode);
                break;
            case 4:
                printf("Select one Sat for DFS: ");
                scanf("%d",&mode);
                init(graph); 
                DFS(graph, mode);
                break;
            case 5:
                printf("Select one Start for dijkstra: ");
                scanf("%d",&start);
                printf("Select one End for dijkstra: ");
                scanf("%d",&end);
                dijkstra(edge,  start,end);
                break;
            case 6:
                printf("\n");
                return 0;

        }
    }

}