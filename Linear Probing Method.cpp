#include <iostream>
#include<cmath>
#include<ctime>
#include<iomanip>
using namespace std;

// Bài toán: Xây dựng chương trình bảng băm(hashtable) với phương pháp xử lý đụng độ: Linear Probing Method(Dò tuyến tính)
// Mặc định số ngăn của bảng băm là 100
#define M 100
#define NULLKEY false // Mặc định logic các khóa chưa có data là false
struct TagNode // Tạo cấu trúc Node
{
	int key;
	bool flag;
};
typedef struct TagNode NODE; 

// Thuật toán băm cơ bản  
int HashFunc(int k)
{
	return ((int)k % 10);
}

// Xây dựng lớp băm 
class HashTable
{
private:
	NODE arr[M]; 
	int n;
public:
	HashTable() // Phương thức khởi tạo 
	{
		this->n = 0;
		for (int i = 0; i < M; i++)
		{
			this->arr[i].key = -1;
			this->arr[i].flag = NULLKEY;	
		}
	}
	~HashTable(){} // Phương thức hủy
	
	bool isEmpty() { return((n == 0) ? true : false); } // Hàm logic Kiểm tra bảng băm có rỗng hay không? 
	bool isFull() { return ((n == M) ? true : false); } // Hàm logic Kiểm tra bàng băm có đầy hay không?

	void Insert(int k) // Hàm thêm key vô bảng băm
	{
		if (this->isFull() == true)
		{
			return;
		}
		else
		{
			// Cụm các lệnh thêm khóa bằng phương thức xử lý tuyến tính khi xảy ra đụng độ 
			int i;
			for (i = HashFunc(k); i < M; i++)
			{
				if (this->arr[i].flag == false)
				{
					this->arr[i].key = k;
					this->arr[i].flag = true;
					this->n++;
					break;
				}
			}

		}
	}

	void InsertArray(int a[], int m) // Hàm thêm các key vào bảng băm bằng mảng 1 chiều các số nguyên 
	{
		for (int i = 0; i < m; i++)
			this->Insert(a[i]);
	}

	// Hàm Xuất tuần tự các bucket trong bảng băm 
	void TraverseHashTable()
	{
		int line = 0;
		for (int i = 0; i < M; i++)
		{
			if (this->arr[i].flag == true)
			{
				cout << "Bucket " << i << ": " << this->arr[i].key << "\t\t";
				line++;
			}
			else
			{
				cout << "Bucket " << i << ": NULLKEY" << "\t";
				line++;
			}
			if (line ==5)
			{
				cout << endl;
				line = 0;
			}
		}
	}

	// Hàm Tìm kiếm key trong bảng băm 
	void Search(int k)
	{
		if (this->isEmpty() == true)
			cout << "\n\tHashTable is Empty!";
		else
		{
			for (int i = 0; i < M; i++)
			{
				if (this->arr[i].flag == true && this->arr[i].key == k)
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
		else if (k >= 0) // Điều kiện xử lý lệnh xóa ngăn: đầu vào phải là số tự nhiên
		{
			this->arr[k].flag = false;
			this->arr[k].key = -1;
			this->n--;
			return;
		}
		else if (k < 0)
			cout << "\nNot found this Bucket! Please try again!";
	}
};

int main()
{
	int n = 100;
	int* a = new int[n];
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		a[i] = rand() % 200 - 0;

	// HashTable
	cout << "\n\n\t\t\t\t\t===== HASH TABLE =====\n";
	HashTable A;
	A.InsertArray(a, n);
	A.TraverseHashTable();
	if(A.isFull()==true)
		cout << "\n\t HashTable is FULL! Can't insert new key!";
	delete[]a;

	// Search 
	int k = rand() % 200 - 0;
	cout << "\n\nSearch " << k;
	A.Search(k);

	cout << endl;
	system("pause");

	// Delete
	int z = rand() % 99 - 0;
	cout << "\n\nDelete bucket " << z ;
	A.DeleteBucket(z);
	cout << "\n\n\t\t\t\t\t===== HASH TABLE =====\n";
	A.TraverseHashTable();

	cout << endl;
	system("pause");
	return 0;
}