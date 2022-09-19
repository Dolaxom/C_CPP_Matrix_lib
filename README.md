# Educational project of School 21 on the implementation of functions for working with matrices

### A library consisting of 11 functions for working with matrices of any size, written entirely in pure C


| Unit test coverage over 90%    | ✅ |
|--------------------------------|---|
| Verified google style code     | ✅ |
| Tested for leaks with Valgrind | ✅ |

## Some clarifications:
* The matrix itself is a **matrix_t** structure with components: Pointer to a two-dimensional array, number of rows and columns.

* **s21_create_matrix()** - is the creation of a matrix. The 1st argument is the number of rows, the second is the number of columns in your matrix. The third argument is a pointer to your matrix (structure). Memory is allocated in the function!!!

* **s21_remove_matrix()** - this is the removal of the matrix and the cleansing of memory.

* There are also 6 helper functions needed for the main functions to work.
