/*
1.       Part 1: sorting algorithms for small problem size
a): sorting algorithms :
insertion sort, selection sort, bubble sort, 
recursive merge sort, iterative merge sort, 
recursive quicksort , iterative quicksort,  
heapsort, C++ built in sorting function
B): problem size: 20,40,60,80,100,120
c): data type: string with length 6
2.       Part 1: sorting algorithms for huge problem size
a): sorting algorithms: recursive merge sort, iterative merge sort recursive quicksort , iterative quicksort,  heapsort, C++ built in sorting function
B): problem size: 200萬,400萬,600萬,800萬,1000萬
c): data type: string with length 6
3.       心得報告及效能分析圖表
   a. tile and author
    b. methodology 
         b.1 benchmarks
         b.2 execution environment
    c. experiment result
    d. conclusion
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>
#include <map>
 
using namespace std;

void swap(string *a, string *b){
    string temp = *a;
    *a = *b;
    *b = temp;
}

void OutPut(int size, string a[]) {
	for(int i = 0; i < size; i++)
		cout << a[i] << endl;
}
void Merge(string A[], int p, int q, int m);

void Merge_Sort(string A[], int p, int q) {
	if (p < q) {
		int m = (p + q) / 2;
		Merge_Sort(A, p, m);  //遞迴排序子陣列 A[p...m]
		Merge_Sort(A, m + 1, q); //遞迴排序子陣列 A[m+1...q]
		Merge(A, p, q, m);  //將左右兩個以排序好的子陣列合併
	}
}
void Merge(string A[], int p, int q, int m) {
	int n1 = m - p + 1;
	int n2 = q - m;
	/*Let L[0...n1] and R[0...n2] be new arrays
	and copy A[p...m] to L[0...n1] 
	and copy A[m+1...q] to R[0...n2] */
	string* L = new string[n1 + 1];
	string* R = new string[n2 + 1];

	for (int i = 0; i < n1; i++) {
		L[i] = A[p + i]; 
	}
	for (int i = 0; i < n2; i++) {
		R[i] = A[i + m + 1]; 
	}
	
	L[n1] = "zzzzzz";
	R[n2] = "zzzzzz"; 
	
	int i = 0, j = 0;
	for (int k = p; k <= q; k++) {
		if (L[i] <= R[j]) {
			A[k] = L[i];
			i++;
		}
		else {
			A[k] = R[j];
			j++;
		}
	}
}


//************///////////////////////************/////////////////////////////////////***///************///////////////////////************//////////////
void Rmerge(string arr[], int l, int m, int r);
/* l is for left index and r is right index of the sub-array 
  of arr to be sorted */
void RmergeSort(string arr[], int l, int r) 
{ 
   if (l < r) 
   { 
      int m = l + (r - l) / 2; //Same as (l+r)/2 but avoids overflow for large l & h 
      RmergeSort(arr, l, m); 
      RmergeSort(arr, m + 1, r); 
      Rmerge(arr, l, m, r); 
   } 
   //50 + (60 - 50) / 2 = 55 
 } 
  
