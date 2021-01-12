PHP_ARG_ENABLE(observeit, whether to enable observeit support,
    [  --enable-observeit           Enable observeit support])

if test "$PHP_OBSERVEIT" != "no"; then
    STD_CFLAGS="-ggdb -O0 -Wall"

    PHP_OBSERVEIT_CFLAGS="$STD_CFLAGS $MAINTAINER_CFLAGS"
    PHP_SUBST([OBSERVEIT_SHARED_ADD])
    PHP_NEW_EXTENSION(observeit, "observeit.c", $ext_shared,, $PHP_OBSERVEIT_CFLAGS -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi

