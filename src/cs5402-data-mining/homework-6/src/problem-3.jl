using RDatasets, Clustering, Distances, Gadfly

cars = dataset("datasets", "mtcars")
x = convert(Array, cars[:,3])'
y = convert(Array, cars[:,11])'
distances = pairwise(Euclidean(), x, y)

cluster = dbscan(distances, 2, 5)

assignments = assignments(cluster)
cluster_plot = plot(x=x, y=y, color=assignments, Geom.point);

print(cluster)
