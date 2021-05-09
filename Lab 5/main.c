/*#include<windows.h>
#include<math.h>
#include <stdlib.h>
#include <stdio.h>
#include<conio.h>
#define PI 3.14159265358979323846
#define N 10

struct queue {
    int qu[10];
    int front, rear;
};

struct queue* init() {
    struct queue* q = malloc(sizeof(struct queue));
    q->front = 1;
    q->rear = 0;
   return;
}

int isEmptyQueue(struct queue* q) {
    if (q->rear <q->front) return 1;
    else return 0;
}

void insertElement(struct queue* q, int x) {
    if(q->rear < 10-1) {
    q->rear++;
    q->qu[q->rear]=x;
  }
  else
    printf("Full queue!\n");
  return;
}

int removeItem(struct queue* q) {
  int x;
  if(isEmptyQueue(q)==1) {
    printf("Empty queue!\n");
    return(0);
  }
  x = q->qu[q->front];
  q->front++;
  return x;
}

struct stack {
    int st[10];
    int top;
};

struct stack* initStack() {
    struct stack* stack = malloc(sizeof(struct stack));
    stack->top = 0;
    return stack;
}

void push(struct stack* stack, int info) {
    if (stack->top < 10) {
        stack->st[stack->top] = info;
        stack->top++;
    }
}

void pop(struct stack* stack) {
    stack->top--;
}

int peek(struct stack* stack) {
    if (stack->top > 0) return stack->st[stack->top - 1];
}

int isEmptyStack(struct stack* stack) {
    if (stack->top == 0) return 1;
    else return 0;
}

double** randm(int rows, int cols){
                double** matrix = (double**)malloc(rows * sizeof(double*));

                for (int i = 0; i < rows; i++)
                    matrix[i] = (double*)malloc(cols * sizeof(double));

                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < cols; j++)
                    {
                        matrix[i][j] =  2.0 * rand()/RAND_MAX;
                    }
                }

                return matrix;
            }

            double** mulmr(double coef, double **matrix, int rows, int cols){
                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < cols; j++)
                    {
                        matrix[i][j] = matrix[i][j] * coef;

                        if(matrix[i][j] > 1.0)
                        {
                            matrix[i][j] = 1;
                        } else matrix[i][j] = 0;
                        }
                }

                return matrix;
            }

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char ProgName[]="Lab 5";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w;

    w.lpszClassName=ProgName;
    w.hInstance=hInstance;
    w.lpfnWndProc=WndProc;
    w.hCursor=LoadCursor(NULL, IDC_ARROW);
    w.hIcon=0;
    w.lpszMenuName=0;
    w.hbrBackground = LTGRAY_BRUSH;
    w.style=CS_HREDRAW|CS_VREDRAW;
    w.cbClsExtra=0;
    w.cbWndExtra=0;

    if(!RegisterClass(&w))
        return 0;


    hWnd=CreateWindow(ProgName,
        "Kvasova Liubov",
        WS_OVERLAPPEDWINDOW,
        400,
        100,
        1000,
        800,
        (HWND)NULL,
        (HMENU)NULL,
        (HINSTANCE)hInstance,
        (HINSTANCE)NULL);

    ShowWindow(hWnd, nCmdShow);

    while(GetMessage(&lpMsg, hWnd, 0, 0)) {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
    return(lpMsg.wParam);
    }

    LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
                        WPARAM wParam, LPARAM lParam)
    {
    HDC hdc;
    PAINTSTRUCT ps;

    double** symmetricalMatrix(double **matrix, int r, int c){
             for (int i = 0; i < r; i++)
                {
                    for (int j = 0; j < c; j++)
                    {
                       if (matrix[i][j] == 1) matrix[j][i] = 1;
                }
            }
        return matrix;

        }
    void linesOfGraph(HDC hdc, double** matrix, int nx[N], int ny[N], int i, int j) {
        if(matrix[i][j] == 1)
                {
                    MoveToEx(hdc, nx[i], ny[i], NULL);
                    if(i == j)
                    {
                        if(i < 10*0.25)
                        {
                            Arc(hdc, nx[j], ny[j], nx[j]-30, ny[j]-30, nx[j], ny[j], nx[j], ny[j]);
                        }
                            else if(i < 10*0.5)
                        {
                            Arc(hdc, nx[j], ny[j], nx[j]+30, ny[j]-30, nx[j], ny[j], nx[j], ny[j]);
                        }
                            else if(i < 10*0.75)
                        {
                            Arc(hdc, nx[j], ny[j], nx[j]+30, ny[j]+30, nx[j], ny[j], nx[j], ny[j]);
                        }
                            else
                        {
                            Arc(hdc, nx[j], ny[j], nx[j]-30, ny[j]+30, nx[j], ny[j], nx[j], ny[j]);
                        }
                    }
                    if((ny[i] == ny[j]) && (nx[j] != nx[i] + 150) && (nx[j] != nx[i] - 150))
                    {
                        if(i <= 10*0.25)
                        {
                            if(nx[i] < nx[j])
                            {
                                Arc(hdc, nx[i], ny[i]-50, nx[j], ny[j]+50, nx[j], ny[j], nx[i], ny[i]);
                            }
                            else if(nx[i] > nx[j])
                            {
                                Arc(hdc, nx[j], ny[j]-50, nx[i], ny[i]+50, nx[i], ny[i], nx[j], ny[j]);
                            }
                        }
                        else if(i >= 10*0.5 && i <= 10*0.75)
                        {
                            if(nx[i] < nx[j])
                            {
                                Arc(hdc, nx[j], ny[j]-50, nx[i], ny[i]+50, nx[i], ny[i], nx[j], ny[j]);
                            }
                            else if(nx[i] > nx[j])
                            {
                                Arc(hdc, nx[i], ny[i]-50, nx[j], ny[j]+50, nx[j], ny[j], nx[i], ny[i]);
                            }
                        }
                    }
                    else if((nx[i] == nx[j]) && (ny[j] != ny[i] + 150) && (ny[j] != ny[i] - 150))
                    {
                        if(i >= 10*0.25 && i <= 10*0.5)
                        {
                            if(ny[i] < ny[j])
                            {
                                Arc(hdc, nx[i]-50, ny[i], nx[j]+50, ny[j], nx[j], ny[j], nx[i], ny[i]);
                            }
                            else if(ny[i] > ny[j])
                            {
                                Arc(hdc, nx[j]-50, ny[j], nx[i]+50, ny[i], nx[i], ny[i], nx[j], ny[j]);
                            }
                        }
                        else if(i >= 10*0.75)
                        {
                            if(ny[i] < ny[j])
                            {
                                Arc(hdc, nx[j]-50, ny[j], nx[i]+50, ny[i], nx[i], ny[i], nx[j], ny[j]);
                            }
                            else if(ny[i] > ny[j])
                            {
                                Arc(hdc, nx[i]-50, ny[i], nx[j]+50, ny[j], nx[j], ny[j], nx[i], ny[i]);
                            }
                        }
                    }
                    else
                    {
                        LineTo(hdc, nx[j], ny[j]);
                    }
                }
    }

      void vertexOfGraph(HDC hdc, int nx[N], int ny[N], char* numVerticle[N], int n) {
         int dx = 15, dy = 15, dtx = 7;
        Ellipse(hdc, nx[n]-dx,ny[n]-dy,nx[n]+dx,ny[n]+dy);
        TextOut(hdc, nx[n]-dtx,ny[n]-dy/2,  numVerticle[n], 2);
     }

     void BFS(HDC hdc, int nx[N], int ny[N], char* numVerticle[N], double** matrix, int i) {
    int allNewVerticles[10] = {};
    allNewVerticles[i] = 1;
    int numbers[10][10] = {};
    int graphTree[10][10] = {};
    int k = 1;
    char text[4];
    struct queue* q = init();
    insertElement(q, i);
    int num=0;
    int active;
    numbers[num][i] = 1;
    vertexOfGraph(hdc, nx, ny, numVerticle, i);
    sprintf_s(text, 2, "%d", 1);
    TextOutA(hdc, nx[i] - 20, ny[i] + 15, text, 1);
    while (!isEmptyQueue(q)) {
        active = removeItem(q);
        for (int i = 0; i < N; i++) {
            if (matrix[active][i]==1 && allNewVerticles[i] == 0) {
                k=k+1;
                allNewVerticles[i] = k;
                insertElement(q, i);
                linesOfGraph(hdc, matrix, nx, ny, active, i);
                vertexOfGraph(hdc, nx, ny, numVerticle, i);
                system("pause");
                system("cls");
                num = num+1;
                numbers[num][i] = 1;
                graphTree[active][i] = 1;
                sprintf_s(text, 4, "%d", num+1);
                TextOutA(hdc, nx[i] - 15, ny[i] + 15, text, 2);
            }
        }
    }
    for (int i = 0;i < 10; i++) {
        int vertex = 0;
        for (int j = 0;j < 10; j++) {
            if (numbers[i][j]==1) {
                sprintf_s(text, 5, "V%d", i+1);
                TextOutA(hdc, 10, 300 + 25 * i, text, 3);
                sprintf_s(text, 4, "%d", j+1);
                TextOutA(hdc, 45 + 20 * vertex, 300 + 25 * i, text,2);
                vertex=vertex+1;
            }
        }
    }
    //PRINT MATRIX OF GRAPH'S TREE
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            sprintf_s(text, 2, "%d", graphTree[i][j]);
            TextOutA(hdc, 600 + 15 * j, 600+25 * i, text, 1);
        }
    }
    //Print new numbers
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            sprintf_s(text, 2, "%d", numbers[i][j]);
            TextOutA(hdc, 600 + 15 * j, 400+25 * i, text, 1);
        }
    }
}

void DFS(HDC hdc, int nx[N], int ny[N], char* numVerticle[N], double** matrix, int i) {//depth
    int allNewVerticles[10] = {};
    allNewVerticles[i] = 1;
    int numbers[10][10] = {};
    int graphTree[10][10] = {};
    struct stack* s = initStack();
    int k = 1;
    int num = 0, active;
    char text[12];
    push(s, i);
    numbers[num][i] = 1;
    vertexOfGraph(hdc, nx, ny, numVerticle, i);
    sprintf_s(text, 2, "%d", num+1);
    TextOutA(hdc, nx[i] - 20, ny[i] + 15, text, 1);
    while (!isEmptyStack(s)) {
        active = peek(s);
        for (int i = 0; i < 10; i++) {
            if (matrix[active][i]==1 && allNewVerticles[i] == 0) {
                    k=k+1;
                    allNewVerticles[i] = k;
                    push(s, i);
                    linesOfGraph(hdc, matrix, nx, ny, active, i);
                    vertexOfGraph(hdc, nx, ny, numVerticle, i);
                    num=num+1;
                    numbers[num][i] = 1;
                    graphTree[active][i] = 1;
                    sprintf_s(text, 4, "%d", num+1);
                    TextOutA(hdc, nx[i] - 20, ny[i] + 15, text, 2);
                    system("pause");
                    system("cls");
                    break;
            }
            if (i == 9) {
                pop(s);
                numbers[i][i]=1;
            }
        }
    }
    for (int i = 0;i < N; i++) {
        int vertex = 0;
        for (int j = 0;j < N; j++) {
            if (numbers[i][j]) {
                sprintf_s(text, 5, "V%d", i+1);
                TextOutA(hdc, 10, 300 + 25 * i, text, 3);
                sprintf_s(text, 4, "%d", j+1);
                TextOutA(hdc, 45 + 20 * vertex, 300 + 25 * i, text, 2);
                vertex=vertex+1;
            }
        }
    }

    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            sprintf_s(text, 2, "%d", graphTree[i][j]);
            TextOutA(hdc, 600 + 15 * j, 100 + 25 * i, text, 1);
        }
    }
    //Print new numbers
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            sprintf_s(text, 2, "%d", numbers[i][j]);
            TextOutA(hdc, 600 + 15 * j, 400+25 * i, text, 1);
        }
    }
}
switch(messg){
        case WM_PAINT :

            hdc=BeginPaint(hWnd, &ps);

            int n=10;
            char *nn[10] = {"1","2","3","4","5","6","7","8","9","10"};
            int nx[10] = {};
            int ny[10] = {};
            int dx = 15, dy = 15, dtx = 7;
            int i, j;
            int countX = 0;
            int countY = 0;
        for(int i = 0; i < 10-1; i++)
        {
            countY = (10+2)/4;
            countX = (10+1)/4;

            if(i == 0)
            {
                nx[i] = 150;
                ny[i] = 150;
            } else if(i <= 10*0.25)
            {
                nx[i] = nx[i - 1] + 150;
                ny[i] = ny[i - 1];

                int centreX = 150 + (countX)*(150/2);
                nx[n-1]= centreX;
                int centreY = 150 + (countY)*(150/2);
                ny[n-1]= centreY;

            } else if(i <= 10*0.5)
            {
                nx[i] = nx[i - 1];
                ny[i] = ny[i - 1] + 150;

            } else if(i <= 10*0.75)
            {
                nx[i] = nx[i - 1] - 150;
                ny[i] = ny[i - 1];
            } else
            {
            nx[i] = nx[i - 1] ;
            ny[i] = ny[i - 1] - 150;
            }
        }

            HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
            HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
            HPEN RPen = CreatePen(PS_SOLID, 2, RGB(250, 0, 0));

        srand(04010);
        double** T = randm(n, n);
        double coef = 1 - 0*0.01 - 8*0.005 - 0.15;
        double** A = mulmr(coef, T, n, n);
             for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%g ", A[i][j]);
            }
            printf("\n");
        }
        symmetricalMatrix(A, n, n);
        printf("\nSymmetrical matrix\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%g ", A[i][j]);
            }
            printf("\n");
        }

SelectObject(hdc, KPen);

   for(int i=0;i < n; i++){
            for(int j=0; j < n; j++) {
            linesOfGraph(hdc, A, nx,  ny,  i,  j);
            }
            }
        SelectObject(hdc, BPen);

           for(i=0;i < n;i++){
              vertexOfGraph(hdc, nx,  ny,  nn,  i);
            }

         SelectObject(hdc, RPen);
          //BFS(hdc,  nx,  ny, nn, A, 0);
          DFS(hdc,  nx,  ny, nn, A, 0);

            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}
*/

