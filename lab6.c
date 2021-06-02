#include<windows.h>
#include<math.h>
#include <stdio.h>
#include <stdlib.h>
#define n 10

double** randmm(int rows, int cols)
{
    double** matrix = (double**)malloc(rows * sizeof(double*));

    for (int i = 0; i < rows; i++)
        matrix[i] = (double*)malloc(cols * sizeof(double));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] =  2.0 / RAND_MAX * rand();
        }
    }

    return matrix;
}

double** mulmr(double num, double **mat)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mat[i][j] = mat[i][j] * num;

            if(mat[i][j] > 1.0)
            {
                mat[i][j] = 1;
            } else mat[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if(mat[i][j] == 1) mat[j][i] = 1;

    return mat;
}

    char text[9]; int visited=0;
int *stack[10]; int tos=0; sum=0;
int dx = 16, dy = 16, dtx = 5;
int graphTree[10][10] =  {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
    };
int W[10][10]={0}, mW[10][10]={0}, cycVis[10][10]={};


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[]="Laboratory work #6";
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;
    WNDCLASS w;
    w.lpszClassName = ProgName;
    w.hInstance = hInstance;
    w.lpfnWndProc = WndProc;
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    w.hIcon = 0;
    w.lpszMenuName = 0;
    w.hbrBackground = NULL_BRUSH;
    w.style = CS_HREDRAW|CS_VREDRAW;
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if(!RegisterClass(&w))
    {
        return 0;
    }

    hWnd = CreateWindow(ProgName,
                      "Kvasova Liubov",
                      WS_OVERLAPPEDWINDOW,
                      400, 100,
                      800, 800,
                      (HWND)NULL, (HMENU)NULL,
                      (HINSTANCE)hInstance, (HINSTANCE)NULL);

    ShowWindow(hWnd, nCmdShow);

    while(GetMessage(&lpMsg, hWnd, 0, 0))
    {
    TranslateMessage(&lpMsg);
    DispatchMessage(&lpMsg);
    }

    return(lpMsg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    switch(messg)
    {
        case WM_PAINT :
        hdc=BeginPaint(hWnd, &ps);

        char *nn[n] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"};
        int nx[n] = {};
        int ny[n] = {};
        int num = 150;
        int countX = 0;
        int countY = 0;
        for(int i = 0; i < n-1; i++)
        {
            countY = (n+2)/4;
            countX = (n+1)/4;

            if(i == 0)
            {
                nx[i] = num;
                ny[i] = num;
            } else if(i <= n*0.25)
            {
                nx[i] = nx[i - 1] + num;
                ny[i] = ny[i - 1];

                int centreX = num + (countX)*(num/2);
                nx[n-1]= centreX;
                int centreY = num + (countY)*(num/2);
                ny[n-1]= centreY;

            } else if(i <= n*0.5)
            {
                nx[i] = nx[i - 1];
                ny[i] = ny[i - 1] + num;

            } else if(i <= n*0.75)
            {
                nx[i] = nx[i - 1] - num;
                ny[i] = ny[i - 1];
            } else
            {
            nx[i] = nx[i - 1] ;
            ny[i] = ny[i - 1] - num;
            }
        }


        int dx = 15, dy = 15, dtx = 7;
        int i;

        HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
        HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
        HPEN RPen = CreatePen(PS_SOLID, 2, RGB(220, 20, 60));

        srand(04010);
        double** T = randmm(n, n);
        double coef = 1.0 - 0*0.01 - 8*0.005 - 0.05;
        double** A = mulmr(coef, T);

        printf("Matrix (non directed):\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%.0f ", A[i][j]);
            }
            printf("\n");
        }


