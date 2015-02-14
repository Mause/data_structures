dict* py_dict_to_dict_c(PyObject* dict);
PyObject* dict_c_to_py_dict(dict* d);


PyObject* dict_c_to_py_dict(dict* d) {
    int i;
    PyObject *dict, *list;
    LengthedArray* arr;
    dict = PyDict_New();
    if (dict == NULL) {
        return NULL;
    }

    for (i=0; i<d->max_size; i++) {
        if (dict_valid_entry(d, i)) {
            int res;
            dict_entry* entry;

            entry = d->entries[i];
            arr = entry->value;

            list = lengthed_arr_to_pylist(arr);
            if (list == NULL) {
                Py_DECREF(dict);
                return NULL;
            }

            res = PyDict_SetItemString(dict, entry->key, list);
            if (res == -1) {
                Py_DECREF(list);
                Py_DECREF(dict);
                return NULL;
            }
            Py_DECREF(list);
        }
    }

    return dict;
}


dict* py_dict_to_dict_c(PyObject* py_dict) {
    dict *d;
    PyObject *items, *iterator, *item;

    if (!PyDict_Check(py_dict)) {
        return NULL;
    }

    items = PyDict_Items(py_dict);
    if (items == NULL) {
        return NULL;
    }

    iterator = PyObject_GetIter(items);
    if (iterator == NULL) {
        Py_DECREF(items);
        return NULL;
    }

    d = dict_create(PyDict_Size(py_dict));

    while ((item = PyIter_Next(iterator))) {
        PyObject *key, *value, *as_string;
        char* s_as_string;
        LengthedArray* arr;

        key = PyTuple_GetItem(item, 0);

        as_string = PyUnicode_AsASCIIString(key);
        if (as_string == NULL) {
            Py_DECREF(iterator);
            Py_DECREF(items);
            Py_DECREF(item);
            return NULL;
        }

        s_as_string = PyBytes_AsString(as_string);
        if (s_as_string == NULL) {
            Py_DECREF(as_string);
            Py_DECREF(iterator);
            Py_DECREF(items);
            Py_DECREF(item);
            return NULL;
        }
        s_as_string = strdup(s_as_string);

        value = PyTuple_GetItem(item, 1);
        arr = pylist_to_lengthed_arr(value);
        if (arr == NULL) {
            Py_DECREF(as_string);
            Py_DECREF(iterator);
            Py_DECREF(items);
            Py_DECREF(item);
            return NULL;
        }

        dict_set(d, s_as_string, arr);
        Py_DECREF(as_string);
        Py_DECREF(item);
    }
    Py_DECREF(iterator);
    Py_DECREF(items);

    return d;
}
