/* program boundedbuffer */
const int sizeofbuffer=<buffersize>;
semaphore s=1, n=0, e=sizeofbuffer;
void producer() { while(true) {
    produce( );
    semWait(e);   // P( ) 
    semWait(s); 
    append( );
    semSignal(s); // V( )
    semSignal(n); // signal not empty
  }}
void consumer() { while(true) {
    semWait(n);   // prevent empty buffer
    semWait(s);
    take( );
    semSignal(s); // buffer is unlocked
    semSignal(e);
    consume( );
}}
void main( ) { parbegin( producer, consumer ); }
