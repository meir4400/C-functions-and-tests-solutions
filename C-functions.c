
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

/*--------------------------------------------------------------------------
------------------------- general functions --------------------------------
--------------------------------------------------------------------------*/


// quick sort for array of int ===================================================

void quick_sort_int(int arr[], int first, int last) {
    int i, j, pivot, temp;
    if (first < last) {
        pivot = first;
        i = first;
        j = last;
        while (i < j) {
            while (arr[i] <= arr[pivot] && i < last)
                i++;
            while (arr[j] > arr[pivot])
                j--;
            if (i < j) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        temp = arr[pivot];
        arr[pivot] = arr[j];
        arr[j] = temp;
        quick_sort_int(arr, first, j - 1);
        quick_sort_int(arr, j + 1, last);
    }
}
// count number of char in string ================================================

int count_char_in_str(char* s, char c) {
    int total = 0, i=0;
    while (s[i]) {
        if (s[i] == c) {
            total++;
        }
        i++;
    }
    return total;
}
// count number of digits in number ==============================================

int count_digits_in_int(int num) {
    int counter = 1;
    while ((num /= 10) > 0) {
        counter++;
    }
    return counter;
}
//  convert char in given range to int ===========================================

int char_to_int(char c, char first, char last) {
    if (c < first || c > last) { return -1; }
    return c - first;
}
//  convert string of digits to int ==============================================

int str_to_int(char* S) {
    int num = 0, temp;
    if ((temp = char_to_int(*S, '0', '9')) >= 0) { num = temp; }
    while ( (temp = char_to_int(*(++S), '0', '9')) >= 0 ){
        num *= 10;
        num += temp;
    } 
    return num;
}
// swap int ======================================================================

void swap_int(int* a, int* b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}
// swap generic ==================================================================

void swap_generic(void* v1, void* v2, size_t  size) {
    void* temp = malloc(size);
    if (!temp) {
        printf("error while allocating memory\n");
    }
    memcpy(temp, v1, size);
    memcpy(v1, v2, size);
    memcpy(v2, temp, size);
    free(temp);
}

// work with linked list (int) ===================================================

typedef struct {
    int val;
    int* next;
}Node;

void print_list(Node* list) {
    while (list != NULL) {
        printf("%d ", list->val);
        list = list->next;
    }
}

Node* allocate_node() {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        printf("error while allocation memory\n");
        return NULL;
    }
}

Node* is_smaller_node(Node* current, Node* other) { //gets two nodes and put the smaller at first
    if (current->val > other->val) {
        other->next = current;
        return other;
    }
    else {
        other->next = current->next;
        current->next = other;
        return current;
    }
}

Node* insert_node(Node *list, int value) {//insert node to list in descending order
    Node *node = allocate_node(), **temp;
    node->val = value;
    node->next = NULL;
    if (list == NULL) { //empty list case
        return node;
    }
    else if (list->val >= value) { //should insert to head case
        node->next = list;
        list = node;
        return list;
    }
    else {  //other cases
        temp = &list->next;
        while ( *temp != NULL ) {
            if ( (*temp)->val >= value ) {
                node->next = *temp;
                *temp = node;
                return list;
            }
            temp = &(*temp)->next;
        }
        *temp = node;
            return list;
    }
}

Node* delete_node_by_val(Node* list, int val) { //delete one node with specific value from list
    Node **temp, *temp2;
    if (list == NULL) { return NULL; }
    else if (list->val == val) {    //if desired value is the head, delete it and return
        temp2 = list->next;
        free(list);
        return temp2;
    }
    else {  //when node to delete is not at first
        temp = &list->next;
        while (*temp != NULL) {
            if ((*temp)->val == val) {
                temp2 = *temp;
                *temp = temp2->next;
                free(temp2);
                return list;
            }
        }
        temp = &(*temp)->next;
    }
    return list;    //will arrive here if value not exist in list
}

int get_min_value(Node* list) {
    if (!list) { return -1; }
    int min = list->val;
    while (list != NULL) {
        if (list->val < min) {
            min = list->val;
        }
        list = list->next;
    }
    return min;
}

