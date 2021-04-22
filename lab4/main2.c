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

double** mulmr(double num, double **mat, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mat[i][j] = mat[i][j] * num;

            if(mat[i][j] > 1.0)
            {
                mat[i][j] = 1;
            } else mat[i][j] = 0;
        }
    }

    return mat;
}

double** step (double **fMat, double **Smat, double **Rmat, int rows, int cols)
{
    for ( int i = 0; i < rows; i++ )
    {
        for ( int j = 0; j < cols; j++ )
        {
            Rmat[i][j] = 0;
            for ( int k = 0; k < cols; k++ )
            {
                Rmat[i][j] += fMat[i][k] * Smat[k][j];
            }
        }
    }
    return Rmat;
}

double** transp (double **mat, double **Rmat, int rows, int cols)
{
    for ( int i = 0; i < rows; i++ ) {
        for ( int j = 0; j < cols; j++ ) {
            Rmat[i][j] = 0;
        }
    }
    for ( int i = 0; i < rows; i++ ) {
        for ( int j = 0; j < cols; j++ ) {
            Rmat[j][i] = mat[i][j];
        }
    }
    return Rmat;
}

double** condenc (double** mat, double** checkin, double** svyaz, int row, int cols)
{
    for ( int i = 0; i < row; i++ ) {
        for ( int k = 0; k < 9; k++ ) {
            if ( checkin[i][k] != -1 ) {
                double thisEl = checkin[i][k];

            }
        }
    }
    return mat;
}


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[]="Laboratory work #4";
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
                      150, 150,
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

    void arrow(float fi, int px,int py)
    {
        //fi = 3.1416*(180.0 - fi)/180.0;
        int lx,ly,rx,ry;
        lx = px+15*cos(fi+0.3);
        rx = px+15*cos(fi-0.3);
        ly = py+15*sin(fi+0.3);
        ry = py+15*sin(fi-0.3);
        MoveToEx(hdc, lx, ly, NULL);
        LineTo(hdc, px, py);
        LineTo(hdc, rx, ry);
    }

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


        int dx = 16, dy = 16, dtx = 7;
        int i;

        HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
        HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

        srand(04010);
        double** T = randmm(n, n);
        double coef = 1.0 - 0*0.005 - 8*0.005 - 0.27;
        double** A = mulmr(coef, T, n, n);

        printf("\nMatrix:\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%.0f ", A[i][j]);
            }
            printf("\n");
        }

        double B[n][n] = {};
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    B[i][j] = A[i][j];
                }
            }

        double sqB[n][n]; //шлях довжиною 2
                   printf("2 dovsina\n");
                    for(i=0;i < n;i++){
                        for(int j=0;j < n;j++){
                            sqB[i][j]=0;
                            for(int k=0;k < n;k++){
                                sqB[i][j]=sqB[i][j]+B[i][k]*B[k][j];
                            }
                            if (sqB[i][j]>0) {
                                    sqB[i][j]=1;
                                    for(int k=0;k < n;k++){
                                        if (B[i][k]==1 && B[k][j]==1) {
                                            printf("%d->%d->%d->%d || ", i+1, k+1, j+1);
                                        }
                                    }
                            }
                        }
                         printf("\n");
                    }

            double cubB[n][n]; //шлях довжиною 3
        printf("3 dovsina\n");
            for(i=0;i < n;i++){
                for(int j=0;j < n;j++){
                    cubB[i][j]=0;
                    for(int k=0;k < n;k++){
                        cubB[i][j]=cubB[i][j]+sqB[i][k]*B[k][j];
                    }
                    if (cubB[i][j]>0) {
                        for(int k=0;k < n;k++){
                            if (sqB[i][k]==1 && B[k][j]==1) {
                                for(int m=0;m < n;m++){
                                    if (B[i][m]==1 && B[m][k]==1) {
                                        cubB[i][j]=1;
                                        printf("%d->%d->%d->%d || ", i+1, m+1, k+1, j+1);
                                    }
                                }

                            }
                        }
                    }
                }
                 printf("\n");
            }


            double** some = randmm(n,n);
            double** puti = step(A, A, some, n, n );
            printf( "\nReached matrix:\n" );
            double** matDos = randmm(n,n);
            for( int i = 0; i < n; i++ )
            {
                for ( int j = 0; j < n; j++ )
                {
                    puti[i][j] = A[i][j];
                    matDos[i][j] = A[i][j];
                }
            }
            for ( int i = 0; i < n-1; i++ )
            {
                puti = step(puti,A,some,n,n);
                for ( int k = 0; k < n; k++ )
                {
                    for ( int f = 0; f < n; f++ )
                    {
                        if ( puti[k][f] != 0 || matDos[k][f] != 0 ) matDos[k][f] = 1;
                        else matDos[k][f] = 0;
                    }
                }

            }
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    printf("%.0f ", matDos[i][j]);
                }
                printf("\n");
            }


          //silnosvyaz
            printf( "\nMatrix svyazi:\n" );
            double** smt = randmm(n,n);
            double** transported = transp(matDos,smt,n,n);
            double components [n][n] = {};
            for ( int i = 0; i < n; i++ )
            {
                for ( int j = 0; j < n; j++ )
                {
                    if ( matDos[i][j] != 0 && transported[i][j] != 0 ) smt[j][j] = 1;
                    else smt[i][j] = 0;
                    printf("%.0f ", smt[i][j]);
                    components[i][j] = -1;
                }
                printf("\n");
            }


         printf( "\nComponents silnoi svyaznosti:\n" );
            double checker[n] = {};
           for (int i = 0; i < n; i++ ) checker[i] = 0;
            for ( int i = 0; i < n; i++ )
            {
                if( checker[i] == 0 ) {
                    printf("{ ");
                    for ( int j = i; j < n; j++ ) {
                        if ( smt[i][j] == 1 ) {
                            printf("%i, ", j+1);
                            checker[j] = -1;
                        }
                    }
                    printf(" },\n");
                }

            }


        SelectObject(hdc, KPen);

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(A[i][j] == 1)
                {
                    MoveToEx(hdc, nx[i], ny[i], NULL);

                    if(i == j)
                    {
                        if(i < n*0.25)
                        {
                            Arc(hdc, nx[j], ny[j], nx[j]-40, ny[j]-40, nx[j], ny[j], nx[j], ny[j]);
                            arrow((-90*3.1416)/180, nx[j], ny[j]-dy);
                        }
                            else if(i < n*0.5)
                        {
                            Arc(hdc, nx[j], ny[j], nx[j]+40, ny[j]-40, nx[j], ny[j], nx[j], ny[j]);
                            arrow((0*3.1416)/180, nx[j]+dx, ny[j]);
                        }
                            else if(i < n*0.75)
                        {
                            Arc(hdc, nx[j], ny[j], nx[j]+40, ny[j]+40, nx[j], ny[j], nx[j], ny[j]);
                            arrow((90*3.1416)/180, nx[j], ny[j]+dy);
                        }
                            else
                        {
                            Arc(hdc, nx[j], ny[j], nx[j]-40, ny[j]+40, nx[j], ny[j], nx[j], ny[j]);
                            arrow((180*3.1416)/180, nx[j]-dx, ny[j]);
                        }
                    }
                    if((ny[i] == ny[j]) && (nx[j] != nx[i] + num) && (nx[j] != nx[i] - num))
                    {
                        if(i <= n*0.25)
                        {
                            if(nx[i] < nx[j])
                            {
                                Arc(hdc, nx[i], ny[i]-50, nx[j], ny[j]+50, nx[j], ny[j], nx[i], ny[i]);
                                arrow((-140*3.1416)/180, nx[j]-16*cos(-45), ny[j]+16*sin(-45));
                            }
                            else if(nx[i] > nx[j])
                            {
                                Arc(hdc, nx[j], ny[j]-40, nx[i], ny[i]+40, nx[i], ny[i], nx[j], ny[j]);
                                arrow((-25*3.1416)/180, nx[j]+dx*cos(-150), ny[j]-dy*sin(-140)-30);
                            }
                        }
                        else if(i >= n*0.5 && i <= n*0.75)
                        {
                            if(nx[i] < nx[j])
                            {
                                Arc(hdc, nx[j], ny[j]-50, nx[i], ny[i]+50, nx[i], ny[i], nx[j], ny[j]);
                                arrow((140*3.1416)/180, nx[j]+16*cos(-45), ny[j]-16*sin(-45)+3);
                            }
                            else if(nx[i] > nx[j])
                            {
                                Arc(hdc, nx[i], ny[i]-40, nx[j], ny[j]+40, nx[j], ny[j], nx[i], ny[i]);
                                arrow((25*3.1416)/180, nx[j]-dx*cos(-150), ny[j]+dy*sin(-140)+30);
                            }
                        }
                    }
                    else if((nx[i] == nx[j]) && (ny[j] != ny[i] + num) && (ny[j] != ny[i] - num))
                    {
                        if(i >= n*0.25 && i <= n*0.5)
                        {
                            if(ny[i] < ny[j])
                            {
                                Arc(hdc, nx[i]-40, ny[i], nx[j]+40, ny[j], nx[j], ny[j], nx[i], ny[i]);
                                arrow((-70*3.1416)/180, nx[j]+dx*cos(-145)-2, ny[j]+dy*sin(-145)-2);
                            }
                            else if(ny[i] > ny[j])
                            {
                                Arc(hdc, nx[j]-50, ny[j], nx[i]+50, ny[i], nx[i], ny[i], nx[j], ny[j]);
                                arrow((45*3.1416)/180, nx[j]+dx*cos(-145), ny[j]+dy*sin(-145)+15);
                            }
                        }
                        else if(i >= n*0.75)
                        {
                            if(ny[i] < ny[j])
                            {
                                Arc(hdc, nx[j]-40, ny[j], nx[i]+40, ny[i], nx[i], ny[i], nx[j], ny[j]);
                                arrow((-110*3.1416)/180, nx[j]-dx*cos(-145)+1, ny[j]-dy*sin(-145)-15);
                            }
                            else if(ny[i] > ny[j])
                            {
                                Arc(hdc, nx[i]-40, ny[i], nx[j]+40, ny[j], nx[j], ny[j], nx[i], ny[i]);
                                arrow((110*3.1416)/180, nx[j]-dx*cos(-145)+1, ny[j]+dy*sin(-145)+15);
                            }
                        }
                        else if(i == 0)
                        {
                            Arc(hdc, nx[j]-60, ny[j], nx[i]+60, ny[i], nx[i], ny[i], nx[j], ny[j]);
                            arrow((-130*3.1416)/180, nx[j]-dx*cos(-145)-2, ny[j]-dy*sin(-145)-12);
                        }
                    }
                    else
                    {
                        double fi = 3.141 + acos((nx[j]-nx[i])/(sqrt((nx[j]-nx[i])*(nx[j]-nx[i])+(ny[j]-ny[i])*(ny[j]-ny[i]))));
                        if(ny[j] < ny[i]) fi *= -1;

                        if(A[i][j] == A[j][i] && i < j)
                        {
                            MoveToEx(hdc, nx[i]+5, ny[i]+5, NULL);
                            LineTo(hdc, nx[j]+5, ny[j]+5);
                            arrow(fi, nx[j]+5+dx*cos(fi), ny[j]+5+dy*sin(fi));
                        }
                        else if(A[i][j] == A[j][i] && i > j)
                        {
                            MoveToEx(hdc, nx[i]-5, ny[i]-5, NULL);
                            LineTo(hdc, nx[j]-5, ny[j]-5);
                            arrow(fi, nx[j]-5+dx*cos(fi), ny[j]-5+dy*sin(fi));
                        }
                        else
                        {
                            LineTo(hdc, nx[j], ny[j]);
                            arrow(fi, nx[j]+dx*cos(fi), ny[j]+dy*sin(fi));
                        }
                    }
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
