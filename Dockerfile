FROM alpine:3.19

ENV Z88DK_PATH="/opt/z88dk"

RUN apk add --no-cache build-base libxml2 m4 gmp \
    && apk add --no-cache -t .build_deps bison flex libxml2-dev git subversion boost-dev texinfo \
    perl-template-toolkit perl-app-cpanminus curl gmp-dev \
    && cpanm -l $HOME/perl5 --no-wget local::lib Template::Plugin::YAML \
    && curl -L http://nightly.z88dk.org/archive/2021/z88dk-20210612-63a43ff-18409.tgz -o /tmp/z88dk.tgz \
    && mkdir -p ${Z88DK_PATH} \
    && tar -xzf /tmp/z88dk.tgz -C ${Z88DK_PATH} --strip-components=1 \
    && sed -i 's/ testsuite//g' ${Z88DK_PATH}/Makefile \
    && cd ${Z88DK_PATH} \
    && eval "$(perl -I$HOME/perl5/lib/perl5 -Mlocal::lib)" \
    && chmod 777 build.sh \
    && CFLAGS="-fcommon" BUILD_SDCC=1 BUILD_SDCC_HTTP=1 BUILD_SDCC_TESTS=0 ./build.sh
WORKDIR ${Z88DK_PATH}
RUN ls -lah
RUN make install 

ENV PATH="${Z88DK_PATH}/bin:${PATH}" \
    ZCCCFG="${Z88DK_PATH}/lib/config/"

WORKDIR /src/

WORKDIR /app
COPY . .
RUN chmod +x /app/makemisifu.sh

#RUN apk add --no-cache git
#WORKDIR /build_vt_sound
#RUN git clone https://github.com/stefanbylund/vt_sound.git
#WORKDIR /build_vt_sound/vt_sound
#RUN make all
#RUN ls -la ./lib/sdcc_iy
#RUN cp ./lib/sdcc_iy/*.lib /app/ay/vt_sound_6.lib 
#RUN cp ./include/vt_sound.h /app/ay/vt_sound.h
#RUN ls -lah /app/ay/vt_sound_6.lib 
#RUN rm -rf /build_vt_sound
#2021
WORKDIR /app

CMD ["/app/makemisifu.sh"]

