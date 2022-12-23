PORTNAME=	libkernaux
DISTVERSION=	0.7.0
CATEGORIES=	devel
MASTER_SITES=	https://github.com/tailix/libkernaux/releases/download/v${DISTVERSION}/

MAINTAINER=	kotovalexarian@gmail.com
COMMENT=	Auxiliary library for kernel development
WWW=		https://github.com/tailix/libkernaux

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		libtool
USE_LDCONFIG=	yes
GNU_CONFIGURE=	yes

CONFIGURE_ARGS+=	--enable-pkg-config=${PREFIX}/libdata/pkgconfig

.include <bsd.port.mk>
