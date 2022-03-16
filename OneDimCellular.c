#include<stdio.h>
#include<stdlib.h>

void change_state(int a,int arr[]);
void print_automata(int a,int arr[]);
int change_rule(int left, int current, int right);
int* initialize_automata(int *a, int*b);

int main() {
    int i,num_of_steps,len_automata;
    int *current_automata;
    
    current_automata = initialize_automata(&len_automata,&num_of_steps);
    print_automata(len_automata,current_automata);
    
    for (i=0;i<num_of_steps;++i) {
        change_state(len_automata, current_automata);
        print_automata(len_automata,current_automata);
    }
    free(current_automata);
}

int* initialize_automata(int *a, int *b) {
    int i;
    int* policko;
    printf("zadej delku pole\n");
    scanf("%d",a);
    printf("zadej pocet kol\n");
    scanf("%d",b);
    policko = (int *)malloc((*a)*sizeof(int));
    
    printf("zadej hodnoty pole\n");
    for (i=0;i<(*a);++i) {
        scanf("%d",&policko[i]);
    }
    return policko;
}

void change_state(int a, int arr[]) {
    int i;
    int *help_arr;
    help_arr = (int*) malloc(a*sizeof(int));

    for (i=0;i<a-1;++i) {
        help_arr[i]=arr[i];
    }
    for (i=1;i<a-1;++i) {
        arr[i]=change_rule(help_arr[i-1],help_arr[i],help_arr[i+1]);
    }
    arr[0]=change_rule(help_arr[a-1],help_arr[0],help_arr[1]);
    arr[a-1]=change_rule(help_arr[a-2],help_arr[a-1],help_arr[0]);
    free(help_arr);
}

void print_automata(int a, int arr[]) {
    int i;
    for (i=0;i<a;++i) {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int change_rule(int left, int current, int right) {
    int result;
    int decide = left+3*current+5*right;
    switch (decide)
    {
    case 9:
    case 1:
    case 8:
    case 5:
        result=1;
        break;
    default:
        result=0;
    }
    return result;
}