#include <iostream>
using namespace std;

template <typename T>
class arrayList {
	int size;
	int max;
	
	T *data;
	
public:
	int sizeOf()const {
		return size;
	}
	
	const T& first() const {
		if (size > 0) {
	 		return data[0];
		} else {
			cerr << "Error.";
		}
	}
	
	void insert(const T& itemToInsert, const int position) {
		// if position is invalid: error
		// if not enough storage, get a new array, copy data, dispose old array
		// if enough storage, shift all elements to the right → insert position into array, update size
		
		if (position < 0 || position > size) { cerr << "Error"; }
		if (size == max) { 
			T* tmp = new T[max * 2]; // get a new array
			max = max * 2; // update max
			
			for (int i = 0; i < size; i++) { // copy data 
				tmp[i] = data[i];
			}
			
			delete []data;
			data = tmp;
			
			// DO NOT DELETE TMP
			// tmp points to the data. delete tmp = delete the data.
			// Because tmp is limited to the scope of this if statement
			// tmp gets cleaned up upon exiting scope
		}
		
		for (int i = size; i > position; i--) { 
			// countdown. going up would copy the elements improperly
			// attempt the alogithm visually. Going to the right makes less sense than going to the left.
			// shift every element
			data[i] = data[i - 1];
		}
		
		data[position] = itemToInsert; // insert item
		size++; // update the size
	}
	
	bool find(const T& itemToFind) {
		for (int i = 0; i < size; i++) {
			if (itemToFind == data[i]) { return true; }
		}
		
		return false;
	}
	
	void remove(); // This is for us to do

	~arrayList() {
		delete []data;
		// Do not need to set data to null, class gets destructed
	}
};

int main(int argc, char *argv[]) {
	arrayList<char> arbitraryList;
}