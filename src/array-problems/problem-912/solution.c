/*
					912. Sort an Array

Given an array of integers nums, sort the array in ascending order and return it.

You must solve the problem without using any built-in functions in O(nlog(n)) time complexity and with the smallest space complexity possible.

*/

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

void merge_sort(int *arr, int l, int r) 
{
	if (l >= r) 
    {
        return;
    }    
	
    int mid = (r - l) / 2 + l;
    
    merge_sort(arr, l, mid);
    merge_sort(arr, mid + 1, r);
    merge(arr, l, mid, r);
}


int* sortArray(int *nums, int numsSize, int *returnSize) 
{
    merge_sort(nums, 0, numsSize - 1);
    *returnSize = numsSize;
    return nums;
}