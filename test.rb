require_relative 'centroid_decomposition'

matrix = File.readlines('input.txt').map { |r| r.split(',').collect &:to_f }
nrows = matrix.size
ncols = matrix.first.size
truncated = ncols

size_of_double = FFI.type_size FFI::TYPE_FLOAT64
matrix_ptr = FFI::MemoryPointer.new size_of_double * nrows * ncols
matrix_ptr.write_array_of_double matrix.flatten

# require 'pry'; binding.pry
res_l = FFI::MemoryPointer.new size_of_double * nrows*ncols
res_r = FFI::MemoryPointer.new size_of_double * ncols*ncols
CentroidDecomposition.centroidDec(matrix_ptr, nrows, ncols, truncated, res_l, res_r)

mat_l = res_l.read_array_of_double(nrows*ncols).each_slice(ncols).to_a
mat_r = res_r.read_array_of_double(ncols*ncols).each_slice(ncols).to_a

trg_l = matrix = File.readlines('Ltrg.txt').map { |r| r.split(',').collect &:to_f }
trg_r = matrix = File.readlines('Rtrg.txt').map { |r| r.split(',').collect &:to_f }

# check if matrices L and matrices R are respectively (approximately) the same
max_err = 1e-3
resL = mat_l.zip(trg_l).all? { |a,b| a.zip(b).all? { |v1, v2| (v1-v2).abs < max_err } }
puts "Matrices L are #{resL ? '' : 'NOT '}the same"
resR = mat_l.zip(trg_l).all? { |a,b| a.zip(b).all? { |v1, v2| (v1-v2).abs < max_err } }
puts "Matrices R are #{resR ? '' : 'NOT '}the same"

require 'pry'; binding.pry

# require 'fiddle'
# require 'fiddle/import'

# module LibCD
#   extend Fiddle::Importer
#   dlload './libcentroiddecomposition.so'
#   # void centroidDec( double **X, int n, int m, int truncated);
#   extern 'void centroidDec(double **, int, int, int)'
# end

# nrows, ncols, truncated = 10, 20, 10
# mat = nrows.times.collect { |r| ncols.times.collect { |c| Float(r) + Float(c)/10 } }
# matp = Fiddle::Pointer[mat.flatten.pack('d*')]

# require 'pry'; binding.pry
# LibCD.centroidDec(matp, nrows , ncols, truncated)

# require 'pry'; binding.pry
