require 'ffi'

module CentroidDecomposition
  extend FFI::Library
  ffi_lib './libcentroiddecomposition.so'
  # void centroidDec( double **X, int n, int m, int truncated);
  attach_function :centroidDec,
    # matrix, nrows, ncols, trunc, L, R
    [:pointer, :int, :int, :int, :pointer, :pointer], :void
end
