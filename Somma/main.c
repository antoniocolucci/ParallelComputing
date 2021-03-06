/*
  Il programma funziona solo de il numero di elementi dell'array è esattamente divisibile per il numero di core.
  Per esempio con N = 8 e t = 4.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
    int N, i, t, nloc;
    float sumtot, sum, *a;

    sumtot = 0;

    printf("Inserire N: ");
    scanf("%d", &N);

    a = (float*)calloc(N,sizeof(float)); //array allocato dinamicamente.

    printf("Inserire i numeri da sommare: \n");
    for(i = 0; i < N; i++)
    {
       scanf("%f", &a[i]);
    }

    #pragma omp parallel private(sum, nloc, i) shared(sumtot)
    {
        t = omp_get_num_threads();
        nloc = N/t;

        printf("Sono il thread %d, di %d: numeri %d\n",omp_get_thread_num(),t,nloc);

        sum = 0;

        for(i = 0; i < nloc; i++)
        {
            sum = sum+a[i+nloc*omp_get_thread_num()];
        }

        sumtot+=sum;
    }

    printf("La somma totale e': %f\n", sumtot);


}
