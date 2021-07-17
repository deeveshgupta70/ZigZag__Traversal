// function for Diameter Calculation
// function LevelOrder Level By Level Traversal
// function To Remove Leaf Node
// Funtion For ZigZag Traversal
// Function To Check Balance Tree




#include<bits/stdc++.h>

using namespace std;

#define Fast1 ios_base::sync_with_stdio(0)
#define Fast2 cin.tie(0)
#define Fast3 cout.tie(0)
#define max(a, b) (a < b ? b : a)
#define min(a, b) ((a > b) ? b : a)
#define mod 1e9 + 7
#define FOR(a, c) for (int(a) = 0; (a) < (c); (a)++)
#define FORL(a, b, c) for (int(a) = (b); (a) <= (c); (a)++)
#define FORR(a, b, c) for (int(a) = (b); (a) >= (c); (a)--)
#define INF 1000000000000000003
typedef long long int ll;
typedef short int SI;
typedef vector<int> vi;
typedef pair<int, int> pi;
#define F first
#define S second
#define PB push_back
#define POB pop_back
#define MP make_pair

class treeNode
{
public:
	int data;
	treeNode* left;
	treeNode* right;
	treeNode(int data){
		this->data = data;
		left = NULL;
		right = NULL;
	}
	~treeNode(){
		delete left;
		delete right;
	}
	
};

class List{  // for level wise link list creation
    public:
    int data;
    List* next;
    
    //Constructor of List Class
    List(int data)
    {
        this->data = data;
        next = NULL;
    }
};

treeNode* builtTree(){  // Creating Tree 

	// cout<<"\n Enter root :";
	int rootData;
	cin>>rootData;
	treeNode* root = new treeNode(rootData);

	queue<treeNode*> node;
	node.push(root);

	while(!node.empty()){

		treeNode* ptr = node.front();
		node.pop();

		int val;
		// cout<<"\n Enter Left of "<<ptr->data<<" :";
		cin>>val;

		if( val != -1){
			ptr->left = new treeNode(val);
			node.push(ptr->left);
		}

		// cout<<"\n Enter right of "<<ptr->data<<" :";
		cin>>val;

		if(val != -1){
			ptr->right = new treeNode(val);
			node.push(ptr->right);
		}

	}

	return root;
}

pair<int,int> getDiameter(treeNode* root){ // calculation of diameter & height Simultaneously

	pair<int,int> res;
	if(!root){
		res = make_pair(0,0);
		return res;
	}

	pair<int,int> left = getDiameter(root->left);
	pair<int,int> right = getDiameter(root->right);

	int lh = left.F;
	int ld = left.S;
	int rh = right.F;
	int rd = right.S;

	int height = 1 + max(lh,rh);
	int diameter = max(lh + rh,max(rd,ld));
	res = make_pair(height,diameter);

	return res;
}

pair<int,bool> checkBalance(treeNode* root){ // Check the Tree is Balance Or Not

	pair<int,bool> res;
	if( !root){

		res = make_pair(0,true);
		return res;
	}

	pair<int,bool> left = checkBalance(root->left);
	pair<int,bool> right = checkBalance(root->right);

	int height = 1 + max(left.F,right.F);
	bool check = ((left.S && right.S) && ((abs(left.F - right.F) == 1) || (abs(left.F - right.F) == 0)));
	res = make_pair(height,check);
	return res;
}// return height & balance( -1 <= leftHeight - rightHeight <= 1);

void levelWiseTraversal(treeNode* root){
	queue<treeNode*> node;
	if( !root) return ;

		node.push(root);
	while(!node.empty()){

		int count = node.size();

		while(count--){

			treeNode* ptr = node.front();
			cout<< ptr->data<<" ";
			node.pop();

			if(ptr->left){
				node.push(ptr->left);
			}
			if(ptr->right){
				node.push(ptr->right);
			}
		}
		cout<<"\n";
	} // Level by Level Traversal
}	

treeNode* removeLeaf(treeNode* root){

	if( !root) return NULL;

	if( !root->left && !root->right){
		delete(root);
		return NULL;
	}

	root->left = removeLeaf(root->left);
	root->right = removeLeaf(root->right);

	return root;  // Remove Leaf Node Form Tree
}

vector<List*> createList(treeNode* root){
    
    vector<List*> res;
    if(!root) return res;
    
    queue<treeNode* > node;
    node.push(root);
    
    while(!node.empty()){
        
        int count  = node.size();
        List* head = NULL;
        List* last = NULL;
        
        while(count--){
            treeNode* ptr = node.front();
            List* temp = new List(ptr->data);
            node.pop();
            
            if( head == NULL){
                head = temp;
                last = temp;
            }else{
                last->next = temp;
                last = temp;
            }
            
            if(ptr->left) node.push(ptr->left);
            
            if(ptr->right) node.push(ptr->right);
        }
        res.push_back(head);
    }
    
    return res; // Creating vec. of LinkList Head
}

void output(List* head){
    
    List* ptr = head;
    
    while(ptr){
        cout<<ptr->data<<" -> ";
        ptr = ptr->next;
    }
    cout<< "NULL";    /// TO print Each List
    
}

void Display(vector<List*> res){
    cout<<"\n";
    for(int i = 0; i< res.size() ; i++){
        output(res[i]);
        cout<<"\n";
    } // To call Each List Head
}

void ZigZagTraversal(treeNode* root){

	if(!root) return ;

	stack<treeNode*> s1;
	stack<treeNode*> s2;

	s2.push(root);
	while( !s1.empty() || !s2.empty())
	{
		if(!s1.empty()){
			while(!s1.empty() ){
				treeNode* ptr = s1.top();
				cout<<ptr->data<<" ";
				s1.pop();

				if(ptr->left) s2.push(ptr->left);

				if(ptr->right) s2.push(ptr->right);
			}		
		}
		else{	
			while(!s2.empty()){
				treeNode* ptr = s2.top();
				cout<<ptr->data<<" ";
				s2.pop();

				if(ptr->right) s1.push(ptr->right);

				if(ptr->left) s1.push(ptr->left);

			}
		}
		cout<<"\n";

	}
}

int main(){

	treeNode* root = builtTree();

	pair<int,int> res= getDiameter(root);
	cout<<"levelWiseTraversal Before:\n";
	levelWiseTraversal(root);

	cout<<"\n ZigZag Traversal : \n";
	ZigZagTraversal(root);
	
	// cout<<"\n Level Order LinkLIst : ";
	// vector<List*> head = createList(root);
	// Display(head);
// 	cout<<"levelWiseTraversal After:\n";
// 	root = removeLeaf(root);
// 	levelWiseTraversal(root);
	cout<<"\n Diameter of Tree :"<< res.F;
	cout<<"\n Height of Tree : "<< res.S;
	pair<int,bool> balance = checkBalance(root);
	cout<<"\n Balanced Tree : "<< balance.S;
	return 0;
}
//1 2 3 4 5 -1 -1 6 -1 -1 7 8 -1 -1 9 10 -1 -1 -1 -1 -1
