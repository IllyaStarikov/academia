using RDatasets, DecisionTree, DataFrames

cars = dataset("datasets", "mtcars")

features = convert(Array, cars[:, [12, 3, 5, 11]])
classification = convert(Array, cars[:, 2])
model = build_tree(classification, features)

print_tree(model)
