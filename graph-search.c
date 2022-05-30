#include <stdio.h>
#include <stdlib.h>

typedef struct node { // 인접리스트 그래프 노드
	int Vertex;
	struct node *link;
} GraphNode;

#define MAX_VERTEX 10 
int top = -1;
int front = -1;
int rear = -1;

GraphNode* stack[MAX_VERTEX]; // 스택
GraphNode* queue[MAX_VERTEX]; // 큐

void createGraph(GraphNode** g); // 그래프 생성 함수
int insertVertex(GraphNode* g, int v); // 정점 삽입 함수
int insertEdge(GraphNode* g, int u, int v); // 간선 삽입 함수
void DepthFS(GraphNode* g, int v); // Depth First Search 함수
//void BreathFS(GraphNode* g, int v); // Breath First Search 함수
void printGraph(GraphNode* g); // 그래프 출력 함수
int destroyGraph(GraphNode* g); // 그래프 삭제 함수

int main() {	

	char command;
    int u, v;
	GraphNode* Graph = NULL;

    do{	
		printf("\n[----- [Kim Hyeong Jin]  [2021041079] -----]\n"); // 학번 이름 출력
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                          Graph Searches                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertex        = v      Insert Edge                  = e \n");
		printf(" Depth First Search   = d      Breath First Search          = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':	// 명령어 Z : 그래프 생성 함수 호출
				createGraph(&Graph);
				break;
        case 'v': case 'V':	// 명령어 V : 정점 삽입 함수 호출
				printf("Create Vertex = ");
				scanf("%d", &v);
				insertVertex(Graph, v);
				break;    
		case 'e': case 'E':	// 명령어 E : 간선 삽입 함수 호출
				printf("Input Edge u, Vertex = ");
				scanf("%d %d", &u, &v);
				insertEdge(Graph, u, v);
				break;
		case 'd': case 'D':	// 명령어 D : DepthFS 함수 호출
				printf("DepthFS = ");
				scanf("%d", &u);
				DepthFS(Graph, u);
				break;
		//case 'b': case 'B':	// 명령어 B : BreathFS 함수 호출
				//printf("BreathFS = ");
				//scanf("%d", &u);
				//BreathFS(Graph, u);
				//break;
		case 'p': case 'P':	// 명령어 P : 그래프 출력 함수 호출
			printGraph(Graph);
			break;
        case 'q': case 'Q':	// 명령어 Q : 그래프 삭제 함수 호출
			destroyGraph(Graph);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void createGraph(GraphNode** g) {

    if(*g != NULL) { // Node가 NULL이 아닐 시
        destroyGraph(*g);  // 그래프 삭제 함수 호출
	}

    *g = (GraphNode*)malloc(sizeof(GraphNode)*MAX_VERTEX);	// 동적 할당

    for (int i = 0; i < MAX_VERTEX; i++) {
        (*g+i) -> link = NULL;  // Link 초기화
        (*g+i) -> Vertex = -1;  // 정점 초기화
    }

	top = -1; 
    front = -1;
	rear = -1;
}

int insertVertex(GraphNode* g, int v) {

    if (((g+v) -> Vertex) == v) {	// 정점이 존재할 시 에러메시지
	   printf("\nError : Vertex already exists.\n");
	   return 0;
    }
	if ((v < 0) || (v >= MAX_VERTEX)) { // 정점이 범위 밖일 시 에러메시지
        printf("\nError : Invalid Vertex.\n");
	    return 0;
    }
	(g+v) -> Vertex = v; // 정점 삽입

   return 1;
}

int insertEdge(GraphNode* g, int u, int v) {

    if (u < 0 || v < 0) { // 값이 범위 밖일 시 에러메시지
		printf("\nError\n");
		return 0;
	}
	if((g+u)->Vertex == -1 || (g+v)->Vertex == -1) { // 정점이 존재하지 않을 시 에러메시지
		printf("\nVertex is not exist.\n");
		return 0;
	}

	GraphNode* temp = (g+u);
	GraphNode* E =(GraphNode*)malloc(sizeof(GraphNode));		
	GraphNode* Vtx =(GraphNode*)malloc(sizeof(GraphNode));	

	E->Vertex = u;
	Vtx->Vertex = v;
    E->link = Vtx->link = NULL;
	

	while(1) {
		if(temp->Vertex == v){ // 이미 존재하면 에러메시지
			printf("\nEdge is already exist.\n");
			return 0;
		}
		if(!temp->link){
			temp->link = Vtx;
			break;
		}
		if(temp->link->Vertex > v){ // 번호 작은 순
			Vtx->link = temp->link;
			temp->link = Vtx;
			break;
		}
		else {
			temp = temp ->link; // 다음 노드 이동
		}
	}
    temp=(g+v);
	while(1){
		if(!temp->link) { 
			temp->link = E;
			break;
		}
		if(temp->link->Vertex > u) { // 번호 작은 순
			temp->link = temp->link;   
			temp->link = E;
			break;
		}
		else {
			temp = temp->link; // 다음 노드 이동
		}
	}
	return 1;
}

void DepthFS(GraphNode* g, int v) {
	if((g+v)->Vertex == -1) { // 오류 처리
		printf("\nThere is no Vertex.\n");
		return ;
	}
    if (v < 0 || v > MAX_VERTEX - 1) {
		printf("\nError\n");
		return;
	}

	top = -1;
	int visit[MAX_VERTEX]; 
    for(int i = 0; i < MAX_VERTEX; i++) { // 방문에 대한 초기화
        visit[i] = 0; 
    }

	GraphNode* temp = g+v;
	GraphNode* popp = NULL;

	while(1) {
		
		v = temp->Vertex; // 정점 저장

		if(!visit[v]){ // 방문하지 않았을 경우
			visit[v]=1;
			push(g+v);	// push
            printf(" [%d] ",v);	// 정점 출력
			temp = g+v;
		}
		else {
			if (temp->link == NULL) { // NULL 이면
				popp = pop(); // 스택에서 삭제
				temp = g+(temp->Vertex);
			}
			temp = temp->link; // 노드 이동
		}
    	if (top == -1) { // top이 초기값이면 반복문 탈출
			break;
		} 
	}
}

void printGraph(GraphNode* g) {
	for(int num=0; num < MAX_VERTEX; num++) {
		GraphNode* temp = (g + num);
		for(int i=0; i < MAX_VERTEX; i++) {	 // 반복문 통해 Vertex 출력
			if(temp->Vertex != -1) {
				printf(" [%d] ", (temp->Vertex));
			}
			if(temp->link) { // 링크가 NULL이 아니면
				temp = temp->link; // 다음 노드 이동
			}
			else { // 링크가 NULL일 시 반복문 탈출
				break;
			}
			
		}
		printf("\n");
	}
}

int destroyGraph(GraphNode* g) {
	int num =0;
	GraphNode* temp = NULL;
	GraphNode* prev = NULL;
	temp = (g+num);
    for (num = 0; num < MAX_VERTEX; num++) {
		GraphNode* temp = (g+num);
		GraphNode* prev = NULL;
		while (temp != NULL) { // 메모리 해제
			prev = temp;
			temp = temp->link;
			free(prev);
		}

		free(temp); // 메모리 해제
		temp = NULL;
	}
}