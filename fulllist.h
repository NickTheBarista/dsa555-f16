#include <iostream>
using namespace std;

template <typename T>
class DList{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{},Node* next=nullptr,Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};
	Node* head_;
	Node* tail_;
public:
	class const_iterator{
		friend class DList;
		Node* curr_;
		const_iterator(Node* p){
			curr_=p;
		}
	public:
		const_iterator(){
			curr_=nullptr;
		}
		const_iterator operator++(){
			//++it
			curr_=curr_->next_;
			return *this;
		}
		const_iterator operator++(int){
			//it++
			//duplicate current object (*this)
			const_iterator old=*this;
			//update our current object
			curr_=curr_->next_;

			return old;
		}
		const_iterator operator--(){
			//--it
			curr_=curr_->prev_;
			return *this;
		}
		const_iterator operator--(int){
			//it--
			//duplicate current object (*this)
			const_iterator old=*this;
			//update our current object
			curr_=curr_->prev_;

			return old;			
		}
		T operator*(){
			return curr_->data_;
		}
		bool operator==(const_iterator right){
			return curr_ == right.curr_;
		}
		bool operator!=(const_iterator right){
			return curr_ != right.curr_;

		}
	};
	class iterator:public const_iterator{

	};
	DList(){
		head_=new Node();  //head sentinel
		tail_=new Node();  //tail sentinel
		head_->next_=tail_;
		tail_->prev_=head_;
	}
	//returns an const_iterator to the
	//first node (first data node) in linked list
	const_iterator begin() const{
		return const_iterator(head_->next_);
	}
	//returns a const_iterator to the node
	//after the last node in the linked list
	const_iterator end() const{
		return const_iterator(tail_);

	}
	void push_front(const T& data){
		//head_ points to the front sentinel, so
		//the node that follows is the first node
		//in the linked list.  If that first node
		//is tail_ then the list is empty.
		Node* first=head_->next_;
		//make a node
		Node* nn=new Node(data,first,head_);
		head_->next_=nn;
		first->prev_=nn;		
		
	}
	void push_back(const T& data);
	void pop_front();
	void pop_back(){
		//check if list is empty
		//front sentinel's next does not point at back
		//sentinel, list is not empty
		if(head_->next_!=tail_){
			//this is the node we want to remove
			Node* last=tail_->prev_; 

			//this is the node before the one we want to remove
			Node* secondLast=last->prev_;

			//unlink last data node
			tail_->prev_= secondLast;
			secondLast->next_= tail_; //secondLast->next_=last->next_ is also ok

			//delete last data node
			delete last;
		}


	}
	void print() const{
		Node* it=head_->next_;
		while(it!=tail_){
			cout << it->data_ << endl;
			it=it->next_;
		}
	}
};

