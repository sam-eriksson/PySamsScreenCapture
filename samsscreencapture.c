//
//  samsscreencapture.c
//  PySamsScreenCapture
//
//  Created by Sam Eriksson on 2018-12-17.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#include "Python.h"
#include "ScreenCapture.h"

static PyObject *SscError;

static PyObject * ssc_alldisplays(PyObject *self, PyObject *args) {
    char *path;
    int sts;
    
    if (!PyArg_ParseTuple(args, "s", &path))
        return NULL;
    
    takeScreenShotAllDisplays(path);

    sts = 0;
    if (sts < 0) {
        PyErr_SetString(SscError, "System command failed");
        return NULL;
    }
    return PyLong_FromLong(sts);
}

static PyObject * ssc_display(PyObject *self, PyObject *args) {
    char *path;
    int display=0;
    int sts;
    
    if (!PyArg_ParseTuple(args, "si", &path, &display))
        return NULL;
    takeScreenShot(path, display);
    
    sts = 0;
    if (sts < 0) {
        PyErr_SetString(SscError, "System command failed");
        return NULL;
    }
    return PyLong_FromLong(sts);
}

static PyObject * ssc_displaytofile(PyObject *self, PyObject *args) {
    char *path;
    int display=0;
    char *filename;
    int sts;
    
    if (!PyArg_ParseTuple(args, "sis", &path, &display, &filename))
        return NULL;

    takeScreenShotToFile(path, display, filename);
    
    sts = 0;
    if (sts < 0) {
        PyErr_SetString(SscError, "System command failed");
        return NULL;
    }
    return PyLong_FromLong(sts);
}

static PyMethodDef SscMethods[] = {
    {"alldisplays",  ssc_alldisplays, METH_VARARGS,
        "Capture all displays to path, File format generated."},
    {"display",  ssc_display, METH_VARARGS,
        "Capture a display to path, File format generated."},
    {"displaytofile",  ssc_displaytofile, METH_VARARGS,
        "Capture a display to a specified file."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef sscmodule = {
    PyModuleDef_HEAD_INIT,
    "sscmodule",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
               or -1 if the module keeps state in global variables. */
    SscMethods
};

PyMODINIT_FUNC PyInit_ssc(void) {
    PyObject *m;
    
    m = PyModule_Create(&sscmodule);
    if (m == NULL)
        return NULL;
    
    SscError = PyErr_NewException("ssc.error", NULL, NULL);
    Py_INCREF(SscError);
    PyModule_AddObject(m, "error", SscError);
    return m;
}

int
main(int argc, char *argv[])
{
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }
    
    /* Add a built-in module, before Py_Initialize */
    PyImport_AppendInittab("ssc", PyInit_ssc);
    
    /* Pass argv[0] to the Python interpreter */
    Py_SetProgramName(program);
    
    /* Initialize the Python interpreter.  Required. */
    Py_Initialize();
    
    /* Optionally import the module; alternatively,
     import can be deferred until the embedded script
     imports it. */
    PyImport_ImportModule("ssc");
    
    
    PyMem_RawFree(program);
    return 0;
}
