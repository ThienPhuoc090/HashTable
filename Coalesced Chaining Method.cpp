#include<iostream>
using namespace std;

// Bài toán: Xây dựng chương trình bảng băm(hashtable) với phương pháp xử lý đụng độ: Coalesced Chaining Method(Nối kết hợp nhất)

// Cấu trúc bảng băm và hàm khởi tạo 
// Định nghĩa hàm băm với giả định 10 phần tử 
#define M 10
struct Node
{
	int key;
	int next;
};
typedef Node* HashTable[M];

void InitHashTable(HashTable& HT) // Khởi tạo mảng: cấp phát bộ nhớ cho từng Node
{
	for (int i = 0; i < M; i++)
	{
		HT[i] = NULL;
	}
}
int Hash(int k) // Hàm băm 
{
	return k % M;
}

static int n = 0;
// Cụm hàm thêm nút vào bảng băm 
void Add(Node*& l, int k) // Thêm Node vào đuôi của danh sách liên kết đơn 
{
	Node* newNode = new Node{ k, -1 };
	l = newNode;
	n++;
}

void InsertNode(HashTable& HT, int k) // Thêm nút vào bảng băm 
{

	int i = Hash(k);

	if (HT[i] == NULL)
		Add(HT[i], k);
	else
	{
		for (int j = M - 1; j >= 0; j--)
		{
			if (HT[j] == NULL)
			{
				Add(HT[j], k);
				if (HT[i]->next == -1)
					HT[i]->next = j;
				else {
					int t = i;
					while (HT[t]->next != -1)
					{
						t = HT[t]->next;
					}
					HT[t]->next = j;
				}
				return;
			}
		}
	}

}

void TraverseHashTable(HashTable HT)
{
	for (int i = 0; i < M; i++)
	{
		if (HT[i])
		{
			if (HT[i]->next == -1)
				cout << "Bucket: " << i << ": " << HT[i]->key << ", Next: " << "NULL" << endl;
			else 
				cout << "Bucket: " << i << ": " << HT[i]->key << ", Next: " << HT[i]->next << endl;
		}

	}
}


int main()
{
	HashTable mHashTable;
	InitHashTable(mHashTable);

	InsertNode(mHashTable, 20);
	InsertNode(mHashTable, 35);
	InsertNode(mHashTable, 16);
	InsertNode(mHashTable, 40);
	InsertNode(mHashTable, 45);
	InsertNode(mHashTable, 25);
	InsertNode(mHashTable, 32);
	InsertNode(mHashTable, 37);
	InsertNode(mHashTable, 22);
	InsertNode(mHashTable, 55);

	cout << "\n\n\t========== HashTable ==========\n";
	TraverseHashTable(mHashTable);

	return 0;
}