#include<windows.h>
#include<math.h>
#include <stdlib.h>
#include <stdio.h>
#include<conio.h>
#define N 10

struct queue {
    int qu[10];
    int front, rear;
};

struct queue* init() {
    struct queue* q = malloc(sizeof(struct queue));
    q->front = 1;
    q->rear = 0;
   return;
}

int isEmptyQueue(struct queue* q) {
    if (q->rear <q->front) return 1;
    else return 0;
}

void insertElement(struct queue* q, int x) {
    if(q->rear < 10-1) {
    q->rear++;
    q->qu[q->rear]=x;
  }
  else
    printf("Full\n");
  return;
}

int removeItem(struct queue* q) {
  int x;
  if(isEmptyQueue(q)==1) {
    printf("Empty\n");
    return(0);
  }
  x = q->qu[q->front];
  q->front++;
  return x;
}

struct stack {
    int st[10];
    int top;
};

struct stack* initStack() {
    struct stack* stack = malloc(sizeof(struct stack));
    stack->top = 0;
    return stack;
}

void push(struct stack* stack, int info) {
    if (stack->top < 10) {
        stack->st[stack->top] = info;
        stack->top++;
    }
}

void pop(struct stack* stack) {
    stack->top--;
}

int peek(struct stack* stack) {
    if (stack->top > 0) return stack->st[stack->top - 1];
}

