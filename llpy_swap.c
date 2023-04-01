#include <Python.h>
#include <stdio.h>

#define DO_SWAP(type, a, b) do { \
	type temp = *(a); \
	*(a) = *(b); \
	*(b) = temp; \
} while (0);

static PyObject *swap_func(PyObject *self, PyObject *args)
{
    PyObject *obj1, *obj2;

    if (!PyArg_ParseTuple(args, "OO", &obj1, &obj2)) {
		PyErr_SetString(PyExc_ValueError, "Invalid argument");
        return NULL;
    }
	
	// float
	{
		int is_sub1 = PyType_IsSubtype(obj1->ob_type, &PyFloat_Type);
		int is_sub2 = PyType_IsSubtype(obj2->ob_type, &PyFloat_Type);
		
		if (is_sub1 != is_sub2) {
			PyErr_SetString(PyExc_ValueError, "Invalid argument");
			return NULL;
		}
		if (is_sub1)
		{
			PyFloatObject *fobj1 = (PyFloatObject *)obj1;
			PyFloatObject *fobj2 = (PyFloatObject *)obj2;
			
			double ftemp = fobj1->ob_fval;
			fobj1->ob_fval = fobj2->ob_fval;
			fobj2->ob_fval = ftemp;
			
			Py_RETURN_NONE;
		}
	}
	// class method
	{
		int is_sub1 = PyMethod_Check(obj1);
		int is_sub2 = PyMethod_Check(obj2);
		
		if (is_sub1 != is_sub2) {
			PyErr_SetString(PyExc_ValueError, "Invalid argument");
			return NULL;
		}
		if (is_sub1)
		{
			PyMethodObject *mobj1 = (PyMethodObject *)obj1;
			PyMethodObject *mobj2 = (PyMethodObject *)obj2;
			
			DO_SWAP(PyObject *, &mobj1->im_func, &mobj2->im_func);
			DO_SWAP(PyObject *, &mobj1->im_self, &mobj2->im_self);
			DO_SWAP(PyObject *, &mobj1->im_weakreflist, &mobj2->im_weakreflist);
			DO_SWAP(vectorcallfunc, &mobj1->vectorcall, &mobj2->vectorcall);
			
			Py_RETURN_NONE;
		}
	}
	// instance method
	{
		int is_sub1 = PyInstanceMethod_Check(obj1);
		int is_sub2 = PyInstanceMethod_Check(obj2);
		
		if (is_sub1 != is_sub2) {
			PyErr_SetString(PyExc_ValueError, "Invalid argument");
			return NULL;
		}
		if (is_sub1)
		{
			PyInstanceMethodObject *mobj1 = (PyInstanceMethodObject *)obj1;
			PyInstanceMethodObject *mobj2 = (PyInstanceMethodObject *)obj2;
			
			DO_SWAP(PyObject *, &mobj1->func, &mobj2->func);
			
			Py_RETURN_NONE;
		}
	}
	// tuple
	{
		int is_sub1 = PyTuple_Check(obj1);
		int is_sub2 = PyTuple_Check(obj2);
		
		if (is_sub1 != is_sub2) {
			PyErr_SetString(PyExc_ValueError, "Invalid argument");
			return NULL;
		}
		if (is_sub1)
		{
			Py_ssize_t objSize = Py_SIZE(obj1);

			if (objSize != Py_SIZE(obj2)) {
				PyErr_SetString(PyExc_ValueError, "Invalid size");
				return NULL;
			}
				
			PyTupleObject *tobj1 = (PyTupleObject *)obj1;
			PyTupleObject *tobj2 = (PyTupleObject *)obj2;
			
			// swap all elements in tuple
			while (--objSize >= 0) {
				DO_SWAP(PyObject *, &tobj1->ob_item[objSize], &tobj2->ob_item[objSize]);
			}
			
			Py_RETURN_NONE;
		}
	}
	// list
	{
		int is_sub1 = PyList_Check(obj1);
		int is_sub2 = PyList_Check(obj2);
		
		if (is_sub1 != is_sub2) {
			PyErr_SetString(PyExc_ValueError, "Invalid argument");
			return NULL;
		}
		if (is_sub1)
		{
			PyListObject *lobj1 = (PyListObject *)obj1;
			PyListObject *lobj2 = (PyListObject *)obj2;
			
			DO_SWAP(PyObject **, &lobj1->ob_item, &lobj2->ob_item);
			DO_SWAP(Py_ssize_t, &lobj1->allocated, &lobj2->allocated);
			
			Py_RETURN_NONE;
		}
	}
	
	// int (PyLong) objects aren't supported because of arbitrary precision i.e.
	// memory is already allocated for given quantity of digits.
	
	PyErr_SetString(PyExc_ValueError, "Invalid argument");
    return NULL;
}

static PyMethodDef llpy_swap_methods[] = {
    {"swap", swap_func, METH_VARARGS, "Swaps two Python objects."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef llpy_swap_module = {
    PyModuleDef_HEAD_INIT,
    "llpy_swap",
    "C part of low-level Python extension",
    -1,
    llpy_swap_methods
};

PyMODINIT_FUNC PyInit_llpy_swap(void) {
    return PyModule_Create(&llpy_swap_module);
}