int get_max_value(Node* list) {
    if (!list) { return -1; }
    int max = list->val;
    while (list != NULL) {
        if (list->val > max) {
            max = list->val;
        }
        list = list->next;
    }
    return max;
}

int search_list(Node* list, int value) {
    while (list != NULL) {
        if (list->val == value) {
            return 1;
        }
        list = list->next;
    }
    return 0;
}

void free_list(Node* list) {
    Node* temp;
    while (list != NULL) {
        temp = list->next;
        free(list);
        list = temp;
    }
}
// bitwise actions ================================================================
/*
To set the nth bit, use OR:
x |= (1 << 5); // sets the 5th-from right

To clear a bit, use AND:
x &= ~(1 << 5); // clears 5th-from-right

To flip a bit, use XOR:
x ^= (1 << 5); // flips 5th-from-right

To get the value of a bit use shift and AND:
(x & (1 << 5)) >> 5 // gets the value (0 or 1) of the 5th-from-right

To restart bit:
variable &= ~( 1 << bit_index );
*/

/*--------------------------------------------------------------------------
------------------------- problems solutions -------------------------------
--------------------------------------------------------------------------*/

// is array sorted in one swap =====================================================

int is_sorted_array_in_one_swap(int* arr, int size) {
    int i, j, current, ok = 1;
    for (i = 1; i < size - 1; i++) {
        if (arr[i] < arr[i - 1]) {
            if (ok == 0) {
                return 0;
            }
            for (j = i - 1; j >= 0; j--) {
                if (j == 0 && arr[i] <= arr[j]) {
                    swap_int(arr[j], arr[i]);
                    ok = 0;
                    i--;
                    break;
                }
                else if (j > 0 && arr[i] <= arr[j] && arr[i] >= arr[j - 1]) {
                    swap_int(&arr[j], &arr[i]);
                    ok = 0;
                    i--;
                    break;
                }
            }
        }
    }
    return 1;
}
// seats in airplane problem (change "row" if indexed from 1) ========================

int** fill_seats_array(int N, char* S) {
    int row=0, col=0;
    int** arr = (int**)calloc(N, sizeof(int*));
    for (int i = 0; i < N; i++) {
        arr[i] = (int*)calloc(8, sizeof(int));
    }
    char *token = strtok(S," ");
    while(token != NULL) {
        row = str_to_int(token);   
        //row--;  //assumes the arr indexed from 0. if isnt, enable this line to decrease row in 1
        col = char_to_int( *(token + count_digits_in_int(row)), 'B', 'I');
        if (col >= 0) {   //ignore row edges
            arr[row][col] = 1;
        }
        token = strtok(NULL, " ");
    }
    return arr;
}

void free_arr(int** arr, int N) {
    for (int i = 0; i < N; i++) {
        free(arr[i]);
    }
    free(arr);
}

int seats_in_plane(int N, char* S) {
    int **arr = fill_seats_array(N, S);
    int set, counter = 0, row, col;
    for (row = 0; row < N; row++) {
        for (col= 0, set=0; col < 8; col++) {
printf("%d ", arr[row][col]);
            (arr[row][col] == 0) ? (set++) : (set = 0) ;

            if (set == 4) {
                counter++;
                set = 0;
            }
        }
printf("\n");
    }
    free_arr(arr, N);
    return counter;
}
// preventing company debt ====================================================

int relocations_pyments(int A[], int N) {
    int counter = 0, sum = 0, num_to_del, i;
    Node* list = NULL;
    for (i = 0; i < N; i++) {
        if (A[i] < 0) {
            list = insert_node(list, A[i]);
        }
        sum += A[i];
        if (sum < 0) {
            num_to_del = get_min_value(list);
            list = delete_node_by_val(list, num_to_del);
            sum -= num_to_del;
            counter++;
        }
    }
    free_list(list);
    return counter;
}
// main ========================================================================
int main()
{
    return 0;
}