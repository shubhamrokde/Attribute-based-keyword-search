#include<bits/stdc++.h> 
using namespace std; 
  
int c=1;
vector<vector<int > > r;
// An expression tree node 
struct et 
{ 
    char value; 
    et* left, *right; 
    vector<int> v;
    
}; 
  
// A utility function to check if 'c' 
// is an operator 
bool isOperator(char c) 
{ 
    if (c == '+' ||  c == '*' ) 
        return true; 
    return false; 
} 

void printInorder(et *t) 
{ 
    if(t) 
    { 
        printInorder(t->left); 
        printf("%c ", t->value); 
        printInorder(t->right); 
    } 
}   
// Utility function to do inorder traversal 
void inorder(et *t) 
{ 
    if(t) 
    { 
        if(isOperator(t->value)){
            while(t->v.size() != c){
                t->v.push_back(0);				
            }	
            if(t->value == '+'){
                t->left->v = t->v;
                t->right->v = t->v;
            }
            else{
                while(t->left->v.size()!= c){
                    t->left->v.push_back(0);
                }
                t->left->v.push_back(-1);
                t->right->v = t->v;
                t->right->v.push_back(1);
                c++;							
            }
        }
        inorder(t->left);  
        inorder(t->right);
        if(!t->left && !t->right){
            r.push_back(t->v);
        }
        		 
    } 
} 
  
// A utility function to create a new node 
et* newNode(int v) 
{ 
    et *temp = new et; 
    temp->left = temp->right = NULL; 
    temp->value = v; 
    return temp; 
}; 
  
// Returns root of constructed tree for given 
// postfix expression 
et* constructTree(char postfix[]) 
{ 
    stack<et *> st; 
    et *t, *t1, *t2; 
  
    // Traverse through every character of 
    // input expression 
    for (int i=0; i<strlen(postfix); i++) 
    { 
        // If operand, simply push into stack 
        if (!isOperator(postfix[i])) 
        { 
            t = newNode(postfix[i]); 
            st.push(t); 
        } 
        else // operator 
        { 
            t = newNode(postfix[i]); 
  
            // Pop two top nodes 
            t1 = st.top(); // Store top 
            st.pop();      // Remove top 
            t2 = st.top(); 
            st.pop(); 
  
            //  make them children 
            t->right = t1; 
            t->left = t2; 
  
            // Add this subexpression to stack 
            st.push(t); 
        } 
    } 
  
    //  only element will be root of expression 
    // tree 
    t = st.top(); 
    st.pop(); 
  
    return t; 
} 
  
// Driver program to test above 
int main() 
{ 
    char postfix[] = "EAB*CD*+AB+CD+*+*"; 
    et* root = constructTree(postfix); 
    
    printf("infix expression is \n"); 
    printInorder(root);
    root->v.push_back(1);
    inorder(root);
    cout << "$$" << endl; 
    for(int i=0 ;i<r.size();i++){
        while(r[i].size() != c){
                r[i].push_back(0);				
            }	
    } 
    fstream myfile;
    myfile.open("rmatrix.txt",fstream::out);
    myfile << r.size()<< " "; 
    myfile << r[0].size()<< " "<<endl; 
       for(int i=0 ;i<r.size();i++){
        for(int j=0;j<r[i].size();j++){
                myfile << r[i][j]<< " "; 				
            }	
            myfile<< std::endl;
    } 
    myfile.close();
    
    return 0; 
} 

