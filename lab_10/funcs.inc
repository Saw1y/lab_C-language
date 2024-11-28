void fill_random(arr_type** const arr, int const A, int const left, int const right)
{
    srand(time(NULL));
    int i;
    int j;
    for (i = 0; i < A; i++)
    {
        for (j = 0; j < LEN(arr[i]); j++)
        {
            ELEM(arr[i], j) = left + rand() % (right - left + 1);
        }
    }
}


void print_array(arr_type** const arr, int A) {
  int i;
  int j;
    for (i = 0; i < A; i++)
    {
        for (j = 0; j < LEN(arr[i]); j++)
        {
            printf(string_type " ", ELEM(arr[i], j));
        }
        printf("\n");
    }
    printf("\n");
}



arr_type* deleting(arr_type* row) {
    int i = 1;
    while (i <= LEN(row) ) {
        if (ELEM(row, i - 1) % 2 == 0) {
            ELEM(row, i - 1) = ELEM(row, LEN(row) - 1); 
            LEN(row)--;            
        } else {
            i++;
        }
    }
    row = realloc(row, (LEN(row) + 1) * sizeof(int));
    return row;
}


arr_type* add(arr_type* const row, int const left, int const right) {
    int count = 0;
    int j;
    
    for (j = 0; j < LEN(row); j++) 
	{
        if (ELEM(row, j) < 0) 
		{
            count++;
        }
    }

    int new_size = LEN(row) + count; 
    arr_type* new_row = (arr_type*)malloc((new_size + 1) * sizeof(arr_type));
    if (!new_row) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    LEN(new_row) = new_size;

    int index = 0; 
    for (j = 0; j < LEN(row); j++) {
        ELEM(new_row, index) = ELEM(row, j);
		index++; 
        if (ELEM(row, j) < 0) {
            ELEM(new_row, index) = left + rand() % (right - left + 1);
            index++; 
        }
    }

    free(row); 
    return new_row;
}




arr_type* rearrangement(arr_type* const row) {
    int left = 0;
    int right = LEN(row) - 1; 
    while (left < right) {
        while (left <= LEN(row) && ELEM(row, left) >= 0) {
            left++;
        }
        while (right > 0 && ELEM(row, right) < 0) {
            right--;
        }
        if (left < right) {
            int temp = ELEM(row, left);
            ELEM(row, left) = ELEM(row, right);
            ELEM(row, right) = temp;
        }
    }
    return row;
}

arr_type *find(arr_type* const row)
{
  int i;
  int ind = -1;
  
  #ifdef FIND_FIRST
  for (i = 0; i < LEN(row); i++)
  {
    if (ELEM(row, i) < 0 )
    {
      ind = i;
    }
  }
  #else
  for (i = 0; i < LEN(row); i++)
  {
    if (ELEM(row, i) < 0 )
    {
      ind = i;
      break;
    }
  }
  #endif
  if (ind != -1)
  {
    ELEM(row, ind)= 0;
  }
	
  return row;
}
