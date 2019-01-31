#include <Python.h>
#include <unistd.h>

//#ifdef __cplusplus
extern "C"
{
//#endif

static PyObject *kernel_conf_clock_tick(PyObject *self, PyObject *args)
{
    char *input;
    long result;
    PyObject *ret;

    // run the actual function
    result = sysconf(_SC_CLK_TCK);

    // build the resulting string into a Python object.
    ret = PyLong_FromLong(result);

    return ret;
}

static PyMethodDef UsysMethods[] = {
    {"clock_tick", kernel_conf_clock_tick, METH_NOARGS, "get kernel clock tick"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef usysmodule = {
    PyModuleDef_HEAD_INIT,
    "usys", /* name of module */
    NULL,   /* module documentation, may be NULL */
    -1,     /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    UsysMethods};


PyMODINIT_FUNC
PyInit_usys(void)
{
    return PyModule_Create(&usysmodule);
}

//#ifdef __cplusplus
}
//#endif