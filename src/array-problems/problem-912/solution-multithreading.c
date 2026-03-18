struct arr_struct
{
	int *arr;
	size_t l;
	size_t r;
};


struct arr_struct make_arr_struct(int * arr, size_t l, size_t r)
{
	struct arr_struct res; 
	res.arr = arr;
	res.l = l;
	res.r = r;
	return res;
}

void unpack_arr_struct(struct arr_struct inst, int **arr, size_t *l, size_t *r)
{
    *arr = inst.arr;
	*l = inst.l;
	*r = inst.r;
}

size_t calculate_mid(size_t l, size_t r)
{
	return (r - l) / 2 + l;
}

void merge(int *arr, size_t l, size_t mid, size_t r) 
{    
    size_t arr_size = r - l + 1;

    int temp_arr[arr_size];
    memset(temp_arr, 0, sizeof(int) * arr_size);
    size_t i = l;
    size_t j = mid + 1;
    size_t k = 0;

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
	
	size_t l, r;
	int *arr;
	unpack_arr_struct(*((struct arr_struct*)args), &arr, &l, &r);

	if (l >= r) 
    {
        return NULL;
    }    
	
    size_t mid = calculate_mid(l, r);
    
    struct arr_struct l_part_args = make_arr_struct(arr, l, mid);
	struct arr_struct r_part_args = make_arr_struct(arr, mid + 1, r);
    merge_sort_multithread((void*)&l_part_args);
    merge_sort_multithread((void*)&r_part_args);
    
    merge(arr, l, mid, r);
	return NULL;
}

size_t start_sorting(int *arr, size_t size)
{
	size_t l = 0;
	size_t r = size - 1;	
	size_t mid = calculate_mid(l, r);
	
	pthread_t l_part_thread, r_part_thread;
	
	struct arr_struct l_part_args = make_arr_struct(arr, l, mid);
	struct arr_struct r_part_args = make_arr_struct(arr, mid + 1, r);
	
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
    start_sorting(nums, (int)numsSize);
    *returnSize = numsSize;
    return nums;
}