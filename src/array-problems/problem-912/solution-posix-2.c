/*
                    912. Sort an Array

Given an array of integers nums, sort the array in ascending order and return it.

You must solve the problem without using any built-in functions in O(nlog(n)) time complexity and with the smallest space complexity possible.

*/


/*
        Multithreading solution using POSIX threads
        to DO
        add shared thread counter and mutex for it
*/

struct arg_struct
{
    int *arr;
    int thread_cnt;
    int l;
    int r;
};

struct arg_struct make_arg_struct(int * arr, int thread_cnt, int l, int r)
{
    struct arg_struct res; 
    res.arr = arr;
    res.thread_cnt = thread_cnt;
    res.l = l;
    res.r = r;
    return res;
}

void unpack_arg_struct(struct arg_struct args, int **arr, int *thread_cnt, int *l, int *r)
{
    *arr = args.arr;
    *thread_cnt = args.thread_cnt;
    *l = args.l;
    *r = args.r;
}

int calculate_mid(int l, int r)
{
    return (r - l) / 2 + l;
}

void merge(int *arr, int l, int mid, int r) 
{    
    int arr_size = r - l + 1;

    int temp_arr[arr_size];
    memset(temp_arr, 0, sizeof(int) * arr_size);
    int i = l;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= r)
    {
        if (arr[i] <= arr[j])
        {
            temp_arr[k++] = arr[i];
            i++;
        } 
        else 
        {
            temp_arr[k++] = arr[j];
            j++;
        }
    }
    
    while(i <= mid)
    {
        temp_arr[k++] = arr[i];
        i++;
    }
    
    while(j <= r)
    {
        temp_arr[k++] = arr[j];
        j++;        
        
    }
    memcpy(arr + l, temp_arr, (arr_size)*sizeof(int));
}

void* merge_sort_multithread(void *args) 
{
    if (args == NULL)
    {
        return NULL;
    }
    
    int l, r;
    int *arr = NULL;
    int thread_cnt;
    unpack_arg_struct(*((struct arg_struct*)args), &arr, &thread_cnt, &l, &r);

    if (l >= r) 
    {
        return NULL;
    }    
    
    int mid = calculate_mid(l, r);
    
    if (thread_cnt > 0)
    {
        pthread_t l_part_thread, r_part_thread;
        
         
        struct arg_struct l_part_args = make_arg_struct(arr, thread_cnt, l, mid);
        struct arg_struct r_part_args = make_arg_struct(arr, thread_cnt, mid + 1, r);
        thread_cnt--;
        
        if (pthread_create(&l_part_thread, NULL, merge_sort_multithread, (void*)(&l_part_args)) != 0) 
        {
            fprintf(stderr, "Could not start left thread!\n");
            return NULL;
        }
    
        if (pthread_create(&r_part_thread, NULL, merge_sort_multithread, (void*)(&r_part_args)) != 0) 
        {
            fprintf(stderr, "Could not start right thread!\n");
            return NULL;
        }    
        
        pthread_join(l_part_thread, NULL);
        pthread_join(r_part_thread, NULL);
            
    } 
    else 
    { 
        struct arg_struct l_part_args = make_arg_struct(arr, thread_cnt, l, mid);
        struct arg_struct r_part_args = make_arg_struct(arr, thread_cnt, mid + 1, r);
        merge_sort_multithread((void*)&l_part_args);
        merge_sort_multithread((void*)&r_part_args);
    }
    
    merge(arr, l, mid, r);
    
    return NULL;
}

int start_multithread_sorting(int *arr, int size, int thread_count)
{
    int l = 0;
    int r = size - 1;    
     
    
    struct arg_struct args = make_arg_struct(arr, thread_count, l, r);
    merge_sort_multithread((void*)&args);
    
    return 0;
}

int* sortArray(int *nums, int numsSize, int *returnSize) 
{
    start_multithread_sorting(nums, numsSize, 1);
    *returnSize = numsSize;
    return nums;
}
