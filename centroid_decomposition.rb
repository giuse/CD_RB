require 'ffi'

module CentroidDecomposition
  module LibCD
    extend FFI::Library
    ffi_lib './libcentroiddecomposition.so'
    # void centroidDec( double **X, int n, int m, int truncated);
    attach_function :centroidDec,
      # matrix, nrows, ncols, trunc, L, R
      [:pointer, :int, :int, :int, :pointer, :pointer], :void
  end

  def centroid_decomposition matrix, trunc=nil
    raise "Matrix has rows of unequal length" if matrix.collect(&:size).uniq.size > 1
    nrows = matrix.size
    ncols = matrix.first.size
    trunc ||= ncols
    size_of_double = FFI.type_size FFI::TYPE_FLOAT64
    matrix_ptr = FFI::MemoryPointer.new size_of_double * nrows * ncols
    matrix_ptr.write_array_of_double matrix.flatten
    res_l = FFI::MemoryPointer.new size_of_double * nrows*ncols
    res_r = FFI::MemoryPointer.new size_of_double * ncols*ncols
    LibCD.centroidDec matrix_ptr, nrows, ncols, trunc, res_l, res_r
    mat_l = res_l.read_array_of_double(nrows*ncols).each_slice(ncols).to_a
    mat_r = res_r.read_array_of_double(ncols*ncols).each_slice(ncols).to_a
    [mat_l, mat_r]
  end
end
