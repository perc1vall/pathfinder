#include "../inc/libmx.h"

int mx_bubble_sort(char **arr, int size) {
    char *tmp;
    int res = 0;
    for(int R=size-1; R>0; R--){
        for(int i=0; i<R; i++)
            if (mx_strcmp(arr[i],arr[i+1])>0) {
                tmp=arr[i];
                arr[i]=arr[i+1];
                arr[i+1]=tmp;
                res++;
            }
    }

    return res;
}
