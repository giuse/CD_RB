require 'fiddle'
require 'fiddle/import'

module LibCD
  extend Fiddle::Importer
  dlload './libcentroiddecomposition.so'
  # void centroidDec( double *X, int n, int m, int truncated, double* L, double* R);
  extern 'void centroidDec(double*, int, int, int, double*, double*)'
end

matrix = File.readlines('input.txt').map { |r| r.split(',').collect &:to_f }
nrows = matrix.size
ncols = matrix.first.size
truncated = ncols

matp = Fiddle::Pointer[matrix.flatten.pack('d*')]
lp = Fiddle::Pointer[([0]*nrows*ncols).pack('d*')]
rp = Fiddle::Pointer[([0]*ncols*ncols).pack('d*')]

LibCD.centroidDec(matp, nrows , ncols, truncated, lp, rp)

require 'pry'; binding.pry
