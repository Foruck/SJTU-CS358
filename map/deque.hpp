#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include "exceptions.hpp"

#include <cstddef>

namespace sjtu { 

template<class T>
class deque {
public:
	struct node {
		node *next, *pre;
		T v;
		node(T &value) {
			v = value;
			next = pre = NULL;
		}
	};
	node *head, *tail;
	int tot;
	class const_iterator;
	class iterator {
	private:
		node* pointer;
		deque* belong;
	public:
		/**
		 * return a new iterator which pointer n-next elements
		 *   even if there are not enough elements, the behaviour is **undefined**.
		 * as well as operator-
		 */
		iterator(deque* d, node* p) :belong(d), pointer(p) {}

		iterator operator+(const int &n) const {
			//TODO
			int x = 0;
			while (pointer->next && x < n) {
				x++; pointer = pointer->next;
			}
			return *this;
		}
		iterator operator-(const int &n) const {
			//TODO
			int x = 0;
			while (pointer->pre && x < n) {
				x++; pointer = pointer->pre;
			}
			return *this;
		}
		// return th distance between two iterator,
		// if these two iterators points to different vectors, throw invalid_iterator.
		int operator-(const iterator &rhs) const {
			//TODO
			if (belong != rhs.belong) throw invalid_iterator();
			int x = 0;
			while (pointer && pointer != rhs.pointer)
		}
		iterator operator+=(const int &n) {
			//TODO
			int x = 0;
			while (pointer->next && x < n) {
				x++; pointer = pointer->next;
			}
			return *this;
		}
		iterator operator-=(const int &n) {
			//TODO
			int x = 0;
			while (pointer->pre && x < n) {
				x++; pointer = pointer->pre;
			}
			return *this;
		}
		/**
		 * TODO iter++
		 */
		iterator operator++(int) {
			iterator tmp = *this;
			pointer = pointer->next;
			return tmp;
		}
		/**
		 * TODO ++iter
		 */
		iterator& operator++() {
			pointer = pointer->next;
			return *this;
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int) {
			iterator tmp = *this;
			pointer = pointer->pre;
			return tmp;
		}
		/**
		 * TODO --iter
		 */
		iterator& operator--() {
			pointer = pointer->pre;
			return *this;
		}
		/**
		 * TODO *it
		 */
		T& operator*() const { return pointer->v; }
		/**
		 * TODO it->field
		 */
		T* operator->() const noexcept {
			return &pointer->v;
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		bool operator==(const iterator &rhs) const {
			return (belong == rhs.belong && pointer == rhs.pointer);
		}
		bool operator==(const const_iterator &rhs) const {
			return (belong == rhs.belong && pointer == rhs.pointer);
		}
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const {
			return !(belong == rhs.belong && pointer == rhs.pointer);
		}
		bool operator!=(const const_iterator &rhs) const {
			return !(belong == rhs.belong && pointer == rhs.pointer);
		}
	};
	class const_iterator {
		// it should has similar member method as iterator.
		//  and it should be able to construct from an iterator.
	private:
		// data members.
		node* pointer;
		deque* belong;
	public:
		const_iterator() {
			// TODO
			belong = NULL;
			pointer = NULL;
		}
		const_iterator(const const_iterator &other) {
			pointer = other.pointer;
			belong = other.belong;
		}
		const_iterator(const iterator &other) {
			pointer = other.pointer;
			belong = other.belong;
		}
		// And other methods in iterator.
		// And other methods in iterator.
		// And other methods in iterator.
	};
	/**
	 * TODO Constructors
	 */
	deque() {
		head = tail = NULL;
		tot = 0;
	}
	deque(const deque &other) {
		head = new node(other.head->v);
		tot = other.tot;
		node *now_other = other.head, *now = head, *tmp;
		int i = 1;
		while (now_other->next) {
			now->next = new node(now_other->next->v);
			tmp = now;
			now = now->next;
			now_other = now_other->next;
			now->pre = tmp;
			i++;
		}
		tail = now_other;
	}
	/**
	 * TODO Deconstructor
	 */
	~deque() {
		node *tmp = tail;
		while (tmp != head) {
			tmp = tmp->pre;
			delete tmp->next;
		}
		delete tmp;
	}
	/**
	 * TODO assignment operator
	 */
	deque &operator=(const deque &other) {
		if (this == &other) return *this;

		node *tmp = tail;
		while (tmp != head) {
			tmp = tmp->pre;
			delete tmp->next;
		}
		delete tmp;

		head = new node(other.head->v);
		tot = other.tot;
		node *now_other = other.head, *now = head;
		int i = 1;
		while (now_other->next) {
			now->next = new node(now_other->next->v);
			tmp = now;
			now = now->next;
			now_other = now_other->next;
			now->pre = tmp;
			i++;
		}
		tail = now_other;

		return *this;
	}
	/**
	 * access specified element with bounds checking
	 * throw index_out_of_bound if out of bound.
	 */
	T & at(const size_t &pos) {
		if (pos < 0 || pos >= tot) throw index_out_of_bound();
		int cnt = 0;
		node *now = head;
		while (cnt != pos) {
			cnt++;
			now = now->next;
		}
		return now->v;
	}
	const T & at(const size_t &pos) const {
		if (pos < 0 || pos >= tot) throw index_out_of_bound();
		int cnt = 0;
		node *now = head;
		while (cnt != pos) {
			cnt++;
			now = now->next;
		}
		return now->v;
	}
	T & operator[](const size_t &pos) {
		if (pos < 0 || pos >= tot) throw index_out_of_bound();
		int cnt = 0;
		node *now = head;
		while (cnt != pos) {
			cnt++;
			now = now->next;
		}
		return now->v;
	}
	const T & operator[](const size_t &pos) const {
		if (pos < 0 || pos >= tot) throw index_out_of_bound();
		int cnt = 0;
		node *now = head;
		while (cnt != pos) {
			cnt++;
			now = now->next;
		}
		return now->v;
	}
	/**
	 * access the first element
	 * throw container_is_empty when the container is empty.
	 */
	const T & front() const {
		if (!tot) throw container_is_empty();
		return head->v;
	}
	/**
	 * access the last element
	 * throw container_is_empty when the container is empty.
	 */
	const T & back() const {
		if (!tot) throw container_is_empty();
		return tail->v;
	}
	/**
	 * returns an iterator to the beginning.
	 */
	iterator begin() {
		return iterator(this, head);
	}
	const_iterator cbegin() const {
		return const_iterator(this, head);
	}
	/**
	 * returns an iterator to the end.
	 */
	iterator end() {
		return iterator(this, tail);
	}
	const_iterator cend() const {
		return const_iterator(this, tail);
	}
	/**
	 * checks whether the container is empty.
	 */
	bool empty() const { return tot; }
	/**
	 * returns the number of elements
	 */
	size_t size() const { return tot; }
	/**
	 * clears the contents
	 */
	void clear() {
		tot = 0;
		node *tmp = tail;
		while (tmp != head) {
			tmp = tmp->pre;
			delete tmp->next;
		}
		delete tmp;
		head = tail = NULL;
	}
	/**
	 * inserts elements at the specified locat on in the container.
	 * inserts value before pos
	 * returns an iterator pointing to the inserted value
	 *     throw if the iterator is invalid or it point to a wrong place.
	 */
	iterator insert(iterator pos, const T &value) {
		if (pos.belong != this) throw invalid_iterator();
		node *now = pos.pointer, *tmp;
		tmp = now->pre;
		now->pre = new node(value);
		now->pre->next = now;
		if (tmp) tmp->next = now->pre->pre;
		now->pre->pre = tmp;
		if (head == now) head = now->pre;
		tot++;
		return now->pre;
	}
	/**
	 * removes specified element at pos.
	 * removes the element at pos.
	 * returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
	 * throw if the container is empty, the iterator is invalid or it points to a wrong place.
	 */
	iterator erase(iterator pos) {
		if (!tot) throw container_is_empty();
		if (pos.belong != this) throw invalid_iterator();
		node *now = pos.pointer, tmp = now->next;
		if (now == head) {
			head = head->next;
			delete head;
			tot--;
			return head;
		}
		if (now == tail) {
			tail = tail->pre;
			delete tail;
			tot--;
			return tail;
		}
		now->pre->next = now->next;
		now->next->pre = now->pre;
		delete now;
		tot--;
		return tmp;
	}
	/**
	 * adds an element to the end
	 */
	void push_back(const T &value) {
		if (!tot) {
			head = new node(value);
			tail = head;
			tot++;
			return;
		}
		tail->next = new node(value);
		tail->next->pre=tail;
		tail = tail->next;
		tot++;
		return;
	}
	/**
	 * removes the last element
	 *     throw when the container is empty.
	 */
	void pop_back() {
		if (!tot) throw container_is_empty();
		if (tot == 1) {
			delete tail;
			tot--;
			tail = head = NULL;
		}
		else {
			tail = tail->pre;
			delete tail->next;
			tail->next = NULL;
			tot--;
		}
	}
	/**
	 * inserts an element to the beginning.
	 */
	void push_front(const T &value) {
		if (!tot) {
			head = new node(value);
			tail = head;
			tot++;
			return;
		}
		head->pre = new node(value);
		head->pre->next = head;
		head = head->pre;
		tot++;
		return;
	}
	/**
	 * removes the first element.
	 *     throw when the container is empty.
	 */
	void pop_front() {
		if (!tot) throw container_is_empty();
		if (tot == 1) {
			delete tail;
			tail = head = NULL;
			tot = 0;
		}
		else {
			tail = tail->pre;
			delete tail->next;
			tot--;
		}
	}
};

}

#endif