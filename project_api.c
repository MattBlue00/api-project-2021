#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define INFINITE 2147483647

typedef struct{
	int key;
	int datum;
}node;

int AggiungiGrafo(int num_nodes, int indice);

int power_10(unsigned char exp);

void prog(node* arr, int d, int k);

int Dijkstra(int graph[], int num_nodes);

int parent(int i);
int left_child(int i);
int right_child(int i);
node* swap(node* a, int pos1, int pos2);
void insert(node* a, int data, int k, int ind);
void max_heapify(node* a, int i, int n);
void print_heap(node* a, int k, int len);
void cancella_max(node* a, int k);

int main(void){
    
    int d=0, k=0;
    int i=1000000, num=0;
	unsigned char sel=0;
	unsigned char j=7;
	node* arr;
    
    while(1){
        sel=getchar_unlocked();
        if(sel==32){
            num=num/(power_10(j));
            d=num;
            i=1000000;
            j=7;
            num=0;
        }
        else if(sel==10){
            num=num/(power_10(j));
            k=num;
            break;
        }
        else{
            num=num+((sel-48)*i);
            i=i/10;
            j--;
        }
    }

	arr=malloc(k*sizeof(node));
    prog(arr, d, k);
	free(arr);

    return 0;

}

void prog(node* arr, int d, int k){
    
    int len=0;
	char sel=0;
	int i=0;
    int sum=0;

    for(i=0; i<k; i++)
        arr[i].datum=INFINITE;

    while(1){
        sel=getchar_unlocked(); // chooses which function to call
        if(sel==65){
            for(i=0; i<12; i++)
                getchar_unlocked();
            sum=AggiungiGrafo(d, len);
            if(sum>=arr[0].datum){
            }
            else{
				cancella_max(arr, k);
                insert(arr, sum, k, len);
            }
            len++;
        }
        else{
            if(sel==84){
                for(i=0; i<4; i++)
                    getchar_unlocked();
                print_heap(arr, k, len);
            }
            else // end of input
				break;
        }
    }
}

int AggiungiGrafo(int num_nodes, int index){
    
    int i=0, j=0;
    int sum=0;
    int num=0, count=1000000;
	unsigned char temp=0, figures_left=7;
    int matrix[num_nodes*num_nodes];

    getchar_unlocked();
    for(i=0; i<num_nodes; i++){
        j=0;
        while(j!=num_nodes){
            temp=getchar_unlocked();
            if(temp==44){
                num=num/(power_10(figures_left));
                matrix[(i*num_nodes)+j]=num;
                j++;
                count=1000000;
                figures_left=7;
                num=0;
            }
            else if(temp!=10){
                num=num+((temp-48)*count);
                count=count/10;
                figures_left--;
            }
            else{
                num=num/(power_10(figures_left));
                matrix[(i*num_nodes)+j]=num;
                j++;
                count=1000000;
                figures_left=7;
                num=0;
            }
        }
    }
    
    sum=Dijkstra(matrix, num_nodes);
    return sum;
    
}

int power_10(unsigned char exp){
    
    int res=1;
	unsigned char i=0;
    
    for(i=0; i<exp; i++)
        res=res*10;
    return res;
    
}

int Dijkstra(int graph[], int num_nodes){
    
    int distance[num_nodes];
    int i, count=0, v, u;
    int sum=0;
    bool visited[num_nodes]; // visited[i] will be true if vertex i is processed
    int minimum;
    
    for(i=0; i<num_nodes; i++){
        distance[i]=INFINITE;
        visited[i]=false;
    }
    distance[0]=0;
    
    for(i=1; i<num_nodes; i++){
        if(graph[i]!=0)
            break;
        count++;
    }
    if(count==num_nodes-1)
        return 0;
    
    for(count=0; count<num_nodes-1; count++){
        u=0;
        minimum=INFINITE;
        for(v=0; v<num_nodes; v++){
            if(distance[v]<=minimum && visited[v]==false){
                u=v;
                minimum=distance[v];
            }
        }
        visited[u]=true;
        for(v=0; v<num_nodes; v++){
            if(!visited[v] && graph[(u*num_nodes)+v] && distance[u]!=INFINITE && distance[u]+graph[(u*num_nodes)+v]<distance[v])
                distance[v]=distance[u]+graph[(u*num_nodes)+v];
        }
    }
    
    for(i=1;i<num_nodes;i++){
        if(distance[i]==INFINITE)
            continue;
        else
            sum=sum+distance[i];
    }
    return sum;
    
}

int parent(int i){

    return (i-1)/2;

}

int left_child(int i){

    return 2*i+1;

}

int right_child(int i){

    return 2*i+2;

}

node* swap(node* a, int pos1, int pos2){

	int temp_key=0, temp_datum=0;

	temp_datum=a[pos1].datum;
	temp_key=a[pos1].key;
	a[pos1].datum=a[pos2].datum;
	a[pos1].key=a[pos2].key;
	a[pos2].datum=temp_datum;
	a[pos2].key=temp_key;

	return a;

}

void insert(node* a, int data, int k, int ind) {
    
    int i=0, pos=0;

    a[k-1].datum=data;
	a[k-1].key=ind;
    i=k-1;
    while(i>0){
		pos=parent(i);
		if(a[pos].datum>=a[i].datum)
			break;
		a=swap(a, pos, i);
        i=pos;
    }

}

void max_heapify(node* a, int n, int k){
    
    int left=0, right=0, posmax=0;

	left=left_child(n);
	right=right_child(n);

    if(left<k && a[left].datum>a[n].datum)
        posmax=left;
    else
        posmax=n;
    
    if(right<k && a[right].datum>a[posmax].datum)
        posmax=right;
    if(posmax!=n){
        a=swap(a, n, posmax);
        max_heapify(a, posmax, k);
    }

}

void cancella_max(node* a, int k){

 	a[0].datum=a[k-1].datum;
	a[0].key=a[k-1].key;
	a[k-1].datum=-1; // no need to change the key: it will be overwritten without if clauses
 	max_heapify(a, 0, k);

}

void print_heap(node* a, int k, int len){
    
	int i=0, lim=0;
    
    if(len<k)
        lim=len;
    else
        lim=k;
    
    for(i=0; i<lim; i++){
		if(a[i].datum==INFINITE)
			lim++;
		else{
			if(i+1!=lim)
				printf("%d ", a[i].key);
			else
				printf("%d", a[i].key);
		}
    }
    printf("\n");

}
