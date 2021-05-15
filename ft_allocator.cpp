#include <iostream>
#include <string>


// struct S
// {
// 	int x = 3;
// 	double d = 0.5;
// 	void *operator new(size_t n) {
// 		std::cout << n << " byte allocated for struct S!\n";
// 		void *p = malloc(n);
// 		if (!p) throw std::bad_alloc();
// 		return p;
// 	}

// 	void operator delete(void *p) noexcept {
// 		std::cout << "S deallocated!\n";
// 		free(p);
// 	}
// };

// void *operator new(size_t n) {
// 	std::cout << n << " byte allocated!\n";
// 	void *p = malloc(n);
// 	if (!p) throw std::bad_alloc();
// 	return p;
// }

// void *operator new[](size_t n) {
// 	std::cout << "Array of "<< n << " byte allocated!\n";
// 	void *p = malloc(n);
// 	if (!p) throw std::bad_alloc();
// 	return p;
// }

// void operator delete(void *p) noexcept {
// 	std::cout << "deallocated!\n";
// 	free(p);
// }

// void operator delete[](void *p) noexcept {
// 	std::cout << "Array deallocated!\n";
// 	free(p);
// }


template <typename T>
struct allocator
{
	T *allocate(size_t n) {
		return ::operator new(n * sizeof(T));
	}

	void deallocate(T *ptr, size_t) {
		::operator delete(ptr);
	}

	void construct(T *ptr, const T& value){
		new (ptr) T(value);
	}

	void destroy(T *ptr) {
		ptr->~T();
	}

};

int main () {

}
