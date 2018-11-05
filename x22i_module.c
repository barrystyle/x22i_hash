#include <Python.h>
#include "x22i.h"

static PyObject *x22i_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);
#if PY_MAJOR_VERSION >= 3
    x22i_hash((char *)PyBytes_AsString((PyObject*) input), output);
#else
    x22i_hash((char *)PyString_AsString((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef x22iMethods[] = {
    { "getPoWHash", x22i_getpowhash, METH_VARARGS, "Returns the proof of work hash using x22i" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef x22iModule = {
    PyModuleDef_HEAD_INIT,
    "x22i_hash",
    "...",
    -1,
    x22iMethods
};

PyMODINIT_FUNC PyInit_x22i_hash(void) {
    return PyModule_Create(&x22iModule);
}

#else

PyMODINIT_FUNC initx22i_hash(void) {
    (void) Py_InitModule("x22i_hash", x22iMethods);
}
#endif
