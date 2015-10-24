#ifndef _VECTOR_
#define _VECTOR_

template <class Data>
class Vector
{
	unsigned int m_nSize, m_nCapacity;
	Data *m_pVector;

public:
	Vector();
	~Vector() { delete[] m_pVector; };
	Vector(const Vector<Data> &that);

	Vector<Data>& operator=(const Vector<Data> &that);
	Data &operator[](const unsigned int unIndex){ return m_pVector[unIndex]; };

	unsigned int size() { return m_nSize; };
	unsigned int capacity() { return m_nCapacity; };
	void resize(unsigned int unCapacity = 0);
	void pushback(Data &data);

};

template <class Data>
Vector<Data>::Vector()
{
	m_nCapacity = m_nSize = 0;
	m_pVector = nullptr;
}

template <class Data>
Vector<Data>::Vector(const Vector<Data> &that)
{
	*this = that;
}

template <class Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& that)
{
	if (this != that)
	{
		m_nSize = that.m_nSize;
		m_nCapacity = that.m_nCapacity;
		m_pVector = new Data[m_nCapacity];
		for (unsigned int i = 0; i < m_nSize; ++i)
			m_pVector[i] = that.m_pVector[i];
	}
	return *this;
}

template <class Data>
void Vector<Data>::resize(unsigned int unCapacity)
{
	if (unCapacity == 0) // default
		m_nCapacity++;
	else if (unCapacity > m_nCapacity) // set manually to specified size
		m_nCapacity = unCapacity;

	// Update the container
	Data *pVector = new Data[m_nCapacity];
	for (unsigned int i = 0; i < m_nSize; ++i)
		pVector[i] = m_pVector[i];
	m_pVector = pVector;
}

template <class Data>
void Vector<Data>::pushback(Data &data)
{

	// Makes sure to update the capacity of container
	if (m_nSize == m_nCapacity)
		resize();
	m_pVector[m_nSize] = data;
	m_nSize++;

}

#endif