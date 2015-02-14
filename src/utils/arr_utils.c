#include "arr_utils.h"

PyObject* lengthed_arr_to_pylist(LengthedArray* arr) {
    int j, res;
    PyObject* list = PyList_New(arr->len);
    if (list == NULL) {
        return NULL;
    }

    for (j=0; j<arr->len; j++) {
        PyObject* str = PyUnicode_FromString(arr->array[j]);
        if (str == NULL) {
            Py_DECREF(list);
            return NULL;
        }

        res = PyList_SetItem(list, j, str);
        if (res == -1) {
            Py_DECREF(str);
            Py_DECREF(list);
            return NULL;
        }
    }

    return list;
}


LengthedArray* pylist_to_lengthed_arr(PyObject* list) {
    PyObject *list_iterator, *item, *as_string;
    LengthedArray* arr = arr_create();

    list_iterator = PyObject_GetIter(list);
    if (list_iterator == NULL) {
        return NULL;
    }

    while ((item = PyIter_Next(list_iterator))) {
        char* s_item;

        as_string = PyUnicode_AsASCIIString(item);
        if (as_string == NULL) {
            Py_DECREF(item);
            Py_DECREF(list_iterator);
            return NULL;
        }

        s_item = PyBytes_AsString(as_string);
        if (s_item == NULL) {
            Py_DECREF(as_string);
            Py_DECREF(item);
            Py_DECREF(list_iterator);
            return NULL;
        }
        arr_append(arr, strdup(s_item));
        Py_DECREF(as_string);
        Py_DECREF(item);
    }
    Py_DECREF(list_iterator);

    return arr;
}
