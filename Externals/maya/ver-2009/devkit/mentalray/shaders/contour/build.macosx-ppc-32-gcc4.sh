gcc -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I. -I.  ./contourshade.c
gcc -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I. -I.  ./outimgshade.c
gcc -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I. -I.  ./outpsshade.c
g++ -arch ppc -flat_namespace -undefined suppress -dynamiclib -o contour.so contourshade.o outimgshade.o outpsshade.o