void drawtree(HDC hdc, int *uW[11][11], int i, int j, int *nx, int *ny, int tW) {
      int nx0, ny0, nxS, nyS, R, oR;
    for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(A[i][j] == 1)
                {
                    MoveToEx(hdc, nx[i], ny[i], NULL);
                    if (tW) Rectangle(hdc, (nx[i]+nx[j])/2-dx,(ny[i]+ny[j])/2-dy,(nx[i]+nx[j])/2+dx,(ny[i]+ny[j])/2+dy);
                    sprintf_s(text, 3, "%d", uW[i][j]);
                    TextOut(hdc, (nx[i]+nx[j])/2-dtx,(ny[i]+ny[j])/2-dy/2,  text, 3);
                    if(i == j)
                    {
                        if(i < n*0.25)
                        {
                            Arc(hdc, nx[j], ny[j], nx[j]-30, ny[j]-30, nx[j], ny[j], nx[j], ny[j]);
                        }
                            else if(i < n*0.5)
                        {
                            Arc(hdc, nx[j], ny[j], nx[j]+30, ny[j]-30, nx[j], ny[j], nx[j], ny[j]);
                        }
                            else if(i < n*0.75)
                        {
                            Arc(hdc, nx[j], ny[j], nx[j]+30, ny[j]+30, nx[j], ny[j], nx[j], ny[j]);
                        }
                            else
                        {
                            Arc(hdc, nx[j], ny[j], nx[j]-30, ny[j]+30, nx[j], ny[j], nx[j], ny[j]);
                        }
                        if (tW) Rectangle(hdc, nx0-(nx0-nxS)*R/oR-dx,ny0-(ny0-nyS)*R/oR-dy,nx0-(nx0-nxS)*R/oR+dx,ny0-(ny0-nyS)*R/oR+dy);
                        sprintf_s(text, 3, "%d", uW[i][j]);
                        TextOut(hdc, nx0-nxS*R/oR-dtx,ny0-nyS*R/oR-dy/2,  text, 3);

                    }
                    if((ny[i] == ny[j]) && (nx[j] != nx[i] + num) && (nx[j] != nx[i] - num))
                    {
                        if (tW) Rectangle(hdc, nx0-(nx0-nxS)*R/oR-dx,ny0-(ny0-nyS)*R/oR-dy,nx0-(nx0-nxS)*R/oR+dx,ny0-(ny0-nyS)*R/oR+dy);
                            sprintf_s(text, 3, "%d", uW[i][j]);
                            TextOut(hdc, nx0-(nx0-nxS)*R/oR-dtx,ny0-(ny0-nyS)*R/oR-dy/2,  text, 3);
                        if(i <= n*0.25)
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
                        else if(i >= n*0.5 && i <= n*0.75)
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
                    else if((nx[i] == nx[j]) && (ny[j] != ny[i] + num) && (ny[j] != ny[i] - num))
                    {
                        if (tW) Rectangle(hdc, nx0-(nx0-nxS)*R/oR-dx,ny0-(ny0-nyS)*R/oR-dy,nx0-(nx0-nxS)*R/oR+dx,ny0-(ny0-nyS)*R/oR+dy);
                            sprintf_s(text, 3, "%d", uW[i][j]);
                            TextOut(hdc, nx0-(nx0-nxS)*R/oR-dtx,ny0-(ny0-nyS)*R/oR-dy/2,  text, 3);
                        if(i >= n*0.25 && i <= n*0.5)
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
                        else if(i >= n*0.75 && i < n)
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
        }
}

        void push(int i) {
            stack[tos] = i;
            tos++;
        }

        int peek(void) {
            return stack[tos-1];
        }

        int pop(void) {
            tos--;
            if(tos < 0) {
                return 0;
            }
            return stack[tos];
        }


    int DFS (int M[10][10], int start){
    int DFSM[10]={0,0,0,0,0,0,0,0,0,0};
    int i;
    int k=1;
    DFSM[start]=1;
    push(start);
    while (tos!=0) {
        i=peek();
            for(int j = 0; j < 10; j++) {
                if (M[i][j]) {
                    if (DFSM[j]==0) {
                        k=k+1;
                        DFSM[j]=k;
                        push(j);
                        break;
                    }
                }
                if (j == 9) pop();
            }
        }

        for (int l=0; l<10; l++){
            if (DFSM[l]==0) return 1;
        }
        return 0;
    }


         void weightMat(double **A, int* W[10][10]) {
        int num;
        int Wt[10][10];
        int B[10][10];
        int C[10][10];
        int D[10][10];
        //Wt and B
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                num = roundf((rand() / (float)RAND_MAX) * 100) * A[i][j];
                Wt[i][j] = num;
                if (num == 0) B[i][j] = 0;
                else B[i][j] = 1;
            }
        }

        //C and D
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {
                if (B[i][j] != B[j][i]) C[i][j] = 1;
                else C[i][j] = 0;

                if (B[i][j] == B[j][i] && B[i][j] == 1 && j <= i) D[i][j] = 1;
                else D[i][j] = 0;
            }
        }
        //W
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {
                Wt[i][j] = (C[i][j] + D[i][j]) * Wt[i][j];
            }
        }
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {
                if (Wt[i][j]) {
                    W[j][i] = Wt[i][j];
                    W[i][j] = Wt[i][j];
                }
            }
        }

    }


    int closing(int start, int end, int* VisitedM) {
    if (start==end) return 1;
    if (VisitedM[start] && VisitedM[end]) return 1;
    return 0;
}

