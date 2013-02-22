#ifndef _DLIST_H_
#define _DLIST_H_

struct dlist_node_base
{
	dlist_node_base *_prev, *_next;
	dlist_node_base(dlist_node_base *prev, dlist_node_base *next)
		: _prev(prev), _next(next) {}
};

typedef dlist_node_base* dlist_anchor;

template <class T>
class dlist;

template <class T>
class dlist_node : public dlist_node_base
{
	T _item;

	dlist_node(dlist_anchor prev, const T& item, dlist_anchor next)
		: dlist_node_base(prev, next), _item(item) {}

friend class dlist<T>;
};

template <class T>
class dlist
{
	dlist_anchor _head, _tail;
	int _size;

public:
	//	constructors
	dlist();

	//	updates
	void push(const T& item);
	void append(const T& item);
	T pop();	
	T remove();
	
	//	access
	int size() const;
	bool empty() const;

	//	iteration
	dlist_anchor head() const { return _head; }
	dlist_anchor tail() const { return _tail; }
	dlist_anchor get_item(int index) const;
	dlist_anchor next(dlist_anchor anchor) const { return anchor->_next; }
	dlist_anchor prev(dlist_anchor anchor) const { return anchor->_prev; }
	T& contents(dlist_anchor anchor) { return ((dlist_node<T> *)anchor)->_item; }
	const T& contents(dlist_anchor anchor) const { return ((dlist_node<T> *)anchor)->_item; }
	T erase(dlist_anchor todel);
	dlist_anchor search_back(const T& item);

	//	destructors
	void clear();
	~dlist();
};

template <class T>
dlist<T>::dlist()
{
	_head = 0;
	_tail = 0;
	_size = 0;
}

template <class T>
void dlist<T>::clear()
{
	dlist_node_base *todel;
	while (_size)
	{
		todel = _head;
		_head = _head->_next;
		delete ((dlist_node<T> *)todel);
		_size--;
	}

	_head = _tail = 0;
}

template <class T>
dlist<T>::~dlist()
{
	clear();
}

template <class T>
bool dlist<T>::empty() const
{
	return _head == 0;
}

template <class T>
int dlist<T>::size() const
{
	return _size;
}

template <class T>
void dlist<T>::push(const T& item)
{
	if (!_head)
		_head = _tail = new dlist_node<T>(0, item, 0);
	else
		_head = _head->_prev = new dlist_node<T>(0, item, _head);

	_size++;
}

template <class T>
void dlist<T>::append(const T& item)
{
	if (!_tail)
		_head = _tail = new dlist_node<T>(0, item, 0);
	else
		_tail = _tail->_next = new dlist_node<T>(_tail, item, 0);

	_size++;
}

template <class T>
T dlist<T>::pop()
{
	assert(_size > 0);
	dlist_anchor y = _head;

	_head = _head->_next;
	if (!_head)
		_tail = 0;
	else
		_head->_prev = 0;

	T item(((dlist_node<T> *)y)->_item);
	delete ((dlist_node<T> *)y);
	--_size;

	return item;
}

template <class T>
T dlist<T>::remove()
{
	assert(_size > 0);
	dlist_anchor y = _tail;

	_tail = _tail->_prev;
	if (! _tail)
		_head = 0;
	else
		_tail->_next = 0;

	T item(((dlist_node<T> *)y)->_item);
	delete ((dlist_node<T> *)y);
	--_size;

	return item;
}

template <class T>
dlist_anchor dlist<T>::get_item(int index) const
{
	assert(index < _size);

	dlist_anchor y = _head;
	while (y && index--)
		y = y->_next;

	return y;
}

template <class T>
T dlist<T>::erase(dlist_anchor anchor)
{
	assert (anchor != 0);

	dlist_anchor next = anchor->_next;
	dlist_anchor prev = anchor->_prev;

	if (!prev)
		_head = anchor->_next;
	else
		prev->_next = next;

	if (!next)
		_tail = anchor->_prev;
	else
		next->_prev = prev;

	T item(((dlist_node<T> *)anchor)->_item);
	delete ((dlist_node<T> *)anchor);
	--_size;

	return item;
}

template <class T>
dlist_anchor dlist<T>::search_back(const T& item)
{
	dlist_anchor anchor = _tail;
	while (anchor)
	{
		if (contents(anchor) == item)
			return anchor;

		anchor = anchor->_prev;
	}

	return anchor;
}

#endif // _DLIST_H_