int isEmptyStack(struct stack* stack) {
    if (stack->top == 0) return 1;
    else return 0;
}

double** randm(int rows, int cols){
                double** matrix = (double**)malloc(rows * sizeof(double*));

                for (int i = 0; i < rows; i++)
                    matrix[i] = (double*)malloc(cols * sizeof(double));

                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < cols; j++)
                    {
                        matrix[i][j] =  2.0 * rand()/RAND_MAX;
                    }
                }

                return matrix;
            }

            double** mulmr(double coef, double **matrix, int rows, int cols){
                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < cols; j++)
                    {
                        matrix[i][j] = matrix[i][j] * coef;

                        if(matrix[i][j] > 1.0)
                        {
                            matrix[i][j] = 1;
                        } else matrix[i][j] = 0;
                        }
                }

                return matrix;
            }

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char ProgName[]="Lab 5";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w;

    w.lpszClassName=ProgName;
    w.hInstance=hInstance;
    w.lpfnWndProc=WndProc;
    w.hCursor=LoadCursor(NULL, IDC_ARROW);
    w.hIcon=0;
    w.lpszMenuName=0;
    w.hbrBackground = LTGRAY_BRUSH;
    w.style=CS_HREDRAW|CS_VREDRAW;
    w.cbClsExtra=0;
    w.cbWndExtra=0;

    if(!RegisterClass(&w))
        return 0;


    hWnd=CreateWindow(ProgName,
        "Kvasova Liubov",
        WS_OVERLAPPEDWINDOW,
        400,
        100,
        1000,
        800,
        (HWND)NULL,
        (HMENU)NULL,
        (HINSTANCE)hInstance,
        (HINSTANCE)NULL);

    ShowWindow(hWnd, nCmdShow);

    while(GetMessage(&lpMsg, hWnd, 0, 0)) {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
    return(lpMsg.wParam);
    }

    LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
                        WPARAM wParam, LPARAM lParam)
    {
    HDC hdc;
    PAINTSTRUCT ps;

    double** symmetricalMatrix(double **matrix, int r, int c){
             for (int i = 0; i < r; i++)
                {
                    for (int j = 0; j < c; j++)
                    {
                       if (matrix[i][j] == 1) matrix[j][i] = 1;
                }
            }
        return matrix;

        }
    void lines(HDC hdc, double** matrix, int nx[N], int ny[N], int i, int j) {
        if(matrix[i][j] == 1)
                {
                    MoveToEx(hdc, nx[i], ny[i], NULL);
                    if(i == j)
                    {
                        if(i < 10*0.25)
                        {
                            Arc(hdc, nx[j], ny[j], nx[j]-30, ny[j]-30, nx[j], ny[j], nx[j], ny[j]);
                        }
                            else if(i < 10*0.5)
                        {
                            Arc(hdc, nx[j], ny[j], nx[j]+30, ny[j]-30, nx[j], ny[j], nx[j], ny[j]);
                        }
                            else if(i < 10*0.75)
                        {
                            Arc(hdc, nx[j], ny[j], nx[j]+30, ny[j]+30, nx[j], ny[j], nx[j], ny[j]);
                        }
                            else
                        {
                            Arc(hdc, nx[j], ny[j], nx[j]-30, ny[j]+30, nx[j], ny[j], nx[j], ny[j]);
                        }
                    }
                    if((ny[i] == ny[j]) && (nx[j] != nx[i] + 150) && (nx[j] != nx[i] - 150))
                    {
                        if(i <= 10*0.25)
                        {
                            if(nx[i] < nx[j])
                            {
                                Arc(hdc, nx[i], ny[i]-50, nx[j], ny[j]+50, nx[j], ny[j], nx[i], ny[i]);
                            }
                            else if(nx[i] > nx[j])
                            {
                                Arc(hdc, nx[j], ny[j]-50, nx[i], ny[i]+50, nx[i], ny[i], nx[j], ny[j]);
                            }
                        }
                        else if(i >= 10*0.5 && i <= 10*0.75)
                        {
                            if(nx[i] < nx[j])
                            {
                                Arc(hdc, nx[j], ny[j]-50, nx[i], ny[i]+50, nx[i], ny[i], nx[j], ny[j]);
                            }
                            else if(nx[i] > nx[j])
                            {
                                Arc(hdc, nx[i], ny[i]-50, nx[j], ny[j]+50, nx[j], ny[j], nx[i], ny[i]);
                            }
                        }
                    }
                    else if((nx[i] == nx[j]) && (ny[j] != ny[i] + 150) && (ny[j] != ny[i] - 150))
                    {
                        if(i >= 10*0.25 && i <= 10*0.5)
                        {
                            if(ny[i] < ny[j])
                            {
                                Arc(hdc, nx[i]-50, ny[i], nx[j]+50, ny[j], nx[j], ny[j], nx[i], ny[i]);
                            }
                            else if(ny[i] > ny[j])
                            {
                                Arc(hdc, nx[j]-50, ny[j], nx[i]+50, ny[i], nx[i], ny[i], nx[j], ny[j]);
                            }
                        }
                        else if(i >= 10*0.75)
                        {
                            if(ny[i] < ny[j])
                            {
                                Arc(hdc, nx[j]-50, ny[j], nx[i]+50, ny[i], nx[i], ny[i], nx[j], ny[j]);
                            }
                            else if(ny[i] > ny[j])
                            {
                                Arc(hdc, nx[i]-50, ny[i], nx[j]+50, ny[j], nx[j], ny[j], nx[i], ny[i]);
                            }
                        }
                    }
                    else
                    {
                        LineTo(hdc, nx[j], ny[j]);
                    }
                }
    }

      void graphVertex(HDC hdc, int nx[N], int ny[N], char* numVerticle[N], int n) {
         int dx = 15, dy = 15, dtx = 7;
        Ellipse(hdc, nx[n]-dx,ny[n]-dy,nx[n]+dx,ny[n]+dy);
        TextOut(hdc, nx[n]-dtx,ny[n]-dy/2,  numVerticle[n], 2);
     }

     void BFS(HDC hdc, int nx[N], int ny[N], char* numVerticle[N], double** matrix, int i) {
    int newVertical[10] = {};
    newVertical[i] = 1;
    int numbers[10][10] = {};
    int graphTree[10][10] = {};
    int k = 1;
    char text[4];
    struct queue* q = init();
    insertElement(q, i);
    int num=0;
    int active;
    numbers[num][i] = 1;
    graphVertex(hdc, nx, ny, numVerticle, i);
    sprintf_s(text, 2, "%d", 1);
    TextOutA(hdc, nx[i] - 20, ny[i] + 15, text, 1);
    while (!isEmptyQueue(q)) {
        active = removeItem(q);
        for (int i = 0; i < N; i++) {
            if (matrix[active][i]==1 && newVertical[i] == 0) {
                k=k+1;
                newVertical[i] = k;
                insertElement(q, i);
                lines(hdc, matrix, nx, ny, active, i);
                graphVertex(hdc, nx, ny, numVerticle, i);
                system("pause");
                system("cls");
                num = num+1;
                numbers[num][i] = 1;
                graphTree[active][i] = 1;
                sprintf_s(text, 4, "%d", num+1);
                TextOutA(hdc, nx[i] - 15, ny[i] + 15, text, 2);
            }
        }
    }
    for (int i = 0;i < 10; i++) {
        int vertex = 0;
        for (int j = 0;j < 10; j++) {
            if (numbers[i][j]==1) {
                sprintf_s(text, 5, "V%d", i+1);
                TextOutA(hdc, 10, 300 + 25 * i, text, 3);
                sprintf_s(text, 4, "%d", j+1);
                TextOutA(hdc, 45 + 20 * vertex, 300 + 25 * i, text,2);
                vertex=vertex+1;
            }
        }
    }

    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            sprintf_s(text, 2, "%d", graphTree[i][j]);
            TextOutA(hdc, 600 + 15 * j, 600+25 * i, text, 1);
        }
    }

    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            sprintf_s(text, 2, "%d", numbers[i][j]);
            TextOutA(hdc, 600 + 15 * j, 400+25 * i, text, 1);
        }
    }
}

