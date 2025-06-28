resourceType *resource;
int readCount = 0;
semaphore mutex = 1, writeBlock = 1;

reader() { while(TRUE) {
    <other computing>;
    P(mutex); readCount++;
    if(readCount == 1) P(writeBlock);
    V(mutex);
    //CS
    access(resource); P(mutex);
    readCount--;
    if(readCount == 0) V(writeBlock);
    V(mutex);
  }}

writer() {
  while(TRUE) {
    <other computing>;
    P(writeBlock);
    //CS
    access(resource);
    V(writeBlock);
  }}
