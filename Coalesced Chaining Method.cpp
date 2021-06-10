// Lưu ý: Chương trình dưới đây vẫn chưa hoàn thiện


#include<iostream>
using namespace std;

// Bài toán: Xây dựng chương trình bảng băm(hashtable) với phương pháp xử lý đụng độ: Coalesced Chaining Method(Nối kết hợp nhất)

// Cấu trúc bảng băm và hàm khởi tạo 
// Định nghĩa hàm băm với giả định 10 phần tử 
#define M 10
struct Node
{
	int key;
	Node* next;
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
	if (n == M - 1)
	{
		cout << "\nHashTable is Full!";
	}
	Node* newNode = new Node{ k, NULL };
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
				HT[i]->next = HT[j];
				Add(HT[j], k);
				return;
			}

		}
	}

}

// Hàm tìm kiếm khóa trong bảm băm
Node* SearchNode(HashTable HT, int k)
{
	int i = Hash(k);
	Node* p = HT[i];
	while (p != NULL && p->key != k)
		p = p->next;
	if (p == NULL)
		return NULL;
	return p;
}

void SearchResult(HashTable HT, int k)
{
	Node* result = SearchNode(HT, k);
	if (result == NULL)
		cout << "Not found!";
	else
		cout << "Found!";
}


void DeleteHead(Node*& l)
{
	if (l != NULL)
	{
		Node* p = l;
		l = l->next;
		delete p;
	}
}
void DeleteAfter(Node*& q)
{
	Node* p = q->next;
	if (p != NULL)
	{
		q->next = p->next;
		delete p;
	}
}
void DeleteNode(HashTable& HT, int k)
{
	int i = Hash(k);
	Node* p = HT[i];
	Node* q = p;
	while (p != NULL && p->key != k)
	{
		q = p; // Lưu lại địa chỉ của phần tử trước đó
		p = p->next;
	}
	if (p == NULL)
		cout << k << " not found!" << endl;
	else if (p == HT[i])
		DeleteHead(HT[i]);
	else DeleteAfter(q);
}

// Cụm hàm duyệt qua bảng băm 
void Traverse(Node* p) // Duyệt DSLK
{
	while (p != NULL)
	{
		cout << p->key << ' ';
		p = p->next;
	}
	cout << endl;
}

void TraverseHashTable(HashTable HT)
{
	for (int i = 0; i < M; i++)
	{
		cout << "Bucket: " << i << ": ";
		Traverse(HT[i]);
	}
}


int main()
{
	HashTable mHashTable;
	InitHashTable(mHashTable);

	InsertNode(mHashTable, 0);
	InsertNode(mHashTable, 1);
	InsertNode(mHashTable, 2);
	InsertNode(mHashTable, 3);
	InsertNode(mHashTable, 10);
	InsertNode(mHashTable, 13);
	InsertNode(mHashTable, 9);
	InsertNode(mHashTable, 11);

	cout << "\n\n\t========== HashTable ==========\n";
	TraverseHashTable(mHashTable);

	DeleteNode(mHashTable, 3);
	DeleteNode(mHashTable, 13);
	DeleteNode(mHashTable, 9);
	cout << "\n\n\t========== HashTable after Delete ==========\n";
	TraverseHashTable(mHashTable);

	cout << "\n\tSearch: 10\n\t";
	SearchResult(mHashTable, 10);
	cout << endl;
	system("pause");
	return 0;
}