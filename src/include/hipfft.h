/*******************************************************************************
 * Copyright (C) 2016 Advanced Micro Devices, Inc. All rights reserved.
 ******************************************************************************/

#ifndef __HIPFFT_H__
#define __HIPFFT_H__

#include <hip/hip_runtime_api.h>

#define DLL_PUBLIC __attribute__ ((visibility ("default")))

#ifdef __cplusplus
extern "C" {
#endif

typedef enum hipfftResult_t {
  HIPFFT_SUCCESS        = 0,  //  The hipFFT operation was successful
  HIPFFT_INVALID_PLAN   = 1,  //  hipFFT was passed an invalid plan handle
  HIPFFT_ALLOC_FAILED   = 2,  //  hipFFT failed to allocate GPU or CPU memory
  HIPFFT_INVALID_TYPE   = 3,  //  No longer used
  HIPFFT_INVALID_VALUE  = 4,  //  User specified an invalid pointer or parameter
  HIPFFT_INTERNAL_ERROR = 5,  //  Driver or internal hipFFT library error
  HIPFFT_EXEC_FAILED    = 6,  //  Failed to execute an FFT on the GPU
  HIPFFT_SETUP_FAILED   = 7,  //  The hipFFT library failed to initialize
  HIPFFT_INVALID_SIZE   = 8,  //  User specified an invalid transform size
  HIPFFT_UNALIGNED_DATA = 9,  //  No longer used
  HIPFFT_INCOMPLETE_PARAMETER_LIST = 10, //  Missing parameters in call
  HIPFFT_INVALID_DEVICE = 11, //  Execution of a plan was on different GPU than plan creation
  HIPFFT_PARSE_ERROR    = 12, //  Internal plan database error
  HIPFFT_NO_WORKSPACE   = 13,  //  No workspace has been provided prior to plan execution
  HIPFFT_RESULT_NOT_SUPPORTED = 14
}hipfftResult;

typedef enum hipfftType_t {
    HIPFFT_R2C = 0x2a,  // Real to complex (interleaved)
    HIPFFT_C2R = 0x2c,  // Complex (interleaved) to real
    HIPFFT_C2C = 0x29,  // Complex to complex (interleaved)
    HIPFFT_D2Z = 0x6a,  // Double to double-complex (interleaved)
    HIPFFT_Z2D = 0x6c,  // Double-complex (interleaved) to double
    HIPFFT_Z2Z = 0x69   // Double-complex to double-complex (interleaved)
}hipfftType;


typedef struct hipfftHandle_t *hipfftHandle;

typedef float hipfftComplex[2];
typedef double hipfftDoubleComplex[2];
typedef float  hipfftReal;
typedef double hipfftDoubleReal;

DLL_PUBLIC hipfftResult hipfftPlan1d(hipfftHandle *plan,
                                 int nx,
                                 hipfftType type,
                                 int batch /* deprecated - use hipfftPlanMany */);

DLL_PUBLIC hipfftResult hipfftPlan2d(hipfftHandle *plan,
                                 int nx, int ny,
                                 hipfftType type);

DLL_PUBLIC hipfftResult hipfftPlan3d(hipfftHandle *plan,
                                 int nx, int ny, int nz,
                                 hipfftType type);

DLL_PUBLIC hipfftResult hipfftPlanMany(hipfftHandle *plan,
                                   int rank,
                                   int *n,
                                   int *inembed, int istride, int idist,
                                   int *onembed, int ostride, int odist,
                                   hipfftType type,
                                   int batch);

DLL_PUBLIC hipfftResult hipfftMakePlan1d(hipfftHandle plan,
                                     int nx,
                                     hipfftType type,
                                     int batch, /* deprecated - use hipfftPlanMany */
                                     size_t *workSize);

DLL_PUBLIC hipfftResult hipfftMakePlan2d(hipfftHandle plan,
                                     int nx, int ny,
                                     hipfftType type,
                                     size_t *workSize);

DLL_PUBLIC hipfftResult hipfftMakePlan3d(hipfftHandle plan,
                                     int nx, int ny, int nz,
                                     hipfftType type,
                                     size_t *workSize);

DLL_PUBLIC hipfftResult hipfftMakePlanMany(hipfftHandle plan,
                                       int rank,
                                       int *n,
                                       int *inembed, int istride, int idist,
                                       int *onembed, int ostride, int odist,
                                       hipfftType type,
                                       int batch,
                                       size_t *workSize);

DLL_PUBLIC hipfftResult hipfftMakePlanMany64(hipfftHandle plan,
                                         int rank,
                                         long long int *n,
                                         long long int *inembed,
                                         long long int istride,
                                         long long int idist,
                                         long long int *onembed,
                                         long long int ostride, long long int odist,
                                         hipfftType type,
                                         long long int batch,
                                         size_t * workSize);

DLL_PUBLIC hipfftResult hipfftGetSizeMany64(hipfftHandle plan,
                                        int rank,
                                        long long int *n,
                                        long long int *inembed,
                                        long long int istride, long long int idist,
                                        long long int *onembed,
                                        long long int ostride, long long int odist,
                                        hipfftType type,
                                        long long int batch,
                                        size_t *workSize);




DLL_PUBLIC hipfftResult hipfftEstimate1d(int nx,
                                     hipfftType type,
                                     int batch, /* deprecated - use hipfftPlanMany */
                                     size_t *workSize);

DLL_PUBLIC hipfftResult hipfftEstimate2d(int nx, int ny,
                                     hipfftType type,
                                     size_t *workSize);

DLL_PUBLIC hipfftResult hipfftEstimate3d(int nx, int ny, int nz,
                                     hipfftType type,
                                     size_t *workSize);

DLL_PUBLIC hipfftResult hipfftEstimateMany(int rank,
                                       int *n,
                                       int *inembed, int istride, int idist,
                                       int *onembed, int ostride, int odist,
                                       hipfftType type,
                                       int batch,
                                       size_t *workSize);

DLL_PUBLIC hipfftResult hipfftCreate(hipfftHandle * handle);

DLL_PUBLIC hipfftResult hipfftGetSize1d(hipfftHandle handle,
                                    int nx,
                                    hipfftType type,
                                    int batch, /* deprecated - use hipfftGetSizeMany */
                                    size_t *workSize );

DLL_PUBLIC hipfftResult hipfftGetSize2d(hipfftHandle handle,
                                    int nx, int ny,
                                    hipfftType type,
                                    size_t *workSize);

DLL_PUBLIC hipfftResult hipfftGetSize3d(hipfftHandle handle,
                                    int nx, int ny, int nz,
                                    hipfftType type,
                                    size_t *workSize);

DLL_PUBLIC hipfftResult hipfftGetSizeMany(hipfftHandle handle,
                                      int rank, int *n,
                                      int *inembed, int istride, int idist,
                                      int *onembed, int ostride, int odist,
                                      hipfftType type, int batch, size_t *workArea);

DLL_PUBLIC hipfftResult hipfftGetSize(hipfftHandle handle, size_t *workSize);

DLL_PUBLIC hipfftResult hipfftSetWorkArea(hipfftHandle plan, void *workArea);

DLL_PUBLIC hipfftResult hipfftSetAutoAllocation(hipfftHandle plan, int autoAllocate);

DLL_PUBLIC hipfftResult hipfftExecC2C(hipfftHandle plan,
                                  hipfftComplex *idata,
                                  hipfftComplex *odata,
                                  int direction);

DLL_PUBLIC hipfftResult hipfftExecR2C(hipfftHandle plan,
                                  hipfftReal *idata,
                                  hipfftComplex *odata);

DLL_PUBLIC hipfftResult hipfftExecC2R(hipfftHandle plan,
                                  hipfftComplex *idata,
                                  hipfftReal *odata);

DLL_PUBLIC hipfftResult hipfftExecZ2Z(hipfftHandle plan,
                                  hipfftDoubleComplex *idata,
                                  hipfftDoubleComplex *odata,
                                  int direction);

DLL_PUBLIC hipfftResult hipfftExecD2Z(hipfftHandle plan,
                                  hipfftDoubleReal *idata,
                                  hipfftDoubleComplex *odata);

DLL_PUBLIC hipfftResult hipfftExecZ2D(hipfftHandle plan,
                                  hipfftDoubleComplex *idata,
                                  hipfftDoubleReal *odata);


// utility functions
DLL_PUBLIC hipfftResult hipfftSetStream(hipfftHandle plan,
                                    hipStream_t stream);

/*
DLL_PUBLIC hipfftResult hipfftSetCompatibilityMode(hipfftHandle plan,
                                               hipfftCompatibility mode);
*/

DLL_PUBLIC hipfftResult hipfftDestroy(hipfftHandle plan);

DLL_PUBLIC hipfftResult hipfftGetVersion(int *version);


#ifdef __cplusplus
}
#endif // __cplusplus


#endif // __HIPFFT_H__
