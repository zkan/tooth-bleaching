# http://ww2.coastal.edu/kingw/statistics/R-tutorials/simplelinear.html

data <- read.delim("~/Projects/tooth-shade-predictor/data/input/40cases.txt", header=F)

plot(data$V1, data$V4)
plot(data$V2, data$V4)
plot(data$V3, data$V4)

plot(data$V2, data$V1)
plot(data$V3, data$V1)

# SLR for DE and L
lm.out = lm(data$V4 ~ data$V1)
lm.out
summary(lm.out)
plot(data$V4 ~ data$V1, xlab="L", ylab=expression(Delta * "E"))
abline(lm.out, col="red")

# SLR for DE and a
lm.out = lm(data$V4 ~ data$V2)
lm.out
summary(lm.out)
plot(data$V4 ~ data$V2, xlab="a", ylab=expression(Delta * "E"))
abline(lm.out, col="red")

# SLR for DE and b
lm.out = lm(data$V4 ~ data$V3)
lm.out
summary(lm.out)
plot(data$V4 ~ data$V3, xlab="b", ylab=expression(Delta * "E"))
abline(lm.out, col="red")

# SLR for L and a
lm.out = lm(data$V1 ~ data$V2)
lm.out
summary(lm.out)
plot(data$V1 ~ data$V2, xlab="a", ylab="L")
abline(lm.out, col="red")

# SLR for L and b
lm.out = lm(data$V1 ~ data$V3)
lm.out
summary(lm.out)
plot(data$V1 ~ data$V3, xlab="b", ylab="L")
abline(lm.out, col="red")

# Multiple Linear Regression
train <- read.delim("~/Projects/tooth-shade-predictor/data/input/30cases.txt", header=F)

model = lm(train$V4 ~ train$V1 + train$V2 + train$V3)
model
summary(model)

# dE between obtained dE and predicted dE
dE <- read.delim("~/Projects/tooth-shade-predictor/data/input/mlr-results.txt", header=F)
lm.out = lm(dE$V2 ~ dE$V1)
lm.out
summary(lm.out)
plot(dE$V2 ~ dE$V1, xlab=expression("Predicted " * Delta * "E"), ylab=expression("Obtained " * Delta * "E"))
abline(lm.out, col="red")