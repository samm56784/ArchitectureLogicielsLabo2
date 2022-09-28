#include <Python.h>
#include "fonctions.h"
#include <filesystem>
using namespace std;
static PyObject* start(PyObject* self, PyObject* args)
{
    const char* buffer;
    PyArg_ParseTuple(args,"s", &buffer);
    string buffpath = buffer;
    wstring temp(buffpath.begin(), buffpath.end());
   wstring autre = temp;
   LPCWSTR path = autre.c_str();
    string Message;
    PyObject* val = 0;
    IGraphBuilder* pGraph = NULL;
    IMediaControl* pControl = NULL;
    IMediaEvent* pEvent = NULL;
    IMediaSeeking* pSeeking = NULL;
    // Initialize the COM library.
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        printf("ERROR - Could not initialize COM library");
        return 0;
    }

    // Create the filter graph manager and query for interfaces.
    hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
        IID_IGraphBuilder, (void**)&pGraph);
    if (FAILED(hr))
    {
        printf("ERROR - Could not create the Filter Graph Manager.");
        return 0;
    }

    hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
    hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);
    hr = pGraph->QueryInterface(IID_IMediaSeeking, (void**)&pSeeking);
    // Build the graph. IMPORTANT: Change this string to a file on your system.

    //hr = pGraph->RenderFile(L"C:\\Example.avi", NULL);//args-> C:\\Example.avi
    hr = pGraph->RenderFile(path, NULL);//args-> C:\\Example.avi
    if (SUCCEEDED(hr))
    {
        // Run the graph.
        hr = pControl->Run();
        if (SUCCEEDED(hr))
        {
            //cas video marche et est en cours de lecture
            ToucheEntrée(hr, pGraph, pControl, pEvent, pSeeking);//passer en entrée hr 
            pControl->Release();
            pEvent->Release();
            pGraph->Release();
            pSeeking->Release();
            CoUninitialize();
            Message = "Methode bien fermee!"; 
            const char* buf = Message.c_str();
            val = PyBytes_FromString(buf);
            return val;
            
        }
        return NULL;
    }
    else
    {
        cout << "Erreur d'ouverture du fichier video..." << endl;
        pControl->Release();
        pEvent->Release();
        pGraph->Release();
        CoUninitialize();
        return NULL;
    }
   // return NULL;
}

static PyMethodDef methods[] = {

    {"start",start,METH_VARARGS,"start"},
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef labo2 =
{
    PyModuleDef_HEAD_INIT,
    "labo2", /* name of module */
    "",          /* module documentation, may be NULL */
    -1,          /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    methods
};

PyMODINIT_FUNC PyInit_labo2(void)
{
    return PyModule_Create(&labo2);
}