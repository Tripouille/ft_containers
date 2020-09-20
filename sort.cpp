#include <iostream>

using namespace std;


int
part(int *arr, int r, int l)
{
	int i = r;
	for (int actual = r; actual < l; actual++)
		if (arr[actual] < arr[l])
			std::swap(arr[actual], arr[i++]);
	std::swap(arr[l], arr[i]);
	return (i);
}

void
sort(int *arr, int r, int l)
{
	if (r < l)
	{
		int p = part(arr, r, l);
		sort(arr, r, p - 1);
		sort(arr, p + 1, l);
	}
}

void printArray(int arr[], int size)  
{  
    int i;  
    for (i = 0; i < size; i++)  
        cout << arr[i] << " ";  
    cout << endl;  
}  

int main()  
{  
    int arr[] = {10, 7, 8, 9, 1, 5};  
    int n = sizeof(arr) / sizeof(arr[0]);  
    sort(arr, 0, n - 1);  
    cout << "Sorted array: \n";  
    printArray(arr, n);  
    return 0;  
}  