/*
					912. Sort an Array

Given an array of integers nums, sort the array in ascending order and return it.

You must solve the problem without using any built-in functions in O(nlog(n)) time complexity and with the smallest space complexity possible.

*/


/*
		Multithreading solution using POSIX threads

*/
#include <pthread.h>

struct arr_struct
{
	int *arr;
	int l;
	int r;
};

struct arr_struct make_arr_struct(int * arr, int l, int r)
{
	struct arr_struct res; 
	res.arr = arr;
	res.l = l;
	res.r = r;
	return res;
}

void unpack_arr_struct(struct arr_struct, int **arr, int *l, int *r)
{
	*arr = arr_struct.arr;
	*l = arr_struct.l;
	*r = arr_struct.r;
}

int calculate_mid(int l, int r)
{
	return (r - l) / 2 + l;
}

void merge(int *arr, int l, int mid, int r) 
{    
    int arr_structize = r - l + 1;

    int temp_arr[arr_structize];
    memset(temp_arr, 0, sizeof(int) * arr_structize);
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
    memcpy(arr + l, temp_arr, (arr_structize)*sizeof(int));
}


void* merge_sort_multithread(void *args) 
{
	if (args == NULL)
	{
		return NULL;
	}
	
	int l, r;
	int *arr;
	unpack_arr_struct((arr_struct)(*args), arr, l, r);

	if (l >= r) 
    {
        return NULL;
    }    
	
    int mid = calculate_mid(l, r);
    merge_sort_multithread(arr, make_arr_struct(l, mid));
    merge_sort_multithread(arr, make_arr_struct(mid + 1, r));
    merge(arr, l, mid, r);
	
	return NULL;
}

int start_sorting(int *arr, int size)
{
	int l = 0;
	int r = size - 1;	
	int mid = calculate_mid(l, r);
	
	pthread_t l_part_thread, r_part_thread;
	
	struct arr_struct l_part_args = make_arr_struct(arr, l, mid);
	struct arr_struct r_part_args = make_arr_struct(arr, mid, r);
	
	if (pthread_create(&l_part_thread, NULL, merge_sort_multithread, (void*)(&l_part_args)) != 0) {
        fprintf(stderr, "Could not start left thread!\n");
        return 1;
    }
	
	if (pthread_create(&r_part_thread, NULL, merge_sort_multithread, (void*)(&r_part_args)) != 0) {
        fprintf(stderr, "Could not start right thread!\n");
        return 1;
    }	
	
	pthread_join(l_part_thread, NULL);
    pthread_join(r_part_thread, NULL);
	
	merge(arr, l, mid, r);
	return 0;
}

int* sortArray(int *nums, int numsSize, int *returnSize) 
{
    start_sorting(nums, 0, numsSize);
    *returnSize = numsSize;
    return nums;
}

/*
int main()
{
	
}
*/