require_relative 'centroid_decomposition'
include CentroidDecomposition

matrix = File.readlines('input.txt').map { |r| r.split(',').collect &:to_f }
trg_l = File.readlines('Ltrg.txt').map { |r| r.split(',').collect &:to_f }
trg_r = File.readlines('Rtrg.txt').map { |r| r.split(',').collect &:to_f }

mat_l, mat_r = centroid_decomposition matrix

max_err = 1e-3

resL = mat_l.zip(trg_l).all? { |a,b| a.zip(b).all? { |v1, v2| (v1-v2).abs < max_err } }
puts "Matrices L are #{resL ? '' : 'NOT '}the same"

resR = mat_l.zip(trg_l).all? { |a,b| a.zip(b).all? { |v1, v2| (v1-v2).abs < max_err } }
puts "Matrices R are #{resR ? '' : 'NOT '}the same"
