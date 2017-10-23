#ifndef _GraphLib_BinaryHeapMap_h_
#define _GraphLib_BinaryHeapMap_h_


//    A simple binary min-heap serving as a priority queue
//    - takes an array as the input, with elements having a key property
//    - elements will look like this:
//        {
//            key: "... key property ...",
//            value: "... element content ..."
//        }
//    - provides Insert(), GetMin(), ExtractMin() and Heapify()
//    - example usage (e.g. via the Firebug or Chromium console):
//        var x = {foo: 20, hui: "bla"};
//        var a = new BinaryMinHeap([x,{foo:3},{foo:10},{foo:20},{foo:30},{foo:6},{foo:1},{foo:3}],"foo");
//        console.log(a.ExtractMin());
//        console.log(a.ExtractMin());
//        x.foo = 0; // update key
//        a.Heapify(); // call this always after having a key updated
//        console.log(a.ExtractMin());
//        console.log(a.ExtractMin());
//    - can also be used on a simple array, like [9,7,8,5]

namespace GraphLib {

class BinaryMinHeap {
	
	// Binary tree stored in an array, no need for a complicated data structure
	VectorMap<int64, Node*> tree;
	
public:
	
	BinaryMinHeap();
	BinaryMinHeap(ArrayMap<String, Node>& nodes);
	
	//  Helper function to swap elements with their parent
	//  as long as the parent is bigger
	void BubbleUp(int i);
	
	//  Helper function to swap elements with the smaller of their children
	//  as long as there is one
	void BubbleDown(int i);
	
	//  Insert a new element with respect to the heap property
	//  1. Insert the element at the end
	//  2. Bubble it up until it is smaller than its parent */
	void Insert(int64 hash, Node& element);
	
	// Only show us the minimum
	Node* GetMin();
	
	//  Return and remove the minimum
	//  1. Take the root as the minimum that we are looking for
	//  2. Move the last element to the root (thereby deleting the root)
	//  3. Compare the new root with both of its children, swap it with the
	//    smaller child and then check again from there (bubble down)
	Node* ExtractMin();
	void Heapify();
};

}

#endif