void DFS(HDC hdc, int nx[N], int ny[N], char* numVerticle[N], double** matrix, int i) {
    int newVertical[10] = {};
    newVertical[i] = 1;
    int numbers[10][10] = {};
    int graphTree[10][10] = {};
    struct stack* s = initStack();
    int k = 1;
    int num = 0, active;
    char text[12];
    push(s, i);
    numbers[num][i] = 1;
    graphVertex(hdc, nx, ny, numVerticle, i);
    sprintf_s(text, 2, "%d", num+1);
    TextOutA(hdc, nx[i] - 20, ny[i] + 15, text, 1);
    while (!isEmptyStack(s)) {
        active = peek(s);
        for (int i = 0; i < 10; i++) {
            if (matrix[active][i]==1 && newVertical[i] == 0) {
                    k=k+1;
                    newVertical[i] = k;
                    push(s, i);
                    lines(hdc, matrix, nx, ny, active, i);
                    graphVertex(hdc, nx, ny, numVerticle, i);
                    num=num+1;
                    numbers[num][i] = 1;
                    graphTree[active][i] = 1;
                    sprintf_s(text, 4, "%d", num+1);
                    TextOutA(hdc, nx[i] - 20, ny[i] + 15, text, 2);
                    system("pause");
                    system("cls");
                    break;
            }
            if (i == 9) {
                pop(s);
                numbers[i][i]=1;
            }
        }
    }
    for (int i = 0;i < N; i++) {
        int vertex = 0;
        for (int j = 0;j < N; j++) {
            if (numbers[i][j]) {
                sprintf_s(text, 5, "%d", i+1);
                TextOutA(hdc, 10, 300 + 25 * i, text, 3);
                sprintf_s(text, 4, "%d", j+1);
                TextOutA(hdc, 45 + 20 * vertex, 300 + 25 * i, text, 2);
                vertex=vertex+1;
            }
        }
    }

    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            sprintf_s(text, 2, "%d", graphTree[i][j]);
            TextOutA(hdc, 600 + 15 * j, 100 + 25 * i, text, 1);
        }
    }

    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            sprintf_s(text, 2, "%d", numbers[i][j]);
            TextOutA(hdc, 600 + 15 * j, 400+25 * i, text, 1);
        }
    }
}
switch(messg){
        case WM_PAINT :

            hdc=BeginPaint(hWnd, &ps);

            int n=10;
            char *nn[10] = {"1","2","3","4","5","6","7","8","9","10"};
            int nx[10] = {};
            int ny[10] = {};
            int dx = 15, dy = 15, dtx = 7;
            int i, j;
            int countX = 0;
            int countY = 0;
        for(int i = 0; i < 10-1; i++)
        {
            countY = (10+2)/4;
            countX = (10+1)/4;

            if(i == 0)
            {
                nx[i] = 150;
                ny[i] = 150;
            } else if(i <= 10*0.25)
            {
                nx[i] = nx[i - 1] + 150;
                ny[i] = ny[i - 1];

                int centreX = 150 + (countX)*(150/2);
                nx[n-1]= centreX;
                int centreY = 150 + (countY)*(150/2);
                ny[n-1]= centreY;

            } else if(i <= 10*0.5)
            {
                nx[i] = nx[i - 1];
                ny[i] = ny[i - 1] + 150;

            } else if(i <= 10*0.75)
            {
                nx[i] = nx[i - 1] - 150;
                ny[i] = ny[i - 1];
            } else
            {
            nx[i] = nx[i - 1] ;
            ny[i] = ny[i - 1] - 150;
            }
        }

            HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
            HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
            HPEN RPen = CreatePen(PS_SOLID, 2, RGB(250, 0, 0));

        srand(04010);
        double** T = randm(n, n);
        double coef = 1 - 0*0.01 - 8*0.005 - 0.15;
        double** A = mulmr(coef, T, n, n);
             for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%g ", A[i][j]);
            }
            printf("\n");
        }
        symmetricalMatrix(A, n, n);
        printf("\nSymmetrical:\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%g ", A[i][j]);
            }
            printf("\n");
        }

SelectObject(hdc, KPen);

   for(int i=0;i < n; i++){
            for(int j=0; j < n; j++) {
            lines(hdc, A, nx,  ny,  i,  j);
            }
            }
        SelectObject(hdc, BPen);

           for(i=0;i < n;i++){
              graphVertex(hdc, nx,  ny,  nn,  i);
            }

         SelectObject(hdc, RPen);
          //BFS(hdc,  nx,  ny, nn, A, 0);
            DFS(hdc,  nx,  ny, nn, A, 0);

            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}

