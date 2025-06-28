using CSV, DataFrames
using Clustering
using Gadfly

data_frame = CSV.read("./problem-5.csv"; types=[Float64, Float64, Float64])
data = convert(Array, data_frame[:, [1, 2]])'

k_means = kmeans(data, 3; maxiter=200, display=:iter)

a = assignments(k_means)
c = counts(k_means)

print("Assignments: ")
println(a')

print("Counts: ")
println(c')

plot(x=data[1, :], y = data=[2, :], color=a, Geom.point)
