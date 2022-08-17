#include <stdio.h>
#include <stdlib.h>

#define LOW 0
#define HIGH 299
#define START 53

int func (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}

void swap(int *a, int *b){
    if (*a != *b){
        *a = (*a ^ *b);
        *b = (*a ^ *b);
        *a = (*a ^ *b);
        return;
    }
}

void printSeqNPerformance(int *request, int numRequest){
    int i, last, acc = 0;
    last = START;
    printf("\n");
    printf("%d", START);
    for (i = 0; i < numRequest; i++)
    {
        printf(" -> %d", request[i]);
        acc += abs(last - request[i]);
        last = request[i];
    }
    printf("\nPerformance : %d\n", acc);
    return;
}

void CSCAN(int *request, int numRequest){
    int *newRequest, newCnt = numRequest + 2, i, j=0;
    for(i=0;i<numRequest;i++){
        if(request[i] == LOW || request[i] == HIGH){
            newCnt--;
        }
    }
    newRequest = malloc(newCnt * sizeof(int));

    qsort(request,numRequest,sizeof(int),func);

    int indexOfStart;
    for(i=0;i<numRequest-1;i++){
        if(request[i] < START && request[i+1] > START){
            indexOfStart = i;
        }
    }

    for(i=indexOfStart+1;i<numRequest;i++){
        newRequest[j] = request[i];
        j++;
    }
    newRequest[j] = 299;
    j++;
    newRequest[j] = 0;
    j++;

    for(i=0;i<=indexOfStart;i++){
        newRequest[j] = request[i];
        j++;
    }

    printf("------------------------------------\n");
    printf("C-SCAN :");
    printSeqNPerformance(newRequest, newCnt);
    printf("------------------------------------\n");
    return;
}

void LOOK(int *request, int numRequest){
    int *newRequest, newCnt=numRequest, i, j=0;

    newRequest = malloc(newCnt * sizeof(int));

    qsort(request,numRequest,sizeof(int),func);

    int indexOfStart;
    for(i=0;i<numRequest-1;i++){
        if(request[i] < START && request[i+1] > START){
            indexOfStart = i;
        }
    }

    for(i=indexOfStart+1;i<numRequest;i++){
        newRequest[j] = request[i];
        j++;
    }
    for(i=indexOfStart;i>=0;i--){
        newRequest[j] = request[i];
        j++;
    }

    printf("------------------------------------\n");
    printf("LOOK :");
    printSeqNPerformance(newRequest, newCnt);
    printf("------------------------------------\n");
    return;
}

int main(){
    int *request, numRequest, i, x;

    printf("Enter the number of disk access requests : ");
    scanf("%d", &numRequest);
    request = malloc(numRequest * sizeof(int));

    printf("Enter the requests between %d and %d\n", LOW, HIGH);
    printf("------------------------------------\n");
    for (i = 0; i < numRequest; i++){
        scanf("%d", &request[i]);
    }

    printf("\nPilihan : \n");
    printf("----------------\n");
    printf("1. C-SCAN\n");
    printf("2. LOOK\n");
    printf("----------------\n");
    printf("\nPilih : ");
    scanf("%d",&x);

    switch (x){
        case 1: CSCAN(request, numRequest);
            break;

        case 2: LOOK(request, numRequest);
            break;

        default:
            break;
    }
    return 0;
}
