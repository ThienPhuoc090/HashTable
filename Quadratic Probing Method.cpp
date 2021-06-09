#include <iostream>
#include<cmath>
#include<ctime>
using namespace std;

// Bài toán: Xây dựng chương trình bảng băm(hashtable) với phương pháp xử lý đụng độ: Quadratic Probing Method (Dò bậc hai)
// Xây dựng lớp băm 
class HashTable
{
private:
	int n;
	int size;
	int* arr = new int[size];
public:
	HashTable(int a) : size(a) 
	{
		for (int i = 0; i < this->size; i++)
			this->arr[i] = -1;
	}
	HashTable() // Phương thức khởi tạo 
	{
		this->n = this->size = 0;
		this->arr = NULL;
	}
	~HashTable() {} // Phương thức hủy

	bool isEmpty() { return((n == 0) ? true : false); } // Hàm logic Kiểm tra bảng băm có rỗng hay không? 
	bool isFull() { return ((n == size) ? true : false); } // Hàm logic Kiểm tra bảng băm có đầy hay không?


	void InsertArray(int a[], int m) // Hàm thêm các key vào bảng băm bằng mảng 1 chiều các số nguyên 
	{
		this->size = m;
		for (int i = 0; i < m; i++)
			this->Insert(a[i]);
	}

	void Insert(int k) // Hàm thêm key vô bảng băm
	{
		if (this->isFull() == true)
		{
			return;
		}
		else if (this->size != 0)
		{
			int m = k % this->size;
			for (int j = 0; (j < this->size); j++)
			{
				int i = m + pow(j, 2);
				if (this->arr[i] == -1)
				{
					this->arr[i] = k;
					this->n++;
					return;
				}
			}
		}

	}

	// Hàm Xuất tuần tự các bucket trong bảng băm 
	void TraverseHashTable()
	{
		for (int i = 0; i < size; i++)
		{
			if (this->arr[i] != -1)
				cout << "\nSlot " << i << ": " << this->arr[i] << "\t\t";
			else cout << "\nSlot " << i << " is NULL!" << "\t";
		}
	}

	// Hàm Tìm kiếm key trong bảng băm 
	void Search(int k)
	{
		if (this->isEmpty() == true)
			cout << "\n\tHashTable is Empty!";
		else
		{
			for (int i = 0; i < size; i++)
			{
				if (this->arr[i] == k)
				{
					cout << "\nFound!";
					return;
				}
			}
			cout << "\nNot Found!";
		}
	}

	// Hàm xóa dữ liệu của bucket bất kì trong bảng băm
	void DeleteBucket(int k)
	{
		if (this->isEmpty() == true)
			cout << "\n\tHashTable is Empty!";
		else if (k >= 0 && k< this->size) // Điều kiện xử lý lệnh xóa ngăn: đầu vào phải là số tự nhiên
		{
			arr[k] = -1;
			this->n--;
			return;
		}
		else cout << "\nNot found this Slot! Please try again!";
	}
};

int main()
{
	int n = rand() % 21 - 0;
	int* a = new int[n];
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		a[i] = rand() % 100 - 0;

	// HashTable
	cout << "\n\n\t\t\t\t\t===== HASH TABLE =====\n";
	HashTable A(n);
	A.InsertArray(a, n);
	A.TraverseHashTable();
	if (A.isFull() == true)
		cout << "\n\t HashTable is FULL! Can't insert new key!";
	delete[]a;

	// Search 
	int k = rand() % 100 - 0;
	cout << "\n\nSearch " << k;
	A.Search(k);

	cout << endl;
	system("pause");

	// Delete
	int z = rand() % n - 0;
	cout << "\n\nDelete slot " << z;
	A.DeleteBucket(z);
	cout << "\n\n\t\t\t\t\t===== HASH TABLE AFTER DELETE =====\n";
	A.TraverseHashTable();

	cout << endl;
	system("pause");
	return 0;
}