#ifndef MYLIB_MPICORE_H
#define MYLIB_MPICORE_H

#ifndef SERIAL_MODE
class MPICore {
private:
    static int m_Process;
    static int m_Size;

public:
    static int Initialize(int argc, char* argv[]);
    static int Finalize();
};
#endif

#endif  // MYLIB_MPICORE_H
