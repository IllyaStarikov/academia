library(bnlearn)
dag = model2network("[location][cost|location:quality][quality][number_of_people|location:cost]")

location.values         = factor(c("Good", "Bad"))
quality.values          = factor(c("Good", "Normal", "Bad"))
cost.values             = factor(c("High", "Low"))
number_of_people.values = factor(c("High", "Low"))

plot(dag)

location.prob         = array(c(0.6, 0.4), dim=2, dimnames=list(location=location.values))
quality.prob          = array(c(0.3, 0.5,0.2), dim=3, dimnames=list(quality=quality.values))
cost.prob             = array(c(0.8, 0.2, 0.6, 0.4, 0.1, 0.9, 0.6, 0.4, 0.6, 0.4, 0.05, 0.95), dim=c(2,3,2), dimnames=list(cost=cost.values, quality=quality.values, location=location.values))
number_of_people.prob = array(c(0.6, 0.4, 0.8, 0.2, 0.1, 0.9, 0.6, 0.4), dim=c(2, 2, 2), dimnames=list(number_of_people=number_of_people.values, cost=cost.values, location=location.values))

conditional_probability_table = list(location=location.prob, quality=quality.prob, cost=cost.prob, number_of_people=number_of_people.prob)
print(conditional_probability_table)

bayes_network = custom.fit(dag, conditional_probability_table)

location         = factor(c("Good", "Bad"))
quality          = factor(c("Normal", "Good"))
ccost            = factor(c("High", "Low"))
number_of_people = factor(c("Low", "High"))

d_test        = data.frame(location, quality, ccost, number_of_people)
names(d_test) = c("location", "quality", "cost", "number_of_people")
prediction    = predict(bayes_network, "quality", d_test, debug=FALSE)

table(prediction, d_test[,"quality"])
print(prediction)
