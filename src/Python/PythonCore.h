#ifndef MYLIB_PYTHONCORE_H
#define MYLIB_PYTHONCORE_H


class PythonCore {
public:
    int CheckPython();
    static int Initialize();
    static int Finalize();
private:
    static wchar_t *s_PythonProgram;
};


#endif //MYLIB_PYTHONCORE_H
