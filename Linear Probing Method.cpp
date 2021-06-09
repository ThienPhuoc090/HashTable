#include <iostream>
#include<cmath>
#include<ctime>
#include<iomanip>
using namespace std;

#define M 100
#define NULLKEY false
struct TagNode
{
	int key;
	bool flag;
};
typedef struct TagNode NODE;

int HashFunc(int k)
{
	return ((int)k % 10);
}
class HashTable
{
private:
	NODE arr[M];
	int n;
public:
	HashTable()
	{
		this->n = 0;
		for (int i = 0; i < M; i++)
		{
			this->arr[i].key = -1;
			this->arr[i].flag = NULLKEY;	
		}
	}
	~HashTable(){}
	
	bool isEmpty() { return((n == 0) ? true : false); }
	bool isFull() { return ((n == M) ? true : false); }

	void Insert(int k)
	{
		if (this->isFull() == true)
		{
			return;
		}
		else
		{
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

	void InsertArray(int a[], int n)
	{
		for (int i = 0; i < n; i++)
		{
			this->Insert(a[i]);
		}
	}

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
			else cout << "Bucket " << i << ": NULLKEY" << "\t";
			if (line ==5)
			{
				cout << endl;
				line = 0;
			}
		}
	}
};

int main()
{
	HashTable A;
	int n = 100;
	int* a = new int[n];
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		a[i] = rand() % 200 - 90;
	A.InsertArray(a, n);
	A.TraverseHashTable();
	if(A.isFull()==true)
		cout << "\n\n\t HashTable is FULL! Can't insert new key!";
	delete[]a;
	cout << endl;
	system("pause");
	return 0;
}