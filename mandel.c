#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <omp.h>

int main();
void timestamp();
void mandel(int count_max, double y_max, double y_min, double x_max, double x_min, int n, int m);
void mandel_omp(int count_max, double y_max, double y_min, double x_max, double x_min, int n, int m);
void mandel_task(int count_max, double y_max, double y_min, double x_max, double x_min, int n, int m);

int main(int argc, char* argv[]){
    int m = 500, n = 500, count_max = 1000, num = 0, max = 10000000;
    double wtime_omp, wtime_task, wtime, x_max = 1.25, x_min = - 2.25, y_max = 1.75, y_min = - 1.75;
    double time_list[max/1000];
    double time_omp_list[max/1000];
    double time_task_list[max/1000];
    int iterstep[max/1000];

    printf("\n");
    printf("MANDELBROT_openMP\n");
    timestamp();
    printf("\n\n");

    time_t endwait;
    int seconds = atoi(argv[1]);

    endwait = time (NULL) + seconds ;

    while(time (NULL) < endwait || (count_max > max)){
        if(strcmp(argv[2], "-serial") == 0){
            wtime = omp_get_wtime();
            mandel(count_max, y_max, y_min, x_max, x_min, n, m);
            wtime = omp_get_wtime() - wtime;
            time_list[num] = wtime;
        }

        if(strcmp(argv[2], "-omp") == 0){
            wtime_omp = omp_get_wtime();
            mandel_omp(count_max, y_max, y_min, x_max, x_min, n, m);
            wtime_omp = omp_get_wtime() - wtime_omp;
            time_omp_list[num] = wtime_omp;
        }

        if(strcmp(argv[2], "-task") == 0){
            wtime_task = omp_get_wtime();
            mandel_task(count_max, y_max, y_min, x_max, x_min, n, m);
            wtime_task = omp_get_wtime() - wtime_task;
            time_task_list[num] = wtime_task;
        }
        
        iterstep[num] = count_max;
        //printf("%d\n", count_max);

        count_max += 1000;
        num++;
    }
    if(strcmp(argv[2], "-serial") == 0){
        printf("\nTime_list:\n");
        for(int i = 0; i < num; i++){
            printf("%f,", time_list[i]);
        }
    }

    if(strcmp(argv[2], "-omp") == 0){
        printf("\n\nTime_omp_list:\n");
        for(int i = 0; i < num; i++){
            printf("%f,", time_omp_list[i]);
        }
    }

    if(strcmp(argv[2], "-task") == 0){
        printf("\n\nTime_task_list:\n");
        for(int i = 0; i < num; i++){
            printf("%f,", time_task_list[i]);
        }
    }

    printf("\n\nIterations list:\n");
    for(int i = 0; i < num; i++){
        printf("%d,", iterstep[i]);
    }
    printf("\n\n");
    timestamp();
    printf("\n");
    return 0;
}

void mandel(int count_max, double y_max, double y_min, double x_max, double x_min, int n, int m){
    int i, j, k;
    double x, y, x1, y1, x2, y2;
    for (i = 0; i < m; i++ ){
        y = ((double)(i-1) * y_max + (double)(m - i) * y_min) / (double)(m - 1);
        for (j = 0; j < n; j++ ){
            x = ((double)(j - 1 ) * x_max + (double)(n - j) * x_min) / (double)(n - 1);

            x1 = x;
            y1 = y;

            for (k = 1; k <= count_max; k++){
                x2 = x1 * x1 - y1 * y1 + x;
                y2 = 2 * x1 * y1 + y;

                if ( x2 < -2.0 || 2.0 < x2 || y2 < -2.0 || 2.0 < y2 ){
                    break;
                }
                x1 = x2;
                y1 = y2;
            }
        }
    }
}

void mandel_omp(int count_max, double y_max, double y_min, double x_max, double x_min, int n, int m){
    int i, j, k;
    double x, y, x1, y1, x2, y2;
    #pragma omp parallel shared (count_max, x_max, x_min, y_max, y_min ) private (i, j, k, x, x1, x2, y, y1, y2)
    {
        # pragma omp for
        for (i = 0; i < m; i++ ){
            y = ((double)(i-1) * y_max + (double)(m - i) * y_min) / (double)(m - 1);
            for (j = 0; j < n; j++ ){
            x = ((double)(j - 1 ) * x_max + (double)(n - j) * x_min) / (double)(n - 1);

            x1 = x;
            y1 = y;

                for (k = 1; k <= count_max; k++){
                    x2 = x1 * x1 - y1 * y1 + x;
                    y2 = 2 * x1 * y1 + y;

                    if ( x2 < -2.0 || 2.0 < x2 || y2 < -2.0 || 2.0 < y2 ){
                        break;
                    }
                    x1 = x2;
                    y1 = y2;
                }
            }
        }
    }
}

void mandel_task(int count_max, double y_max, double y_min, double x_max, double x_min, int n, int m){
    int i, j, k;
    double x, y, x1, y1, x2, y2;
    #pragma omp parallel shared (count_max, x_max, x_min, y_max, y_min) private (i, j, k, x, x1, x2, y, y1, y2)
    {
        #pragma omp single
        for (i = 0; i < m; i++ ){
            y = ((double)(i-1) * y_max + (double)(m - i) * y_min) / (double)(m - 1);
            #pragma omp task
            for (j = 0; j < n; j++ ){
            x = ((double)(j - 1 ) * x_max + (double)(n - j) * x_min) / (double)(n - 1);

            x1 = x;
            y1 = y;

                for (k = 1; k <= count_max; k++){
                    x2 = x1 * x1 - y1 * y1 + x;
                    y2 = 2 * x1 * y1 + y;

                    if ( x2 < -2.0 || 2.0 < x2 || y2 < -2.0 || 2.0 < y2 ){
                        break;
                    }
                    x1 = x2;
                    y1 = y2;
                }
            }
        }
    }
}
void timestamp(){
    #define TIME_SIZE 40

    static char time_buffer[TIME_SIZE];
    const struct tm *tm;
    time_t now;

    now = time ( NULL );
    tm = localtime ( &now );

    strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

    printf ( "%s", time_buffer );

    return;
    #undef TIME_SIZE
}