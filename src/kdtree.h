/* \author Aaron Brown */
// Quiz on implementing kd tree

#include "render/render.h"

struct Node
{
	pcl::PointXYZI point;
	int id;
	Node* left;
	Node* right;

	Node(pcl::PointXYZI arr, int setId)	: point(arr), id(setId), left(NULL), right(NULL) {}
};

struct KdTree
{
	Node* root;

	KdTree() : root(NULL) {}

	void insertHelper(Node** node, int depth, pcl::PointXYZI point, int id)
	{
		if (*node == NULL)
		{
			(*node) = new Node(point, id);
		}
		else
		{
			int cd = depth % 2;  // 3 dim kd-tree

			if (cd == 0) 
			{
				if (point.x < (*node)->point.x) 
					insertHelper(&(*node)->left, depth + 1, point, id);
				else 
					insertHelper(&(*node)->right, depth + 1, point, id);
			}
			else 
			{
				if (point.y < (*node)->point.y) 
					insertHelper(&(*node)->left, depth + 1, point, id);
				else 
					insertHelper(&(*node)->right, depth + 1, point, id);
			}
		}
	}

	void insert(pcl::PointXYZI point, int id)
	{
		// TODO: Fill in this function to insert a new point into the tree
		// the function should create a new node and place correctly with in the root 
		insertHelper(&root, 0, point, id);
	}

	void searchHelper(pcl::PointXYZI pivot, Node* node, int depth, float distanceTol, std::vector<int>& ids)
	{
		if (node != NULL)
		{
			if ((node->point.x >= (pivot.x - distanceTol) && (node->point.x <= (pivot.x + distanceTol))) && (node->point.y >= (pivot.y - distanceTol) && (node->point.y <= (pivot.y + distanceTol))))
			{
				float distance = sqrt((node->point.x - pivot.x) * (node->point.x - pivot.x) + (node->point.y - pivot.y) * (node->point.y - pivot.y));

				if (distance <= distanceTol) 
					ids.push_back(node->id);
			}
			if (depth % 2 == 0) // 3 dim kd-tree
			{
				if ((pivot.x - distanceTol) < node->point.x) 
					searchHelper(pivot, node->left, depth + 1, distanceTol, ids);

				if ((pivot.x + distanceTol) > node->point.x) 
					searchHelper(pivot, node->right, depth + 1, distanceTol, ids);
			}
			else 
			{
				if ((pivot.y - distanceTol) < node->point.y) 
					searchHelper(pivot, node->left, depth + 1, distanceTol, ids);
				if ((pivot.y + distanceTol) > node->point.y) 
					searchHelper(pivot, node->right, depth + 1, distanceTol, ids);
			}

		}
	}

	// return a list of point ids in the tree that are within distance of pivot
	std::vector<int> search(pcl::PointXYZI pivot, float distanceTol)
	{
		std::vector<int> ids;
		searchHelper(pivot, root, 0, distanceTol, ids);

		return ids;
	}
};




/*
// Structure to represent node of kd tree
struct Node
{
	std::vector<float> point;
	int id;
	Node* left;
	Node* right;

	Node(std::vector<float> arr, int setId)
	:	point(arr), id(setId), left(NULL), right(NULL)
	{}
};

struct KdTree
{
	Node* root;

	KdTree()
	: root(NULL)
	{}

	void insertHelper(Node** node,uint depth,std::vector<float>point,int id)
	{
		if(*node==NULL)
			*node = new Node(point,id);
		else
		{
			uint cd =depth%2;

			if(point[cd]< ((*node)->point[cd]))
				insertHelper(&((*node)->left),depth+1,point,id);
			else
				insertHelper(&((*node)->right),depth+1,point,id);	
		}
			
	}

	void insert(std::vector<float> point, int id)
	{
		// TODO: Fill in this function to insert a new point into the tree
		// the function should create a new node and place correctly with in the root 
		insertHelper(&root,0,point,id);
	}

	void searchHelper(std::vector<float> target,float distanceTol,std::vector<int>& ids ,Node* node, int depth)
	{
		if(node !=NULL)
		{
			if( (node->point[0]>=(target[0]-distanceTol) && node->point[0]<=(target[0]+distanceTol)) && (node->point[1]>=(target[1]-distanceTol) && node->point[1]<=(target[1]+distanceTol)))
			{
				float distance = sqrt((node->point[0]-target[0])*(node->point[0]-target[0])+(node->point[1]-target[1])*(node->point[1]-target[1]));
				if (distance <= distanceTol)
					ids.push_back(node->id);
			}

			if((target[depth%2]-distanceTol) < node->point[depth%2])
				searchHelper(target,distanceTol,ids,node->left,depth+1);

			if((target[depth%2]+distanceTol)> node->point[depth%2])
				searchHelper(target,distanceTol,ids,node->right,depth+1);	
		}


	}



	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(std::vector<float> target, float distanceTol)
	{
		std::vector<int> ids;
		searchHelper(target,distanceTol,ids,root,0);

		return ids;
	}
	

};*/




