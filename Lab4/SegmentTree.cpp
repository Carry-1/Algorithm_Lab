#include<iostream>
#include<algorithm>
#include<vector>
#include<ctime>
#include<fstream>
using namespace std;

enum class Colors {
	Red,
	Black
};
Colors operator!(Colors& temp) {
	if (temp == Colors::Red)
		return Colors::Black;
	else
		return Colors::Red;
}
ostream& operator<<(ostream& out, Colors& temp) {
	if (temp == Colors::Black)
		out << "Black";
	else
		out << "Red";
	return out;
}

class Node {
public:
	int left;
	int right;
	int max;
	Colors Color;
	Node* Parent;
	Node* LChild;
	Node* RChild;
	Node(int left,int right,int max, Colors color, Node* Parent, Node* Null) :left(left),right(right), max(max),Color(color), Parent(Parent), LChild(Null), RChild(Null) {}
	Node* GetUncle() {
		return Parent == Parent->Parent->LChild ? Parent->Parent->RChild : Parent->Parent->LChild;
	}
};

class RB_Tree {
public:
	Node* root;
	Node* Null;
	RB_Tree() { root = nullptr; Null = new Node(-1,-1,-65536, Colors::Black, nullptr, nullptr); }
	void LeftRotate(Node* node) {
		Node* RightChild = node->RChild;
		node->RChild = node->RChild->LChild;
		node->RChild->Parent = node;
		RightChild->LChild = node;
		RightChild->Parent = node->Parent;
		if (node->Parent->LChild == node)
			node->Parent->LChild = RightChild;
		else
			node->Parent->RChild = RightChild;
		node->Parent = RightChild;
		if (node == root)
			root = RightChild;
		node->max = max(node->right, max(node->LChild->max, node->RChild->max));
		node->Parent->max = max(node->Parent->right, max(node->Parent->LChild->max, node->Parent->RChild->max));
		return;
	}
	void RightRotate(Node* node) {
		Node* LeftChild = node->LChild;
		node->LChild = node->LChild->RChild;
		node->LChild->Parent = node;
		LeftChild->RChild = node;
		LeftChild->Parent = node->Parent;
		if (node->Parent->RChild == node)
			node->Parent->RChild = LeftChild;
		else
			node->Parent->LChild = LeftChild;
		node->Parent = LeftChild;
		if (node == root)
			root = LeftChild;
		node->max = max(node->right, max(node->LChild->max, node->RChild->max));
		node->Parent->max = max(node->Parent->right, max(node->Parent->LChild->max, node->Parent->RChild->max));
		return;
	}
};

ostream& operator<<(ostream& cout, RB_Tree& temp) {
	vector<Node*> arr1;
	vector<Node*> arr2;
	bool button = true;
	arr1.push_back(temp.root);
	string layer;
	while (!arr1.empty()) {
		Node* p = arr1.front();
		arr1.erase(arr1.begin());
		if (p == temp.Null) {
			cout << "Nil ";
			continue;
		}
		button = false;
		cout <<'['<< p->left <<','<<p->right<< "](" << p->Color << ",max= "<<p->max<<") ";
		arr2.push_back(p->LChild);
		arr2.push_back(p->RChild);
		if (arr1.empty()) {
			cout << endl;
			if (button == true)
				break;
			arr1 = arr2;
			arr2.clear();
			button = true;
		}
	}
	return cout;
}

void FixUpRBTree(RB_Tree& Tree, Node* node) {
	if (node->Parent->Color == Colors::Black)
		return;
	if (node->GetUncle()->Color == Colors::Red) {
		if (node->Parent->Parent->LChild == node->Parent)
			cout << "case 1 ";
		else
			cout << "case 4 ";
		node->Parent->Color = !node->Parent->Color;
		node->Parent->Parent->Color = !node->Parent->Parent->Color;
		node->GetUncle()->Color = !node->GetUncle()->Color;
		FixUpRBTree(Tree, node->Parent->Parent);
		//cout << endl;
		return;
	}
	if (node == node->Parent->LChild && node->Parent == node->Parent->Parent->RChild) {
		cout << "case 5 ";
		node = node->Parent;
		Tree.RightRotate(node);
	}
	else if (node == node->Parent->RChild && node->Parent == node->Parent->Parent->LChild) {
		cout << "case 2 ";
		node = node->Parent;
		Tree.LeftRotate(node);
	}
	node->Parent->Color = !node->Parent->Color;
	node->Parent->Parent->Color = !node->Parent->Parent->Color;
	if (node == node->Parent->LChild && node->Parent == node->Parent->Parent->LChild) {
		cout << "case 3 ";
		Tree.RightRotate(node->Parent->Parent);
	}
	else if (node == node->Parent->RChild && node->Parent == node->Parent->Parent->RChild) {
		cout << "case 6 ";
		Tree.LeftRotate(node->Parent->Parent);
	}
	//cout << endl;
	return;
}

void Insert(RB_Tree& Tree, int& val,int& right) {
	if (Tree.root == nullptr) {
		Tree.root = new Node(val,right,right, Colors::Black, Tree.Null, Tree.Null);
		return;
	}
	Node* temp = Tree.root;
	while (temp != Tree.Null) {
		if (temp->left <= val) {
			if (temp->RChild == Tree.Null) {
				Node* node = new Node(val, right, right, Colors::Red, temp, Tree.Null);
				temp->RChild = node;
				Node *p=node;
				while(p->Parent->max<p->max){
					p->Parent->max=p->max;
					p=p->Parent;
				}
				FixUpRBTree(Tree, node);
				Tree.root->Color = Colors::Black;
				break;
			}
			else
				temp = temp->RChild;
		}
		else {
			if (temp->LChild == Tree.Null) {
				Node* node = new Node(val, right, right, Colors::Red, temp, Tree.Null);
				temp->LChild = node;
				Node* p=node;
				while(p->Parent->max<p->max){
					p->Parent->max=p->max;
					p=p->Parent;
				}
				FixUpRBTree(Tree, node);
				Tree.root->Color = Colors::Black;
				break;
			}
			else
				temp = temp->LChild;
		}
	}
	return;
}

Node* IntervalSearch(RB_Tree& Tree, pair<int, int>& Query) {
	Node* temp = Tree.root;
	while (temp != Tree.Null) {
		if (temp->left <= Query.second && temp->right >= Query.first)
			break;
		if (temp->LChild != Tree.Null && temp->LChild->max >= Query.first)
			temp = temp->LChild;
		else
			temp = temp->RChild;
	}
	return temp;
}

int main() {
	RB_Tree Tree;
	vector<pair<int,int>> arr;
	ifstream File;
	File.open("SegmentInsert.txt", ios::in);
	int num = 0;
	while (File >> num) {
		arr.resize(num);
		for (int i = 0; i < num; ++i) {
			
			File >> arr[i].first >> arr[i].second;
		}
	}
	for (int i = 0; i < num; ++i) {
		//cout << "Insert:" << arr[i] << endl;
		Insert(Tree, arr[i].first, arr[i].second);
	}
	cout<<"22222";
	cout<<endl<< Tree << endl;
	//freopen("SegmentTree.txt", "w", stdout);
	cout << Tree << endl;
	pair<int, int> Query;
	while (true) {
		cout << "输入你要查询的区间(数字间用空格间隔)" << endl;
		cin >> Query.first >> Query.second;
		Node* ans = IntervalSearch(Tree, Query);
		if (ans == Tree.Null)
			cout << "没有找到重叠区间"<<endl;
		else
			cout << '[' << ans->left << ',' << ans->right << "]"<<endl;
	}
	return 0;
}




