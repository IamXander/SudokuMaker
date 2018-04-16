#include <cmath>
#include <cassert>
#include <iostream>

template<class numType>
class puzzle_t {
public:
	puzzle_t(size_t size, numType nullVal) : m_size(size), m_values(new numType[size*size]), m_nullVal(nullVal) {
		m_rootSize = std::sqrt(size);
		assert(m_rootSize * m_rootSize == m_size);
		for (int i = 0; i < size*size; i++) {
			m_values[i] = m_nullVal;
		}
	}
	~puzzle_t() {
		delete[] m_values;
	}

	inline numType getValueAt(size_t x, size_t y) {
		return m_values[(m_size * y) + x];
	}
	inline void setValueAt(size_t x, size_t y, numType value) {
		m_values[(m_size * y) + x] = value;
	}

	inline bool isInRow(size_t y, numType value) {
		numType * rowStart = m_values + (y * m_size);
		numType * rowEnd = rowStart + m_size;
		while (rowStart < rowEnd) if (*(rowStart++) == value) return true;
		return false;
	}

	inline bool isInCol(size_t x, numType value) {
		numType * colStart = m_values + x;
		numType * colEnd = m_values + (m_size * m_size);
		for (; colStart < colEnd; colStart += m_size) {
			if (*colStart == value) return true;
		}
		return false;
	}

	inline bool isInBox(size_t x, size_t y, numType value) {
		size_t boxX = (x / m_rootSize) * m_rootSize;
		size_t boxY = (y / m_rootSize) * m_rootSize;
		// std::cout << "x: " << boxX << " y: " << boxY << std::endl;
		for (int i = 0; i < m_rootSize; i++) {
			for (int j = 0; j < m_rootSize; j++) {
				if (m_values[(m_size * (boxY + i)) + (boxX + j)] == value) return true;
			}
		}
		return false;
	}

	inline bool isValid(size_t x, size_t y, numType value) {
		return !isInRow(y, value) && !isInCol(x, value) && !isInBox(x, y, value);
	}

	void print(std::ostream & o) {
		for (int y = 0; y < m_size; y++) {
			if (y % 3 == 0) {
				o << "---------------------------------------------------\n";
			}
			o << '|';
			for (int x = 0; x < m_size; x++) {
				o << m_values[x + (y * m_size)] << '|';
			}
			o << '\n';
		}
	}

	inline numType getNullVal() {
		return m_nullVal;
	}

	inline size_t getSize() {
		return m_size;
	}

private:
	size_t m_rootSize;
	size_t m_size;
	numType * m_values;
	numType m_nullVal;
};


/*
~rule_of_five()
    {
        delete[] cstring;  // deallocate
    }
    rule_of_five(const rule_of_five& other) // copy constructor
    {
        cstring = new char[std::strlen(other.cstring) + 1];
        std::strcpy(cstring, other.cstring);
    }
    rule_of_five(rule_of_five&& other) : cstring(other.cstring) // move constructor
    {
        other.cstring = nullptr;
    }
    rule_of_five& operator=(const rule_of_five& other) // copy assignment
    {
        char* tmp_cstring = new char[std::strlen(other.cstring) + 1];
        std::strcpy(tmp_cstring, other.cstring);
        delete[] cstring;
        cstring = tmp_cstring;
        return *this;
    }
    rule_of_five& operator=(rule_of_five&& other) // move assignment
    {
        if(this!=&other) // prevent self-move
        {
            delete[] cstring;
            cstring = other.cstring;
            other.cstring = nullptr;
        }
        return *this;
    }
 */
