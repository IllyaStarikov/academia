library(party)

data <- read.csv("C:\\temp\\animal data.csv")
data_frame = data.frame(data)

tree = ctree(Name ~ BloodType + GivesBirth + CanFly + LivesInWater, data=data_frame)
plot(tree, type="simple")
