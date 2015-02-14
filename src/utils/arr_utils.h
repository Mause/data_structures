#ifndef ARR_UTILS_H
#define ARR_UTILS_H

#include "Python.h"

PyObject* lengthed_arr_to_pylist(LengthedArray* arr);
LengthedArray* pylist_to_lengthed_arr(PyObject* arr);

#endif
