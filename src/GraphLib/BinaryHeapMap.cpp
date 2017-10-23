#include "GraphLib.h"

namespace GraphLib {

BinaryMinHeap::BinaryMinHeap() {}

BinaryMinHeap::BinaryMinHeap(ArrayMap<String, Node>& nodes) {
	// insert the input elements one by one only when we don't have a key property (TODO can be done more elegant) */
	for(int i = 0; i < nodes.GetCount(); i++) {
		Insert(nodes.GetKey(i).GetHashValue(), nodes[i]);
	}
}

// Calculate the index of the parent or a child
#define parent(x)	(int)(((x) - 1) / 2)
#define right(x)	(int)(2 * (x) + 2)
#define left(x)		(int)(2 * (x) + 1)

//  Helper function to swap elements with their parent
//  as long as the parent is bigger
void BinaryMinHeap::BubbleUp(int i) {
	int p = parent(i);

	while ((p >= 0) && (tree[i]->distance < tree[p]->distance)) {
		// swap with parent
		Swap(tree[i], tree[p]);
		
		// go up one level
		i = p;
		p = parent(i);
	}
}

//  Helper function to swap elements with the smaller of their children
//  as long as there is one
void BinaryMinHeap::BubbleDown(int i) {
	int l = left(i);
	int r = right(i);

	// as long as there are smaller children
	while (l < tree.GetCount() && tree[l] && (tree[i]->distance > tree[l]->distance) || r < tree.GetCount() && tree[r] && (tree[i]->distance > tree[r]->distance)) {
		
		// find smaller child
		int child =
			l < tree.GetCount() && tree[l] ?
				r < tree.GetCount() && tree[r] ?
					tree[l]->distance > tree[r]->distance ? r : l :
					l :
				l;
		
		// swap with smaller child with current element
		Swap(tree[i], tree[child]);
		
		// go up one level
		i = child;
		l = left(i);
		r = right(i);
	}
}


//  Insert a new element with respect to the heap property
//  1. Insert the element at the end
//  2. Bubble it up until it is smaller than its parent */
void BinaryMinHeap::Insert(int64 hash, Node& element) {
	
	// insert element at the end
	tree.Add(hash, &element);
	
	// bubble up the element
	BubbleUp(tree.GetCount() - 1);
}


// Only show us the minimum
Node* BinaryMinHeap::GetMin() {
	if (tree.GetCount() <= 1) return NULL;
	return tree[0];
}

//  Return and remove the minimum
//  1. Take the root as the minimum that we are looking for
//  2. Move the last element to the root (thereby deleting the root)
//  3. Compare the new root with both of its children, swap it with the
//    smaller child and then check again from there (bubble down)
Node* BinaryMinHeap::ExtractMin() {
	Node* result = GetMin();

	// move the last element to the root or empty the tree completely
	// bubble down the new root if necessary
	if (tree.GetCount() == 1)
		tree.Clear();
	else {
		tree[0] = tree.Pop();
		BubbleDown(0);
	}

	return result;
}

void BinaryMinHeap::Heapify() {
	for (int start = (tree.GetCount() - 2) / 2; start >= 0; start--)
		BubbleDown(start);
}

}