void kraskal(double **A, int* W[10][10]) {
    int MinWt, start, end, sumVisited;
    int VisitedM[10] = {};
    while (visited < 9) {
        MinWt = 100;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (W[i][j] && W[i][j] < MinWt) {
                    start = i;
                    end = j;
                    MinWt = W[i][j];
                }
            }
        }

        if (closing(start, end, VisitedM)) {
                cycVis[start][end] = W[start][end];
                cycVis[end][start] = W[end][start];
                W[start][end] = 0;
                W[end][start] = 0;
        } else {
            VisitedM[start] = 1;
            VisitedM[end] = 1;
            mW[start][end] = W[start][end];
            mW[end][start] = W[start][end];
            W[start][end] = 0;
            W[end][start] = 0;
            visited++;
        }
        tos=0;
        if (sum == 10) {
            MinWt = 100;
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (cycVis[i][j] && cycVis[i][j] < MinWt) {
                        start = i;
                        end = j;
                        MinWt = cycVis[i][j];
                    }
                }
            }
            mW[start][end] = cycVis[start][end];
            mW[end][start] = cycVis[start][end];

            if (DFS(mW, start)){
                    cycVis[start][end] = 0;
                    cycVis[end][start] = 0;
                    mW[start][end] = 0;
                    mW[end][start] = 0;
                } else {
                cycVis[start][end] = 0;
                cycVis[end][start] = 0;
                visited++;
                }
        }
        sum=0;
        for (int l=0; l<10; l++) {
            sum+=VisitedM[l];
        }
    }
}
            weightMat(A, W);
            kraskal(A, W);

            TextOutA(hdc, 550, 25, "Matrix for non-oriented graph", 30);
            TextOutA(hdc, 550, 375, "Matrix for graph's kistyak", 27);
            for(int i=0; i<10; i++){
                for(int j=0; j<10; j++){
                    sprintf_s(text, 2, "%g", A[i][j]);
                    TextOutA(hdc, 550 + 20 * j, 25 * i+50, text, 2);
                    sprintf_s(text, 3, "%2d", mW[i][j]);
                    TextOutA(hdc, 550 + 20 * j, 25 * i+400, text, 3);
                }
            }




        SelectObject(hdc, KPen);

            for (int i = 0; i < 10; i++){
                for (int j = 0; j < 10; j++){
                    if (A[i][j] == 1){
                        drawtree(hdc, W, i, j, nx, ny, 0);
                    }
                }
            }

        SelectObject(hdc, BPen);
        for(i = 0; i < n; i++)
        {
            Ellipse(hdc, nx[i]-dx, ny[i]-dy, nx[i]+dx, ny[i]+dy);
            if(i < 9)
            {
                TextOut(hdc, nx[i]-dtx, ny[i]-dy/2, nn[i], 1);
            } else TextOut(hdc, nx[i]-dtx, ny[i]-dy/2, nn[i], 2);
        }

          system("pause");
            system("cls");
            SelectObject(hdc, RPen);
            for (int i = 0; i < 11; i++) {
                for (int j = 0; j < 11; j++) {
                    if (mW[i][j]!=0) {
                    drawtree(hdc, mW, i, j, nx, ny, 1);
                    Ellipse(hdc, nx[i]-dx,ny[i]-dy,nx[i]+dx,ny[i]+dy);
                    TextOut(hdc, nx[i]-dtx,ny[i]-dy/2,  nn[i], 2);
                    system("pause");
                    system("cls");
                    }
                }
            }

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

