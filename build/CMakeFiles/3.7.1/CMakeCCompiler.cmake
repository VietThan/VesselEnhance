set(CMAKE_C_COMPILER "/accre/arch/easybuild/software/Core/GCCcore/5.4.0/bin/cc")
set(CMAKE_C_COMPILER_ARG1 "")
set(CMAKE_C_COMPILER_ID "GNU")
set(CMAKE_C_COMPILER_VERSION "5.4.0")
set(CMAKE_C_COMPILER_WRAPPER "")
set(CMAKE_C_STANDARD_COMPUTED_DEFAULT "11")
set(CMAKE_C_COMPILE_FEATURES "c_function_prototypes;c_restrict;c_variadic_macros;c_static_assert")
set(CMAKE_C90_COMPILE_FEATURES "c_function_prototypes")
set(CMAKE_C99_COMPILE_FEATURES "c_restrict;c_variadic_macros")
set(CMAKE_C11_COMPILE_FEATURES "c_static_assert")

set(CMAKE_C_PLATFORM_ID "Linux")
set(CMAKE_C_SIMULATE_ID "")
set(CMAKE_C_SIMULATE_VERSION "")

set(CMAKE_AR "/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/binutils/2.26/bin/ar")
set(CMAKE_RANLIB "/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/binutils/2.26/bin/ranlib")
set(CMAKE_LINKER "/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/binutils/2.26/bin/ld")
set(CMAKE_COMPILER_IS_GNUCC 1)
set(CMAKE_C_COMPILER_LOADED 1)
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_C_ABI_COMPILED TRUE)
set(CMAKE_COMPILER_IS_MINGW )
set(CMAKE_COMPILER_IS_CYGWIN )
if(CMAKE_COMPILER_IS_CYGWIN)
  set(CYGWIN 1)
  set(UNIX 1)
endif()

set(CMAKE_C_COMPILER_ENV_VAR "CC")

if(CMAKE_COMPILER_IS_MINGW)
  set(MINGW 1)
endif()
set(CMAKE_C_COMPILER_ID_RUN 1)
set(CMAKE_C_SOURCE_FILE_EXTENSIONS c;m)
set(CMAKE_C_IGNORE_EXTENSIONS h;H;o;O;obj;OBJ;def;DEF;rc;RC)
set(CMAKE_C_LINKER_PREFERENCE 10)

# Save compiler ABI information.
set(CMAKE_C_SIZEOF_DATA_PTR "8")
set(CMAKE_C_COMPILER_ABI "ELF")
set(CMAKE_C_LIBRARY_ARCHITECTURE "")

if(CMAKE_C_SIZEOF_DATA_PTR)
  set(CMAKE_SIZEOF_VOID_P "${CMAKE_C_SIZEOF_DATA_PTR}")
endif()

if(CMAKE_C_COMPILER_ABI)
  set(CMAKE_INTERNAL_PLATFORM_ABI "${CMAKE_C_COMPILER_ABI}")
endif()

if(CMAKE_C_LIBRARY_ARCHITECTURE)
  set(CMAKE_LIBRARY_ARCHITECTURE "")
endif()

set(CMAKE_C_CL_SHOWINCLUDES_PREFIX "")
if(CMAKE_C_CL_SHOWINCLUDES_PREFIX)
  set(CMAKE_CL_SHOWINCLUDES_PREFIX "${CMAKE_C_CL_SHOWINCLUDES_PREFIX}")
endif()