/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void Rmerge(string arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    string *L = new string[n1 + 1];
	string *R = new string[n2 + 1]; // remember +1
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1 + j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    
    L[n1] = "zzzzzz";
    R[n2] = "zzzzzz"; // get compiler pass without declare 不知道為啥 
    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
//HeapSort//////////////////////////////////////////////////////////////// 
void max_heapify(string arr[], int start, int end) {
    // 建立父節點指標和子節點指標
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) { // 若子節點指標在範圍內才做比較
        if (son + 1 <= end && arr[son] < arr[son + 1]) // 先比較兩個子節點大小，選擇最大的
            son++;
        if (arr[dad] > arr[son]) // 如果父節點大於子節點代表調整完畢，直接跳出函數
            return;
        else { // 否則交換父子內容再繼續子節點和孫節點比較
            swap(arr[dad], arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void heap_sort(string arr[], int len) {
    // 初始化，i從最後一個父節點開始調整
    for (int i = len / 2 - 1; i >= 0; i--)
        max_heapify(arr, i, len - 1);
    // 先將第一個元素和已?排好的元素前一位做交換，再從新調整(??整的元素之前的元素)，直到排序完畢
    for (int i = len - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        max_heapify(arr, 0, i - 1);
    }
}
/////////////////////////
int Partition(string arr[], int front, int end){
    string pivot = arr[end];
    int i = front -1;
    for (int j = front; j < end; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    i++;
    swap(&arr[i], &arr[end]);
    return i;
}
void Recursive_QS(string arr[], int front, int end){
    if (front < end) {
        int pivot = Partition(arr, front, end);
        Recursive_QS(arr, front, pivot - 1);
        Recursive_QS(arr, pivot + 1, end);
    }
}

///////////////////
int conqure_IQS(string list[], int l, int r)
{
    string pivot = list[r];
    int i = l - 1;

    for(int j = l; j<r; j++)
        if(list[j] < pivot){
            i++;
            swap(list[i], list[j]);
        }
    
    swap(&list[i+1], &list[r]);
     
    return i+1;
}

void Iterative_QS(string list[], int n)
{
    if(n <= 0){
        printf("bad size!");
        exit(-1);
    }

    int stack[1000];
    int top = -1;
    int l, r;

    l = 1, r = n;
    stack[++top] = l;
    stack[++top] = r;

    while(top >= 0){
        r = stack[top--];
        l = stack[top--];
		int p;
        p = conqure_IQS(list, l, r);

        if(p-1 > l){
            stack[++top] = l;
            stack[++top] = p-1;
        }

        if(p+1 < r){
            stack[++top] = p+1;
            stack[++top] = r;
        }
    }
}

void selection_sort(int size, string a[]);
void insertion_sort(int size, string a[]);
void bubble_sort(int size, string a[]);

int main(){
	srand(time(0));
	int pos;
	double start, end; //time counter
	string b = "abcdefghijklmnopqrstuvwxyz", d = "abcdef";
	
	int size[5] = {2000000, 4000000, 6000000, 8000000, 10000000}; //size choise
	
	/*測資 = 
	20
	40
	60
	80
	100
	120
	2000
	4000
	6000
	8000
	10000
	12000
	
	*/
	cout << "0 = CPP build in sorting function\n";
	cout << "1 = Interative QuickSort\n";
	cout << "2 = Recursive QuickSort\n";
	cout << "3 = HeapSort\n";
	cout << "4 = Interactive MergeSort\n";
	cout << "5 = Recursive MergeSor\n";
	cout << "s = selection sort\n";
	cout << "i = insertion sort\n";
	cout << "b = bubble sort\n";
	cout << "There are nine algorithms: \n\n";
	
	string Mode = "012345sib"; //Mode choise
	int mm;
	char MODE;
	for(int s = 0; s < 9; s++) {
		
		cout << "Size is " << size[s] << endl;
		string *e = new string [size[s]]; //e is template and module
		
	/*int len = (int) sizeof(e) / sizeof(*e);
		cout << "586666666666666666666666666660" << endl << len;*/
		
		for(int i = 0; i < size[s]; i++) {
			for(int j = 0; j < 6; j++) {
				d[j] = b[(rand () % 26)];//在26個英文字園中隨機取一個
				//cout << d[j] << endl;
			}
			e[i] = d;
			//cout << "e[" << i << "] = " << e[i] << endl;
		}
	


		for(mm = 0; mm < 6 ; mm++) {
			cout << endl << endl << mm;
			
			string *ee = new string[size[s]]; //ee is the data of each algorithm 
			//ee = e; //you can't do that
			//switch 裡面只接受CHAR? 
			for(int AS = 0; AS < size[s]; AS++)
				ee[AS] = e[AS];
				
			start = clock();
			
			MODE = Mode[mm];
			
			switch(MODE) {
				case '0':
					sort(ee, ee + size[s]);
					break;
				case '1':
					Iterative_QS(ee, size[s] - 1);
					break;
				case '2':
					Recursive_QS(ee, 0, size[s] - 1);
					break;
				case '3':
					heap_sort(ee, size[s]);
					break;
				case '4':
					RmergeSort(ee, 0, size[s] - 1);
					break;
				case '5':
					Merge_Sort(ee, 0, size[s] - 1);
					break;
				case 's':
					selection_sort(size[s], ee);
					break;
				case 'i':
					insertion_sort(size[s], ee);
					break;
				case 'b':
					bubble_sort(size[s], ee);
					break;
	
			}
			cout << endl;
			//OutPut(size, e);
			end = clock();
			cout << "Cost " << (end - start) / CLOCKS_PER_SEC << " sec.";
			cout << endl << endl;
			delete []ee; 
		}
		
		delete[] e;
		cout << "XDDD"; 
	}

	return 0;
}

void selection_sort(int size, string a[]) {
	string temp = "abcdef";
	
	for(int i = 0; i < size; i++) {
		int pos = i;
		for(int j = i + 1; j < size; j++)
			if(a[j] < a[pos])
				pos = j;
			temp = a[i];
			a[i] = a[pos];
			a[pos] = temp;
	}
	//OutPut(size, a);
}

void insertion_sort(int size, string a[]) {
	string temp = "abcdef";
	
	for(int i = 1; i < size; i++){
  		temp = a[i];
   		int j;
   		for (j = i - 1; j >= 0 && temp < a[j]; j--)
       		a[j + 1] = a[j];
   		a[j + 1] = temp;
	}
	//OutPut(size, a);
}

void bubble_sort(int size, string a[]) {
	for(int i = 0; i < size - 1; i++) 
		for(int j = 0; j < size - 1 - i; j++) 
			if(a[j] > a[j + 1])
				swap(a[j], a[j + 1]);
	//OutPut(size, a);
}
