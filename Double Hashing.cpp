#include<iostream>
#include<cmath>
#include<ctime>
using namespace std;
#define PRIME 7
// Bài toán: Xây dựng chương trình bảng băm(hashtable) với phương pháp xử lý đụng độ: Double Hashing (Băm Kép)
// Xây dựng lớp băm 
class DoubleHash
{
private:
	int size;
	int* hashtable = new int[size];
	int n;
public:
	DoubleHash(int a) : size(a)
	{
		for (int i = 0; i < this->size; i++)
			this->hashtable[i] = -1;
	}
	DoubleHash() // Phương thức khởi tạo 
	{
		this->n = this->size = 0;
		this->hashtable = NULL;
	}
	~DoubleHash() {} // Phương thức hủy

	bool isEmpty() { return((n == 0) ? true : false); } // Hàm logic Kiểm tra bảng băm có rỗng hay không? 
	bool isFull() { return ((n == size) ? true : false); } // Hàm logic Kiểm tra bảng băm có đầy hay không?


	void InsertArray(int a[], int m) // Hàm thêm các key vào bảng băm bằng mảng 1 chiều các số nguyên 
	{
		this->size = m;
		for (int i = 0; i < m; i++)
			this->Insert(a[i]);
	}

	// Cụm hàm thực hiện băm kép để xử lý đụng độ
	int BasicHash(int key){ return (key % (this->size)); }
	int AdvancedHash(int key) { return (PRIME - (key % PRIME)); }
	void Insert(int k) // Hàm thêm key vào bảng băm
	{
		if (this->isFull() == true)
		{
			return;
		}
		else if (this->size != 0)
		{
			int index = BasicHash(k);
			if (hashtable[index] != -1)
			{
				int indexcustom = AdvancedHash(k);
				int i = 1;
				while (1)
				{
					int newindex = (index + i * indexcustom) % this->size;
					if (hashtable[newindex] == -1)
					{
						hashtable[newindex] = k;
						this->n++;
						break;
					}
					i++;
				}
			}
			else
			{
				hashtable[index] = k;
				this->n++;
			}

		}

	}

	// Hàm Xuất tuần tự các bucket trong bảng băm 
	void TraverseHashTable()
	{
		for (int i = 0; i < size; i++)
		{
			if (this->hashtable[i] != -1)
				cout << "\nSlot " << i << ": " << this->hashtable[i] << "\t\t";
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
				if (this->hashtable[i] == k)
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
		else if (k >= 0 && k < this->size) // Điều kiện xử lý lệnh xóa ngăn: đầu vào phải là số tự nhiên
		{
			hashtable[k] = -1;
			this->n--;
			return;
		}
		else cout << "\nNot found this Slot! Please try again!";
	}
};

int main()
{
	int n = rand() % 50 - 0;
	int* a = new int[n];
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		a[i] = rand() % 100 - 0;

	// DoubleHash
	cout << "\n\n\t\t\t\t\t===== HASH TABLE =====\n";
	DoubleHash A(n);
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