mkdir -p ppc && ( cd ppc
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../baseblinn.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../basecheck.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../basecolor.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../basecooktorr.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../basedielec.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../baseenviron.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../basegeo.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../basehair.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../baseior.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../baselambert.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../baselens.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../baselight.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../baselightmap.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../basemux.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../basephong.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../basephotbas.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../basepolka.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../baseraymarch.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../basereflect.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../baserefract.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../baseshadow.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../basetexgen.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../basetexgeo.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../basetexlook.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../basetrans.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../baseturb.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../basetwoside.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../basevolume.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../baseward.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../basewardderi.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../basewave.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../baseocc.cpp
g++ -c -O3 -arch ppc -fPIC -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -I.. -I..  ../baseglossy.cpp
g++ -arch ppc -flat_namespace -undefined suppress -dynamiclib -o base.so baseblinn.o basecheck.o basecolor.o basecooktorr.o basedielec.o baseenviron.o basegeo.o basehair.o baseior.o baselambert.o baselens.o baselight.o baselightmap.o basemux.o basephong.o basephotbas.o basepolka.o baseraymarch.o basereflect.o baserefract.o baseshadow.o basetexgen.o basetexgeo.o basetexlook.o basetrans.o baseturb.o basetwoside.o basevolume.o baseward.o basewardderi.o basewave.o baseocc.o baseglossy.o

)

mkdir -p i386 && ( cd i386
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../baseblinn.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../basecheck.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../basecolor.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../basecooktorr.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../basedielec.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../baseenviron.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../basegeo.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../basehair.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../baseior.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../baselambert.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../baselens.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../baselight.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../baselightmap.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../basemux.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../basephong.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../basephotbas.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../basepolka.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../baseraymarch.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../basereflect.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../baserefract.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../baseshadow.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../basetexgen.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../basetexgeo.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../basetexlook.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../basetrans.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../baseturb.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../basetwoside.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../basevolume.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../baseward.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../basewardderi.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../basewave.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../baseocc.cpp
g++ -c -O3 -mtune=pentiumpro -fexpensive-optimizations -fforce-mem -finline-functions -funroll-loops -fomit-frame-pointer -frerun-cse-after-loop -fstrength-reduce -fforce-addr -fPIC -std=c++98 -dynamic -fno-common -DQMC -DMI_MODULE= -DMI_PRODUCT_RAY -DMACOSX -D_REENTRANT -DEVIL_ENDIAN -DX86 -DHYPERTHREAD -I.. -I..  ../baseglossy.cpp
g++ -flat_namespace -undefined suppress -dynamiclib -o base.so baseblinn.o basecheck.o basecolor.o basecooktorr.o basedielec.o baseenviron.o basegeo.o basehair.o baseior.o baselambert.o baselens.o baselight.o baselightmap.o basemux.o basephong.o basephotbas.o basepolka.o baseraymarch.o basereflect.o baserefract.o baseshadow.o basetexgen.o basetexgeo.o basetexlook.o basetrans.o baseturb.o basetwoside.o basevolume.o baseward.o basewardderi.o basewave.o baseocc.o baseglossy.o

)

lipo -output base.so -create ppc/base.so i386/base.so