#include <Python.h>

#define DO_SWAP(type, a, b) do { \
	type temp = *(type *)(a); \
	*(a) = *(b); \
	*(type *)(b) = temp; \
} while (0)

static PyObject *swap_func(PyObject *self, PyObject *args)
{
    PyObject *obj1, *obj2;

    if (!PyArg_ParseTuple(args, "OO", &obj1, &obj2)) {
		PyErr_SetString(PyExc_ValueError, "Invalid argument");
        return NULL;
    }
	
	// float
	{
		if (PyFloat_Check(obj1))
		{
			if (!PyFloat_Check(obj2)) {
				PyErr_SetString(PyExc_ValueError, "Incompatible types");
				return NULL;
			}
			PyFloatObject *fobj1 = (PyFloatObject *)obj1;
			PyFloatObject *fobj2 = (PyFloatObject *)obj2;
			
			double ftemp = fobj1->ob_fval;
			fobj1->ob_fval = fobj2->ob_fval;
			fobj2->ob_fval = ftemp;
			
			Py_RETURN_NONE;
		}
	}
	// tuple
	{
		if (PyTuple_Check(obj1))
		{
			if (!PyTuple_Check(obj2)) {
				PyErr_SetString(PyExc_ValueError, "Incompatible types");
				return NULL;
			}
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
		if (PyList_Check(obj1))
		{
			if (!PyList_Check(obj2)) {
				PyErr_SetString(PyExc_ValueError, "Incompatible types");
				return NULL;
			}
			
			PyListObject *lobj1 = (PyListObject *)obj1;
			PyListObject *lobj2 = (PyListObject *)obj2;
			
			DO_SWAP(Py_ssize_t, &lobj1->ob_base.ob_size, &lobj2->ob_base.ob_size);
			DO_SWAP(PyObject **, &lobj1->ob_item, &lobj2->ob_item);
			DO_SWAP(Py_ssize_t, &lobj1->allocated, &lobj2->allocated);
			
			Py_RETURN_NONE;
		}
	}
	// dict
	{
		if (PyDict_Check(obj1))
		{
			if (!PyDict_Check(obj2)) {
				PyErr_SetString(PyExc_ValueError, "Incompatible types");
				return NULL;
			}
			
			PyDictObject *dobj1 = (PyDictObject *)obj1;
			PyDictObject *dobj2 = (PyDictObject *)obj2;
			
			DO_SWAP(Py_ssize_t, &dobj1->ma_used, &dobj2->ma_used);
			DO_SWAP(uint64_t, &dobj1->ma_version_tag, &dobj2->ma_version_tag);
			DO_SWAP(PyDictKeysObject *, &dobj1->ma_keys, &dobj2->ma_keys);
			DO_SWAP(PyDictValues *, &dobj1->ma_values, &dobj2->ma_values);
			
			Py_RETURN_NONE;
		}
	}
	// function
	{
		if (PyFunction_Check(obj1))
		{
			if (!PyFunction_Check(obj2)) {
				PyErr_SetString(PyExc_ValueError, "Incompatible types");
				return NULL;
			}
			
			PyFunctionObject *fnobj1 = (PyFunctionObject *)obj1;
			PyFunctionObject *fnobj2 = (PyFunctionObject *)obj2;
			
			// common fields (see cpython/funcobject.h)
			DO_SWAP(PyObject *, &fnobj1->func_globals, &fnobj2->func_globals);
			DO_SWAP(PyObject *, &fnobj1->func_builtins, &fnobj2->func_builtins);
			DO_SWAP(PyObject *, &fnobj1->func_name, &fnobj2->func_name);
			DO_SWAP(PyObject *, &fnobj1->func_qualname, &fnobj2->func_qualname);
			DO_SWAP(PyObject *, &fnobj1->func_code, &fnobj2->func_code);
			DO_SWAP(PyObject *, &fnobj1->func_defaults, &fnobj2->func_defaults);
			DO_SWAP(PyObject *, &fnobj1->func_kwdefaults, &fnobj2->func_kwdefaults);
			DO_SWAP(PyObject *, &fnobj1->func_closure, &fnobj2->func_closure);
			
			DO_SWAP(PyObject *, &fnobj1->func_doc, &fnobj2->func_doc);
			DO_SWAP(PyObject *, &fnobj1->func_dict, &fnobj2->func_dict);
			DO_SWAP(PyObject *, &fnobj1->func_weakreflist, &fnobj2->func_weakreflist);
			DO_SWAP(PyObject *, &fnobj1->func_module, &fnobj2->func_module);
			DO_SWAP(PyObject *, &fnobj1->func_annotations, &fnobj2->func_annotations);
			
			DO_SWAP(vectorcallfunc, &fnobj1->vectorcall, &fnobj2->vectorcall);
			
			DO_SWAP(uint32_t, &fnobj1->func_version, &fnobj2->func_version);
			
			Py_RETURN_NONE;
		}
	}
	// class method
	{
		if (PyMethod_Check(obj1))
		{
			if (!PyMethod_Check(obj2)) {
				PyErr_SetString(PyExc_ValueError, "Incompatible types");
				return NULL;
			}
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
		if (PyInstanceMethod_Check(obj1))
		{
			if (!PyInstanceMethod_Check(obj2)) {
				PyErr_SetString(PyExc_ValueError, "Incompatible types");
				return NULL;
			}
			PyInstanceMethodObject *mobj1 = (PyInstanceMethodObject *)obj1;
			PyInstanceMethodObject *mobj2 = (PyInstanceMethodObject *)obj2;
			
			DO_SWAP(PyObject *, &mobj1->func, &mobj2->func);
			
			Py_RETURN_NONE;
		}
	}
	// complex
	{
		if (PyComplex_Check(obj1))
		{
			if (!PyComplex_Check(obj2)) {
				PyErr_SetString(PyExc_ValueError, "Incompatible types");
				return NULL;
			}
			
			PyComplexObject *cobj1 = (PyComplexObject *)obj1;
			PyComplexObject *cobj2 = (PyComplexObject *)obj2;
			
			DO_SWAP(Py_complex, &cobj1->cval, &cobj2->cval);
			
			Py_RETURN_NONE;
		}
	}
	
	// int (PyLongObject) isn't supported because of arbitrary precision i.e.
	// memory is already allocated for given quantity of digits.
	
	// @todo PyGenObject
	// @todo bytes
	// @todo bytearray
	
	PyErr_SetString(PyExc_ValueError, "Unexpected type");
    return NULL;
}

static PyMethodDef llpy_util_methods[] = {
    {"swap", swap_func, METH_VARARGS, "Swaps two Python objects."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef llpy_util_module = {
    PyModuleDef_HEAD_INIT,
    "llpy_swap",
    "C part of low-level Python extension",
    -1,
    llpy_util_methods
};

PyMODINIT_FUNC PyInit_llpy_util(void) {
    return PyModule_Create(&llpy_util_module);
}
