#ifndef CODE_GRAPH_H_
#define CODE_GRAPH_H_

#define SAT_NUM 114 //節點數量
#define MAX 114 //節點數量
#define SAT_LINE 186    //txt行數
#define EDGE_DISTANCE 2000  //邊最大距離
#define infinity 99999


typedef struct Node{
    int node_site;
    char dd[3];
    char MM[4];
    char yy[5];
    char date[13];
    double x, y, z;
    struct Node* txt_next;
    struct Node* next;
}Node;

typedef struct Graph{
    int graph_id;
    int* visited;
    Node** adjList;
    int* distance;
}Graph;



Graph* creategraph(int size);
void read_txt(const char* filename, Node*, int txt_line, int i);
void create_adjlist(Graph*,Node*);
void printAdjList(Graph*);
void sat_distance(Graph*,Node*);
void Selected_sat_distance(Graph*,Node*,int);

void DFS(struct Graph*, int);
void init(Graph*);
void dijkstra(double [SAT_NUM+1][SAT_NUM+1], int ,int);
void Create_Edge(Graph*, Node*, double [SAT_NUM+1][SAT_NUM+1]);
#endif // CODE_GRAPH_H_ 