# http://ww2.coastal.edu/kingw/statistics/R-tutorials/simplelinear.html

data <- read.delim("~/Projects/tooth-shade-predictor/data/input/40cases.txt", header=F)
#data <- read.delim("~/Projects/tooth-shade-predictor/data/input/30cases.txt", header=F)
#data <- read.delim("~/Projects/tooth-shade-predictor/data/input/10cases.txt", header=F)

plot(data$V1, data$V4)
plot(data$V2, data$V4)
plot(data$V3, data$V4)

plot(data$V2, data$V1)
plot(data$V3, data$V1)

# SLR for DE and L
lm.out = lm(data$V4 ~ data$V1)
summary(lm.out)
plot(data$V4 ~ data$V1)
abline(lm.out, col="red")

# SLR for DE and a
lm.out = lm(data$V4 ~ data$V2)
summary(lm.out)
plot(data$V4 ~ data$V2)
abline(lm.out, col="red")

# SLR for DE and b
lm.out = lm(data$V4 ~ data$V3)
summary(lm.out)
plot(data$V4 ~ data$V3)
abline(lm.out, col="red")

# SLR for L and a
lm.out = lm(data$V1 ~ data$V2)
summary(lm.out)
plot(data$V1 ~ data$V2)
abline(lm.out, col="red")

# SLR for L and b
lm.out = lm(data$V1 ~ data$V3)
summary(lm.out)
plot(data$V1 ~ data$V3)
abline(lm.out, col="red")