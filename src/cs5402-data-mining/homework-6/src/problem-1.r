library(kernlab)

xy = matrix(c(1, 2, 4, 1, 1, 5, 2, 1, 2, 0, 1, 2),  nrow=6,  ncol=2)
z =  matrix(c(1, 1, -1, 1, 1, -1),  nrow=6,  ncol=1)

svp = ksvm(xy, z, type="C-svc", kernel='vanilladot', C=100, scaled=c())

print(xmatrix(svp))
print(predict(svp, matrix(c(0, 1), nrow=1, ncol=2)))
print(predict(svp, matrix(c(4, 1), nrow=1, ncol=2)))
