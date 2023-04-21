//
// MATLAB Compiler: 8.4 (R2022a)
// Date: Thu Apr 20 16:16:02 2023
// Arguments:
// "-B""macro_default""-W""cpplib:SudokuSolution,all,version=1.0""-T""link:lib""
// -d""C:\Users\黯渊之主\Desktop\SudokuSolution\for_testing""-v""C:\Users\�
// �渊之主\Desktop\SudokuSolution.m"
//

#ifndef SudokuSolution_h
#define SudokuSolution_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" { // sbcheck:ok:extern_c
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_SudokuSolution_C_API 
#define LIB_SudokuSolution_C_API /* No special import/export declaration */
#endif

/* GENERAL LIBRARY FUNCTIONS -- START */

extern LIB_SudokuSolution_C_API 
bool MW_CALL_CONV SudokuSolutionInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_SudokuSolution_C_API 
bool MW_CALL_CONV SudokuSolutionInitialize(void);

extern LIB_SudokuSolution_C_API 
void MW_CALL_CONV SudokuSolutionTerminate(void);

extern LIB_SudokuSolution_C_API 
void MW_CALL_CONV SudokuSolutionPrintStackTrace(void);

/* GENERAL LIBRARY FUNCTIONS -- END */

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

extern LIB_SudokuSolution_C_API 
bool MW_CALL_CONV mlxSudokuSolution(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

/* C INTERFACE -- MLX WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */

#ifdef __cplusplus
}
#endif


/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- START */

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__MINGW64__)

#ifdef EXPORTING_SudokuSolution
#define PUBLIC_SudokuSolution_CPP_API __declspec(dllexport)
#else
#define PUBLIC_SudokuSolution_CPP_API __declspec(dllimport)
#endif

#define LIB_SudokuSolution_CPP_API PUBLIC_SudokuSolution_CPP_API

#else

#if !defined(LIB_SudokuSolution_CPP_API)
#if defined(LIB_SudokuSolution_C_API)
#define LIB_SudokuSolution_CPP_API LIB_SudokuSolution_C_API
#else
#define LIB_SudokuSolution_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_SudokuSolution_CPP_API void MW_CALL_CONV SudokuSolution(int nargout, mwArray& MA, const mwArray& MQ);

/* C++ INTERFACE -- WRAPPERS FOR USER-DEFINED MATLAB FUNCTIONS -- END */
#endif

#endif