set(CMAKE_C_IMPLICIT_LINK_LIBRARIES "c")
set(CMAKE_C_IMPLICIT_LINK_DIRECTORIES "/cvmfs/oasis.opensciencegrid.org/accre/mirror/optimized/sandy_bridge/easybuild/software/Core/GCCcore/5.4.0/lib/gcc/x86_64-unknown-linux-gnu/5.4.0;/cvmfs/oasis.opensciencegrid.org/accre/mirror/optimized/sandy_bridge/easybuild/software/Core/GCCcore/5.4.0/lib/gcc;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/libffi/3.2.1/lib64;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/nettle/3.2/lib64;/accre/arch/easybuild/software/Core/GCCcore/5.4.0/lib64;/cvmfs/oasis.opensciencegrid.org/accre/mirror/optimized/sandy_bridge/easybuild/software/Core/GCCcore/5.4.0/lib64;/lib64;/usr/lib64;/accre/arch/easybuild/software/Compiler/GCC/5.4.0-2.26/Pango/1.40.3/lib;/accre/arch/easybuild/software/Compiler/GCC/5.4.0-2.26/HarfBuzz/1.3.1/lib;/accre/arch/easybuild/software/Compiler/GCC/5.4.0-2.26/cairo/1.14.6/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/pixman/0.34.0/lib;/accre/arch/easybuild/software/Compiler/GCC/5.4.0-2.26/ITK/4.12.2-Python-2.7.12/lib;/accre/arch/easybuild/software/Compiler/GCC/5.4.0-2.26/VTK/6.3.0-Python-2.7.12/lib;/accre/arch/easybuild/software/Compiler/GCC/5.4.0-2.26/HDF5/1.8.17-serial/lib;/accre/arch/easybuild/software/MPI/GCC/5.4.0-2.26/OpenMPI/1.10.3/ParaView/5.3.0/lib;/accre/arch/easybuild/software/Compiler/GCC/5.4.0-2.26/Python/2.7.12/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/Tk/8.6.5/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/SQLite/3.13.0/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/Tcl/8.6.5/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/libreadline/6.3/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/Szip/2.1/lib;/accre/arch/easybuild/software/Compiler/GCC/5.4.0-2.26/Qt5/5.7.0/lib;/accre/arch/easybuild/software/Compiler/GCC/5.4.0-2.26/GLib/2.49.5/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/PCRE/8.39/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/gettext/0.19.8/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/libxml2/2.9.4/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/XZ/5.2.2/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/libffi/3.2.1/lib;/accre/arch/easybuild/software/Compiler/GCC/5.4.0-2.26/libGLU/9.0.0/lib;/accre/arch/easybuild/software/Compiler/GCC/5.4.0-2.26/Mesa/12.0.2/lib;/accre/arch/easybuild/software/Compiler/GCC/5.4.0-2.26/LLVM/3.8.1/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/ncurses/6.0/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/libdrm/2.4.70/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/GMP/6.1.1/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/X11/20160819/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/fontconfig/2.12.1/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/expat/2.2.0/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/freetype/2.6.5/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/bzip2/1.0.6/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/libpng/1.6.24/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/zlib/1.2.8/lib;/accre/arch/easybuild/software/MPI/GCC/5.4.0-2.26/OpenMPI/1.10.3/ScaLAPACK/2.0.2/lib;/accre/arch/easybuild/software/MPI/GCC/5.4.0-2.26/OpenMPI/1.10.3/FFTW/3.3.4/lib;/accre/arch/easybuild/software/Compiler/GCC/5.4.0-2.26/OpenBLAS/0.2.18-LAPACK-3.6.1/lib;/accre/arch/easybuild/software/Compiler/GCC/5.4.0-2.26/OpenMPI/1.10.3/lib;/accre/arch/easybuild/software/Compiler/GCC/5.4.0-2.26/hwloc/1.11.3/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/numactl/2.0.11/lib;/accre/arch/easybuild/software/Compiler/GCCcore/5.4.0/binutils/2.26/lib;/accre/arch/easybuild/software/Core/GCCcore/5.4.0/lib;/cvmfs/oasis.opensciencegrid.org/accre/mirror/optimized/sandy_bridge/easybuild/software/Core/GCCcore/5.4.0/lib")
set(CMAKE_C_IMPLICIT_LINK_FRAMEWORK_DIRECTORIES "")
