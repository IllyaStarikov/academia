library(ggplot2)

iris_copy <- data.frame(iris[1:4])
iris_cluster = kmeans(iris_copy, 3)

table(iris_cluster$cluster, iris$Species)

# could not get regular plot to work so this is what i got to work
# requires packages ggplot2 + labeling (and dependencies)
iris_cluster$cluster <- as.factor(iris_cluster$cluster)
ggplot(iris, aes(Sepal.Length, Sepal.Width, color = iris_cluster$cluster)) + geom_point()
