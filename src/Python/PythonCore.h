#ifndef MYLIB_PYTHONCORE_H
#define MYLIB_PYTHONCORE_H

#ifdef USE_PYTHON
class PythonCore {
public:
    int CheckPython();
    static int Initialize();
    static int Finalize();

private:
    static wchar_t* s_PythonProgram;
};
#endif

#endif  // MYLIB_PYTHONCORE_H
